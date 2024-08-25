#ifndef S21_SUB_H_
#define S21_SUB_H_

#include "../binary/s21_binary_operations.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_sub_handle(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_big_decimal s21_big_sub(s21_big_decimal decimal1,
                            s21_big_decimal decimal2);

#endif