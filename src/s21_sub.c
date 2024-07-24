#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_sub_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        result_code = S21_DECIMAL_ERROR;
    } else {
        int sign_1 = get_decimal_sign(value_1), sign_2 = get_decimal_sign(value_2);

        // + +    a - b    5 - 3
        // + -    a + b    5 + 3
        // - +    a + b    -5 - 3
        // - -    -a + b    -5 + 7  7 - 5

        if (sign_1 == 0 && sign_2 == 0) {
            if (s21_is_less(value_1, value_2)) {
                result_code = s21_sub_handle(value_2, value_1, result);
                result_code = result_code == 1 ? 2 : result_code;
                set_decimal_sign(result, 1);
            } else {
                result_code = s21_sub_handle(value_1, value_2, result);
            }
        } else if (sign_1 == 0 && sign_2 == 1) {
            set_decimal_sign(&value_2, 0);
            result_code = s21_add(value_2, value_1, result);
        } else if (sign_1 == 1 && sign_2 == 0) {
            set_decimal_sign(&value_1, 0);
            result_code = s21_add(value_1, value_2, result);

            result_code = result_code == 1 ? 2 : result_code;
            set_decimal_sign(result, 1);
        } else if (sign_1 == 1 && sign_2 == 1) {
            set_decimal_sign(&value_1, 0);
            set_decimal_sign(&value_2, 0);

            if (s21_is_less_or_equal(value_1, value_2)) { // 3 - 5
                result_code = s21_sub_handle(value_2, value_1, result);
            } else {
                result_code = s21_sub_handle(value_1, value_2, result);
                set_decimal_sign(result, 1);
                result_code = result_code == 1 ? 2 : result_code;
            }
        }
    }

    return result_code;
}

int s21_sub_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    int exponent_1 = get_decimal_exponent(value_1), exponent_2 = get_decimal_exponent(value_2);
    int result_exponent = exponent_1 > exponent_2 ? exponent_1 : exponent_2;

    s21_big_decimal big_value_1 = {{get_new_decimal(), get_new_decimal()}};
    s21_big_decimal big_value_2 = {{get_new_decimal(), get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    s21_big_decimal big_result = s21_big_sub(big_value_1, big_value_2);
    print_big_decimal(big_result);

    int count_out_bounds = s21_count_digits_out_bounds(big_result);
    result_exponent -= count_out_bounds;

    if (result_exponent < 0) {
        result_code = 1;
    } else {
        s21_big_decimal div_whole = {{get_new_decimal(), get_new_decimal()}};
        s21_big_decimal div_remainder = {{get_new_decimal(), get_new_decimal()}};
        s21_big_div(big_result, s21_get_big_decimal_ten_pow(count_out_bounds), &div_whole, &div_remainder);

        set_decimal_exponent(&div_remainder.decimal[0], count_out_bounds);
        div_whole = s21_round_banking(div_whole.decimal[0], div_remainder.decimal[0]);

        if (!s21_is_full_equal_zero(div_whole.decimal[1]) || div_whole.decimal[0].bits[3] != 0) {
            result_code = 1;
        } else {
            *result = div_whole.decimal[0];
            set_decimal_exponent(result, result_exponent);
        }
    }

    return result_code;
}

s21_big_decimal s21_big_sub(s21_big_decimal decimal1, s21_big_decimal decimal2) {
    // Вычитатель в дополнительных кодах
    s21_big_decimal one = {{get_decimal_with_int_value(1), get_new_decimal()}};

    decimal2.decimal[0] = s21_decimal_not(decimal2.decimal[0]);
    decimal2.decimal[1] = s21_decimal_not(decimal2.decimal[1]);

    decimal1 = s21_big_add(decimal1, decimal2);
    decimal1 = s21_big_add(decimal1, one);

    return decimal1;
}