#ifndef S21_MUL_H_
#define S21_MUL_H_

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_mul_handle(s21_big_decimal big_result, int result_exponent,
                   int count_out_bounds, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_big_decimal s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2);

#endif
