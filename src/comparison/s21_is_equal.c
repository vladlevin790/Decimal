#include "../s21_decimal.h"
#include "comparison.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    s21_comparison_result code = S21_COMPARISON_TRUE;

    s21_decimal tmp_1;
    s21_decimal tmp_2;

    if (tmp_1.bits[0] == 0 && tmp_1.bits[1] == 0
        && tmp_1.bits[2] == 0 && tmp_2.bits[0] == 0
        && tmp_2.bits[1] == 0 && tmp_2.bits[2] == 0){
            code = S21_COMPARISON_TRUE;
        } else {
            code = tmp_1.bits[0] == tmp_2.bits[0]
                && tmp_1.bits[1] == tmp_2.bits[1]
                && tmp_1.bits[2] == tmp_2.bits[2]
                && tmp_1.bits[3] == tmp_2.bits[3];
        }
    return code;
}