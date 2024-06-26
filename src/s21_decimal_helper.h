#ifndef S21_DECIMAL_HELPER_H_
#define S21_DECIMAL_HELPER_H_

#include "s21_decimal.h"
#include "s21_binary.h"

// @brief Получение знака десятичного числа
// @param s21_decimal decimal, в котором лежат bits
// @return 0 - положительное, 1 - отрицательное
int get_decimal_sign(s21_decimal decimal);

// @brief Получение степени 10
// @param s21_decimal decimal, в котором лежат bits
// @return Степень 10
int get_decimal_exponent(s21_decimal decimal);

#endif