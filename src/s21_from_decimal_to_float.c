#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"
#include <math.h>

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int result_code = 0;

    if (dst == NULL || check_decimal(src)) {
        result_code = 1;
    } else {
        *dst = 0;

        for (int i = 0; i < 96; i++) {
            *dst += get_decimal_digit_by_index(src, i) * pow(2, i);
        }
        
        *dst /= pow(10, get_decimal_exponent(src));
        if (*dst != 0 && get_decimal_sign(src)) {
            *dst *= -1;
        }
    }

    return result_code;
}