#ifndef S21_IS_LESS_H_
#define S21_IS_LESS_H_

#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2);

int s21_is_less_big(s21_big_decimal value_1, s21_big_decimal value_2,
                    int sign_1, int sign_2);

#endif
