#ifndef S21_IS_GREATER_H_
#define S21_IS_GREATER_H_

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_big(s21_big_decimal value_1, s21_big_decimal value_2,
                       int sign_1, int sign_2);

#endif