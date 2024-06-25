#include "s21_decimal.h"
#include "s21_binary.h"

// @brief Получение знака десятичного числа
// @param s21_decimal decimal, в котором лежат bits
// @return 0 - положительное, 1 - отрицательное
int get_decimal_sign(s21_decimal decimal) {
    return s21_get_bit(decimal.bits[3], 31);
}

int get_decimal_exponent(s21_decimal decimal) {
    return s21_get_bits(decimal.bits[3], 24, 30);
}