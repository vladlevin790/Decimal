#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

void left_shift_big_decimal(s21_big_decimal *big_value);
int is_decimal_overflow(s21_big_decimal big_value);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        // TODO: какой код ошибки?
    } else {
        s21_big_decimal tmp_big_result = {{get_new_decimal(), get_new_decimal()}};
        s21_big_decimal big_value_1 = {{value_1, get_new_decimal()}};
        s21_big_decimal big_value_2 = {{value_2, get_new_decimal()}};

        tmp_big_result = s21_big_mul(big_value_1, big_value_2);

        if (tmp_big_result.decimal[1].bits[3] == 1) {
            printf("tmp\n");
        }
        // int need_shift = 

        // Число слишком мало или равно отрицательной бесконечности
        // if (result_code == 0 && get_decimal_exponent(*result) > 28) {
        //     result_code = 2;
        // }
    }

    return result_code;
}

s21_big_decimal s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2) {
    s21_big_decimal result = {{get_new_decimal(), get_new_decimal()}};

    int max_index = get_count_full_digits(value_2.decimal[1]) - 1;
    max_index = max_index == -1 ? get_count_full_digits(value_2.decimal[0]) - 1 : DECIMAL_MAX_BITS + max_index;

    for (int i = 0; i <= max_index; i++) {
        int curr_decimal = i / 128;
        int curr_bit = (i % 128) / 32;
        int curr_index = i % 32;
        
        if (s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], curr_index)) {
            result = s21_big_add(result, value_1);
        }
        value_1 = s21_left_shift_big_decimal(value_1, 1);
    }

    return result;
}

// int s21_big_mul(s21_big_decimal big_value_1, s21_big_decimal big_value_2, s21_big_decimal *big_result) {
//     int result_code = 0;

//     for (int i = 0; i < 192 && result_code == 0; i++) {
//         int curr_decimal = i / 96;
//         int curr_bit = i / 32;
//         int curr_index = i % 32;
        
//         if (s21_get_bit(big_value_2.decimal[curr_decimal].bits[curr_bit], curr_index)) {
//             s21_big_add(*big_result, big_value_2, big_result);
//         }
//         left_shift_big_decimal(&big_value_1);
//     }

//     return result_code;
// }

// int s21_get_shift_big_decimal(s21_big_decimal big_decimal) {

// }