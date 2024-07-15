#include "s21_decimal.h"

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

void set_sign(s21_decimal *num, int sign) {
    if (sign)
        num->bits[3] |= 1 << 31;
    else
        num->bits[3] &= ~(1 << 31);
}

// // устанавливает степень для децимал
// void set_scale(s21_decimal *num, int scale){
//     num->bits[3] |= scale << 16;
// }

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

void get_mantissa(s21_decimal num, int *mantissa) {
    mantissa[0] = num.bits[0];
    mantissa[1] = num.bits[1];
    mantissa[2] = num.bits[2];
}

int compare_mantissa(int *mantissa1, int *mantissa2) {
    for (int i = 2; i >= 0; i--) {
        if (mantissa1[i] > mantissa2[i]) return 1;
        if (mantissa1[i] < mantissa2[i]) return -1;
    }
    return 0;
}

int add_mantissa(int *mantissa1, int *mantissa2, int *result) {
    unsigned long long carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long sum = (unsigned long long)(unsigned int)mantissa1[i] + (unsigned int)mantissa2[i] + carry;
        result[i] = (int)sum;
        carry = sum >> 32;
    }
    return carry ? 1 : 0;  // Возвращаем 1, если произошло переполнение
}

void subtract_mantissa(int *mantissa1, int *mantissa2, int *result) {
    long long borrow = 0;
    for (int i = 0; i < 3; i++) {
        long long diff = (long long)mantissa1[i] - mantissa2[i] - borrow;
        if (diff < 0) {
            diff += (1LL << 32);
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = (int)diff;
    }
}


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    int scale1 = get_scale(value_1);
    int scale2 = get_scale(value_2);

    int mantissa1[3], mantissa2[3];
    get_mantissa(value_1, mantissa1);
    get_mantissa(value_2, mantissa2);

    // Приведение к общему масштабу
    while (scale1 < scale2) {
        if (scale1 < 28) {
            for (int i = 0; i < 3; i++) mantissa1[i] *= 10;
            scale1++;
        } else {
            return 1;  // Число слишком велико
        }
    }

    while (scale2 < scale1) {
        if (scale2 < 28) {
            for (int i = 0; i < 3; i++) mantissa2[i] *= 10;
            scale2++;
        } else {
            return 2;  // Число слишком велико
        }
    }

    int result_mantissa[3] = {0, 0, 0};
    
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
    for (int i = 0; i < 3; i++) result->bits[i] = result_mantissa[i];
    return 0;
}
