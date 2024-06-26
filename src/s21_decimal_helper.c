#include "s21_decimal_helper.h"

int get_decimal_sign(s21_decimal decimal) {
    return s21_get_bit(decimal.bits[3], 31);
}

int get_decimal_exponent(s21_decimal decimal) {
    return s21_get_range_bits(decimal.bits[3], 16, 23);
}