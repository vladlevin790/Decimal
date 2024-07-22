#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result_code = 1;

    value_1 = s21_remove_useless_zeros(value_1);
    value_2 = s21_remove_useless_zeros(value_2);

    if (value_1.bits[0] == 0 && value_1.bits[1] == 0
        && value_1.bits[2] == 0 && value_2.bits[0] == 0
        && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        result_code = 1;
    } else {
        result_code = value_1.bits[0] == value_2.bits[0]
                    && value_1.bits[1] == value_2.bits[1]
                    && value_1.bits[2] == value_2.bits[2]
                    && value_1.bits[3] == value_2.bits[3];
    }

    return result_code;
}

int s21_is_full_equal_zero(s21_decimal value_1) {
    return value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 && value_1.bits[3] == 0;
}

int s21_is_equal_big(s21_big_decimal value_1, s21_big_decimal value_2, int sign_1, int sign_2) {
    int result_code = 1;

    for (int i = 255; i >= 0 && result_code; i--) {
        int curr_decimal = i / 128;
        int curr_bit = (i % 128) / 32;
        int bit_index = i % 32;

        int bit_1 = s21_get_bit(value_1.decimal[curr_decimal].bits[curr_bit], bit_index);
        int bit_2 = s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], bit_index);

        if (bit_1 != bit_2) {
            result_code = 0;
        }
    }

    if (result_code == 1 &&
        (!s21_is_equal(value_1.decimal[0], get_decimal_with_int_value(0)) || !s21_is_equal(value_1.decimal[1], get_decimal_with_int_value(0))) &&
        (!s21_is_equal(value_2.decimal[0], get_decimal_with_int_value(0)) || !s21_is_equal(value_2.decimal[1], get_decimal_with_int_value(0)))) {
        result_code = sign_1 == sign_2;
    }
    
    return result_code;
}
