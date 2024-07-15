#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h> // TODO: убрать

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#define s21_NULL ((void*)0)

typedef struct s21_decimal {
    int bits[4];
} s21_decimal;

typedef enum s21_decimal_sign {
    POSITIVE = 0,
    NEGATIVE = 1
} s21_decimal_sign;


int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// compares
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// arithmetic
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif