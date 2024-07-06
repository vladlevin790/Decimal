#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

// >
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int result_code = 0;

    int sign_1 = get_decimal_sign(value_1);
    int sign_2 = get_decimal_sign(value_2);

    if (sign_1 != sign_2) {
        // Если второе число отрицательное, то возвращаем 1 - TRUE
        result_code = sign_2;
    } else {
        s21_decimal decimal_ten = get_new_decimal();
        s21_from_int_to_decimal(10, &decimal_ten);

        int exponent_1 = get_decimal_exponent(value_1);
        int exponent_2 = get_decimal_exponent(value_2);

        while (exponent_1 != exponent_2) {
            if (exponent_1 < exponent_2) {
                s21_mul(value_1, decimal_ten, &value_1);
                exponent_1++;
            } else {
                s21_mul(value_2, decimal_ten, &value_2);
                exponent_2++;
            }
        }

        int is_exit = 0;
        for (int i = 95; i >= 0 && !is_exit; i--) {
            int bit_1 = get_decimal_digit_by_index(value_1, i);
            int bit_2 = get_decimal_digit_by_index(value_2, i);

            if (bit_1 != bit_2) {
                result_code = (sign_1 && bit_1 < bit_2) || (!sign_1 && bit_1 > bit_2);
                is_exit = 1;
            }
        }
    }

    return result_code;
}