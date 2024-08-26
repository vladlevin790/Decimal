#ifndef S21_ADD_H_
#define S21_ADD_H_

#include <stdio.h>
#include "../binary/s21_binary_operations.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_big_decimal s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2);

#endif
