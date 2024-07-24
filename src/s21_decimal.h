#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h>

#define DECIMAL_MAX_BITS 128

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef enum s21_comparison_result {
  S21_COMPARISON_TRUE = 1,
  S21_COMPARISON_FALSE = 0,
} s21_comparison_result;

typedef struct s21_big_decimal {
  s21_decimal decimal[2];
} s21_big_decimal;

typedef enum s21_decimal_sign { POSITIVE = 0, NEGATIVE = 1 } s21_decimal_sign;

enum s21_arithmetic_code_error {
  S21_DECIMAL_OK = 0,
  CODE_CONVERTATION_ERROR = 1,
  FALSE = 0,
  TRUE = 1,
  ERROR_OVERFLOW = 1,  //  the number is too large or equal to infinity
  ERROR_UNDERFLOW =
      2,  // the number is too small or equal to negative infinity;
  ERROR_DIVISION_BY_ZERO = 3,
  S21_DECIMAL_ERROR = 4
};

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

// compares
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_full_equal_zero(s21_decimal value_1);
int s21_is_equal_big(s21_big_decimal value_1, s21_big_decimal value_2,
                     int sign_1, int sign_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_big(s21_big_decimal value_1, s21_big_decimal value_2,
                       int sign_1, int sign_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal_big(s21_big_decimal value_1,
                                s21_big_decimal value_2, int sign_1,
                                int sign_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_big(s21_big_decimal value_1, s21_big_decimal value_2,
                    int sign_1, int sign_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// arithmetic
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_big_decimal s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_big_decimal s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_big_decimal s21_big_mul(s21_big_decimal big_value_1,
                            s21_big_decimal big_value_2);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_big_div(s21_big_decimal decimal1, s21_big_decimal decimal2,
                 s21_big_decimal *div_whole, s21_big_decimal *div_remainder);

#endif