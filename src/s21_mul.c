#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        // TODO: какой код ошибки?
    } else {
        clear_decimal(result);
        s21_big_decimal big_result = {{get_new_decimal(), get_new_decimal()}};

        int result_sign = get_decimal_sign(value_1) != get_decimal_sign(value_2);
        int exponent_1 = get_decimal_exponent(value_1), exponent_2 = get_decimal_exponent(value_2);

        set_decimal_sign(&value_1, 0);
        set_decimal_sign(&value_2, 0);

        set_decimal_exponent(&value_1, 0);
        set_decimal_exponent(&value_2, 0);

        s21_big_decimal big_value_1 = {{value_1, get_new_decimal()}};
        s21_big_decimal big_value_2 = {{value_2, get_new_decimal()}};

        big_result = s21_big_mul(big_value_1, big_value_2);

        int count_out_bounds = s21_count_digits_out_bounds(big_result);
        int res_power = exponent_1 + exponent_2 - count_out_bounds;

        if (count_out_bounds > exponent_1 + exponent_2) {
            result_code = 1;
        } else {
            s21_big_decimal ten_big_decimal = {{get_decimal_with_int_value(10), get_new_decimal()}};
            s21_big_decimal tmp = {{get_new_decimal(), get_new_decimal()}};

            // В шарпе почему-то при ~34 знаках после запятой числа учитываются
            // а при ~35 уже нет
            while (count_out_bounds > 16) {
                s21_big_div(big_result, ten_big_decimal, &big_result, &tmp);
                count_out_bounds--;
            }

            printf("%d\n", res_power);
            // Если слишком много цифр после запятой получается в результате, то корректируем результат
            if (res_power > 28) {
                count_out_bounds = res_power - 28 + count_out_bounds;
                res_power = 28;
            }

            s21_big_decimal remainder = {{get_new_decimal(), get_new_decimal()}};
            s21_big_decimal powerten = get_big_decimal_ten_pow(count_out_bounds);

            // Уменьшаем результат, чтобы он поместился в 96бит числа decimal
            // remainder - остаток от деления при этом
            s21_big_div(big_result, powerten, &big_result, &remainder);
            // Устанавливаем для остатка степень, чтобы выполнить банковское округление чисел decimal
            set_decimal_exponent(&remainder.decimal[0], count_out_bounds);
            // Выполняем банковское округления результата, исходя из остатка от деления remainder
            big_result.decimal[0] = s21_round_banking(big_result.decimal[0], remainder.decimal[0]);
            // Устанавливаем степень результата
            set_decimal_exponent(&big_result.decimal[0], res_power);

            // Анализируем результат на корректность (переполнение)
            if (!s21_is_full_equal_zero(big_result.decimal[1]) || check_decimal(big_result.decimal[0]) ||
                s21_get_range_bits(big_result.decimal[0].bits[3], 0, 15) || s21_get_range_bits(big_result.decimal[0].bits[3], 24, 30)) {
                result_code = 1;
            } else {
                *result = big_result.decimal[0];
            }
        }

        if (result_code == 1 && result_sign == 1) {
            result_code = 2;
        } else {
            if (s21_is_not_equal(value_1, get_decimal_with_int_value(0)) || s21_is_not_equal(value_2, get_decimal_with_int_value(0))) {
                *result = s21_remove_useless_zeros(*result); // TODO: тут возможно неправильно
            }
            set_decimal_sign(result, result_sign);
        }
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