#ifndef S21_IS_GREATER_OR_EQUAL_H_
#define S21_IS_GREATER_OR_EQUAL_H_

#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal_big(s21_big_decimal value_1,
                                s21_big_decimal value_2, int sign_1,
                                int sign_2);

#endif