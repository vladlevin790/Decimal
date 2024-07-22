#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"
#include <math.h>

s21_decimal parse_float_str_to_decimal(char* float_str, int exponent);
int get_exponent_from_float_str(char* float_str);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int result_code = 0;

    if (dst == s21_NULL || isnan(src) || isinf(src) ||
        fabsf(src) > 79228162514264337593543950335.0f) {
        result_code = 1;
    } else if (fabsf(src) > 0 && fabsf(src) < 1e-28) {
        result_code = 1;
        *dst = get_new_decimal();
    } else {
        clear_decimal(dst);
        char float_str[64] = {0};
        sprintf(float_str, "%.6e", fabs(src));

        int exponent = get_exponent_from_float_str(float_str);
        if (exponent < 0) {
            sprintf(float_str, "%.28f", src);
        }
        
        *dst = parse_float_str_to_decimal(float_str, exponent);
        set_decimal_sign(dst, signbit(src) != 0);
    }

    return result_code;
}

s21_decimal parse_float_str_to_decimal(char* float_str, int exponent) {
    s21_decimal decimal = get_new_decimal();
    s21_decimal decimal_tmp = get_new_decimal();

    int is_fractional = 0, curr_fractional_pow = 1, count_digits = 7, count_writed_digits = 0;
    while (*float_str && *float_str != 'e' && count_digits > 0) {
        if (*float_str >= '0' && *float_str <= '9' && (*float_str != '0' || count_digits < 7)) {
            if (is_fractional && *float_str == '0') {
                curr_fractional_pow++;
            } else {
                clear_decimal(&decimal_tmp);

                s21_from_int_to_decimal(pow(10, curr_fractional_pow), &decimal_tmp);
                s21_mul(decimal, decimal_tmp, &decimal);

                s21_from_int_to_decimal(*float_str - '0', &decimal_tmp);
                s21_add(decimal, decimal_tmp, &decimal);

                count_writed_digits += curr_fractional_pow;
                curr_fractional_pow = 1;
            }
            count_digits--;
        } else if (*float_str == '.') {
            is_fractional = 1;
        }

        float_str++;
    }

    // Заполнение целой части нулями, если в нем меньше 7 чисел
    while (count_writed_digits < exponent + 1) {
        clear_decimal(&decimal_tmp);

        s21_from_int_to_decimal(10, &decimal_tmp);
        s21_mul(decimal, decimal_tmp, &decimal);

        count_writed_digits++;
    }

    if (exponent < 0) {
        exponent = -exponent;
        set_decimal_exponent(&decimal, exponent + (count_writed_digits - 1));
    } else {
        set_decimal_exponent(&decimal, count_writed_digits - (exponent + 1));
    }

    return decimal;
}

int get_exponent_from_float_str(char* float_str) {
    if (float_str == s21_NULL) {
        return 0;
    }

    int exponent = 0;

    char *p = float_str;
    while (*p && *p != 'e') {
        p++;
    }

    if (*p) {
        p++;
    }

    int sign = *p == '-';
    p++;

    while (*p >= '0' && *p <= '9') {
        exponent = exponent * 10 + (*p - '0');
        p++;
    }
    if (sign)  {
        exponent = -exponent;
    }

    return exponent;
}