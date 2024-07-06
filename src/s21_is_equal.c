#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    int result_code = 0;

    if (value_1.bits[0] == 0 && value_1.bits[1] == 0
        && value_1.bits[2] == 0 && value_2.bits[0] == 0
        && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        result_code = 1;
    } else {
        int exponent_1 = get_decimal_exponent(value_1);
        int exponent_2 = get_decimal_exponent(value_2);

        int sign_1 = get_decimal_sign(value_1);
        int sign_2 = get_decimal_sign(value_2);

        result_code = value_1.bits[0] == value_2.bits[0]
            && value_1.bits[1] == value_2.bits[1]
            && value_1.bits[2] == value_2.bits[2]
            && exponent_1 == exponent_2
            && sign_1 == sign_2;
    }

    return result_code;
}
