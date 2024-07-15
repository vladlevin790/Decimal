#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        // TODO: какой код ошибки?
    } else {
        set_decimal_sign(result, get_decimal_sign(value_1) || get_decimal_sign(value_2));

        int exponent = get_decimal_exponent(value_1) + get_decimal_exponent(value_2);
        if (exponent > 28) {
            exponent = 28;
        }
        set_decimal_exponent(result, exponent);

        // всю дробную часть воспринимаем, как целые числа
        set_decimal_exponent(&value_1, 0);
        set_decimal_exponent(&value_2, 0);

        // Убираем знак, чтобы можно было правильно складывать числа
        set_decimal_sign(&value_1, 0);
        set_decimal_sign(&value_2, 0);

        result_code = s21_mul_handle(value_1, value_2, result);

        // Число слишком мало или равно отрицательной бесконечности
        if (result_code == 0 && get_decimal_exponent(*result) > 28) {
            result_code = 2;
        }
    }

    return result_code;
}

int s21_mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;
    
    int count_digits_2 = get_count_digits(value_2);

    for (int i = 0; i < count_digits_2 && result_code == 0; i++) {
        if (get_decimal_digit_by_index(value_2, i)) {
            result_code = s21_add(*result, value_1, result);
        }
        left_shift_decimal(&value_1, 1);
    }

    return result_code;
}