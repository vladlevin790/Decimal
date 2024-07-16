// #include "s21_decimal.h"

// void print_binary(int num){
//     for(int i=31; i>=0; i--){
//         printf("%d", (num>>i) &1);
//         // if (i%32 == 0){
//         //     printf("\n");
//         // }
//         // if i ==2 сдвиг вправо 00001010 >> 00000010
//         // было 2^1 + 2^3 = 10
//         // стало 2^1 = 2
//         // 00000010 & 1 = 00000010 & 00000001 = 0
//     }
//     printf("\n");
// }

// void print_decimal(s21_decimal num ) {
//     for (int i = 3; i >=0; i--) {
//         print_binary(num.bits[i]);
//         // printf("%d", num.bits[i]);
//         // if (i != 0) {
//         //     printf(".");
//         // }

//     }
//     printf("\n");
// }

// void print_decimal_to_int(s21_decimal num) {
//     for (int i = 0; i <4; i++){
//         printf("%d : ", num.bits[i]);
//     }
//     printf("\n");
// }
// устанавливает знак для децимал 1 отрицательное, 0 положительное
// void set_sing(s21_decimal *num, int sign) {
//     num->bits[3] |= sign << 31;  // |= это побитовое сложение
// }

#include "s21_decimal.h"

void set_sign(s21_decimal *num, int sign) {
    if (sign)
        num->bits[3] |= 1 << 31;
    else
        num->bits[3] &= ~(1 << 31);
}

void set_scale(s21_decimal *num, int scale) {
    num->bits[3] &= ~(0xFF << 16);  // Clear current scale
    num->bits[3] |= (scale & 0xFF) << 16;  // Set new scale
}

int get_sign(s21_decimal num) {
    return (num.bits[3] >> 31) & 1;
}

int get_scale(s21_decimal num) {
    return (num.bits[3] >> 16) & 0xFF;
}

void get_mantissa(s21_decimal num, unsigned int *mantissa) {
    mantissa[0] = num.bits[0];
    mantissa[1] = num.bits[1];
    mantissa[2] = num.bits[2];
}

void set_mantissa(s21_decimal *num, unsigned int *mantissa) {
    num->bits[0] = mantissa[0];
    num->bits[1] = mantissa[1];
    num->bits[2] = mantissa[2];
}

int compare_mantissa(unsigned int *mantissa1, unsigned int *mantissa2) {
    for (int i = 2; i >= 0; i--) {
        if (mantissa1[i] > mantissa2[i]) return 1;
        if (mantissa1[i] < mantissa2[i]) return -1;
    }
    return 0;
}

int add_mantissa(unsigned int *mantissa1, unsigned int *mantissa2, unsigned int *result) {
    unsigned long long carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long sum = (unsigned long long)mantissa1[i] + mantissa2[i] + carry;
        result[i] = (unsigned int)sum;
        carry = sum >> 32;
    }
    return carry ? 1 : 0;  // Возвращаем 1, если произошло переполнение
}

void subtract_mantissa(unsigned int *mantissa1, unsigned int *mantissa2, unsigned int *result) {
    long long borrow = 0;
    for (int i = 0; i < 3; i++) {
        long long diff = (long long)mantissa1[i] - mantissa2[i] - borrow;
        if (diff < 0) {
            diff += (1LL << 32);
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = (unsigned int)diff;
    }
}

void shift_mantissa_right(unsigned int *mantissa) {
    unsigned long long borrow = 0;
    for (int i = 2; i >= 0; i--) {
        unsigned long long temp = ((unsigned long long)mantissa[i] >> 1) | (borrow << 31);
        borrow = mantissa[i] & 1;
        mantissa[i] = (unsigned int)temp;
    }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    int scale1 = get_scale(value_1);
    int scale2 = get_scale(value_2);

    unsigned int mantissa1[3], mantissa2[3], result_mantissa[3] = {0, 0, 0};
    get_mantissa(value_1, mantissa1);
    get_mantissa(value_2, mantissa2);

    // Приведение к общему масштабу
    while (scale1 < scale2) {
        if (scale1 < 28) {
            for (int i = 2; i >= 0; i--) {
                unsigned long long temp = (unsigned long long)mantissa1[i] * 10;
                if (i > 0) temp += mantissa1[i - 1] >> 28;
                mantissa1[i] = temp & 0xFFFFFFFF;
            }
            scale1++;
        } else {
            shift_mantissa_right(mantissa2);
            scale2--;
        }
    }

    while (scale2 < scale1) {
        if (scale2 < 28) {
            for (int i = 2; i >= 0; i--) {
                unsigned long long temp = (unsigned long long)mantissa2[i] * 10;
                if (i > 0) temp += mantissa2[i - 1] >> 28;
                mantissa2[i] = temp & 0xFFFFFFFF;
            }
            scale2++;
        } else {
            shift_mantissa_right(mantissa1);
            scale1--;
        }
    }
    

    if (sign1 == sign2) {
        // Оба числа с одинаковыми знаками
        if (add_mantissa(mantissa1, mantissa2, result_mantissa)) {
            return 1;  // Переполнение
        }
        set_sign(result, sign1);
    } else {
        // Числа с разными знаками
        int compare = compare_mantissa(mantissa1, mantissa2);
        if (compare == 0) {
            // Оба числа равны
            for (int i = 0; i < 4; i++) result->bits[i] = 0;
            return 0;  // Оба числа равны нулю
        } else if (compare > 0) {
            // value_1 больше по модулю
            subtract_mantissa(mantissa1, mantissa2, result_mantissa);
            set_sign(result, sign1);
        } else {
            // value_2 больше по модулю
            subtract_mantissa(mantissa2, mantissa1, result_mantissa);
            set_sign(result, sign2);
        }
    }

    set_scale(result, scale1);
    set_mantissa(result, result_mantissa);
    return 0;
}

