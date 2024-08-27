#ifndef S21_FROM_FLOAT_TO_DECIMAL_H
#define S21_FROM_FLOAT_TO_DECIMAL_H

#include <math.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal* dst);
s21_decimal s21_parse_float_str_to_decimal(char* float_str, int exponent);
int s21_get_exponent_from_float_str(char* float_str);

#endif