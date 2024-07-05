#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"
#include <math.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int result_code = 0;

    if (dst == s21_NULL || check_int_range(src)) {
        result_code = 1;
    } else {
        s21_decimal truncated_decimal = get_new_decimal();
        // TODO: s21_truncate(src, &truncated_decimal);

        *dst = 0;
        for (int i = 0; i < 32; i++) {
            *dst += get_decimal_digit_by_index(truncated_decimal, i) * pow(2, i);
        }

        if (get_decimal_sign(src) && *dst != INT_MIN) {
            *dst *= -1;
        }
    }
    
    return result_code;
}