#include "../s21_decimal.h"
#include "comparison.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    s21_comparison_result code = S21_COMPARISON_TRUE;

    if (value_1.bits[0] == 0 && value_1.bits[1] == 0
        && value_1.bits[2] == 0 && value_2.bits[0] == 0
        && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
            code = S21_COMPARISON_TRUE;
        } else {
            code = value_1.bits[0] == value_2.bits[0]
                && value_1.bits[1] == value_2.bits[1]
                && value_1.bits[2] == value_2.bits[2]
                && value_1.bits[3] == value_2.bits[3];
        }
    return code;
}