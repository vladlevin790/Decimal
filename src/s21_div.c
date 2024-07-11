#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_div_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        // TODO: какой код ошибки?
    } else {
        set_decimal_sign(result, get_decimal_sign(value_1) || get_decimal_sign(value_2));
        set_decimal_exponent(result, get_decimal_exponent(value_1) + get_decimal_exponent(value_2));

        set_decimal_exponent(&value_1, 0);
        set_decimal_exponent(&value_2, 0);

        set_decimal_sign(&value_1, 0);
        set_decimal_sign(&value_2, 0);

        result_code = s21_div_handle(value_1, value_2, result);
    }

    return result_code;
}

int s21_div_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;
    
    int count_digits_1 = get_count_digits(value_1);
    int count_digits_2 = get_count_digits(value_2);

    for (int i = 0; i < count_digits_2 && result_code == 0; i++) {
        // Если сейчас идёт умножение на 0
        if (!get_decimal_digit_by_index(value_2, i)) {
            continue;
        }
        
        for (int j = 0; j < count_digits_1 && result_code == 0; j++) {
            result_code = s21_add(result, value_1, &result);
        }
    }

    return result_code;
}