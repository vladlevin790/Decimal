#ifndef S21_COMPARISON_H
#define S21_COMPARISON_H

#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

typedef enum s21_comparison_result{
    S21_COMPARISON_TRUE = 1,
    S21_COMPARISON_FALSE = 0,
} s21_comparison_result;

#endif