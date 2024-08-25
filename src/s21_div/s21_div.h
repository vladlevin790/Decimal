#ifndef S21_DIV_H_
#define S21_DIV_H_

#include <stdlib.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#define DECIMAL_MAX_BITS 128

int s21_div_handle(s21_big_decimal value_2l, s21_big_decimal res,
                   s21_big_decimal remainder, s21_decimal *result);
int s21_div_calc_fractional(s21_big_decimal *res, s21_big_decimal value_2l,
                            s21_big_decimal *remainder);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_big_div(s21_big_decimal decimal1, s21_big_decimal decimal2,
                 s21_big_decimal *div_whole, s21_big_decimal *div_remainder);

#endif