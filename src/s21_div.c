#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"
#include <stdlib.h>

#define BYTES_FOR_DIGIT 4

int s21_div_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_set_decimal_from_int_part(int* arr, int arr_length, s21_decimal *result);
int s21_set_decimal_from_fract_part(int* arr, int arr_length, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        // TODO: какой код ошибки?
    } else if (s21_is_equal(value_2, get_decimal_with_int_value(0))) {
        // TODO: деление на 0
    } else {
        set_decimal_sign(result, get_decimal_sign(value_1) || get_decimal_sign(value_2));
        
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
    
    int digit_index_1 = get_count_digits(value_1) - 1;
    
    int int_digits[BYTES_FOR_DIGIT] = {0, 0, 0, 0};
    int fract_digits[BYTES_FOR_DIGIT] = {0, 0, 0, 0};
    int curr_int_index = 0, curr_fract_index = 0;

    const int max_index = (BYTES_FOR_DIGIT * sizeof(int) * 8) - 1;

    s21_decimal curr_divisible = get_new_decimal();
    int is_remainder_zero = 0;
    while (result_code == 0 && !is_remainder_zero && curr_int_index <= max_index && curr_fract_index <= max_index) {
        result_code = s21_mul(curr_divisible, get_decimal_with_int_value(10), &curr_divisible);
        
        // Если можем взять число из делимого
        if (digit_index_1 >= 0) {
            if (get_decimal_digit_by_index(value_1, digit_index_1)) {
                result_code = s21_add(curr_divisible, get_decimal_with_int_value(1), &curr_divisible);
            }
            digit_index_1--;
        }

        int curr_answer = s21_is_greater_or_equal(curr_divisible, value_2);
        
        // Если больше нет чисел в делимом
        if (digit_index_1 < -1) {
            if (curr_answer) {
                s21_set_bit(fract_digits[curr_fract_index / 32], curr_fract_index % 32);
            }
            curr_fract_index++;
        } else if (curr_int_index > 0 || curr_answer == 1) {
            if (curr_answer) {
                s21_set_bit(int_digits[curr_int_index / 32], curr_int_index % 32);
            }
            curr_int_index++;
        }

        if (curr_answer == 1) {
            result_code = s21_sub(curr_divisible, value_2, &curr_divisible);
        }
        is_remainder_zero = s21_is_equal(curr_divisible, get_decimal_with_int_value(0));
    }

    if (result_code == 0) {
        result_code = s21_set_decimal_from_int_part(int_digits, curr_int_index, result);
    }
    if (result_code == 0) {
        result_code = s21_set_decimal_from_fract_part(fract_digits, curr_fract_index, result);
    }
    
    return result_code;
}

int s21_set_decimal_from_int_part(int* arr, int arr_length, s21_decimal *result) {
    int result_code = 0;

    s21_decimal pow_two_decimal = get_decimal_with_int_value(1);
    
    for (int i = arr_length - 1; i >= 0 && result_code == 0; i--) {
        if (s21_get_bit(arr[i / 32], i % 32)) {
            result_code = s21_add(*result, pow_two_decimal, result);
        }

        s21_mul(pow_two_decimal, get_decimal_with_int_value(2), &pow_two_decimal);
    }

    return result_code;
}

int s21_set_decimal_from_fract_part(int* arr, int arr_length, s21_decimal *result) {
    int result_code = 0;
    
    s21_decimal pow_two_decimal = get_decimal_with_float_value(0.5f);
    
    for (int i = 0; i < arr_length && result_code == 0; i++) {
        if (s21_get_bit(arr[i / 32], i % 32)) {
            result_code = s21_add(*result, pow_two_decimal, result);
        }

        s21_mul(pow_two_decimal, get_decimal_with_float_value(0.5f), &pow_two_decimal);
    }

    return result_code;
}