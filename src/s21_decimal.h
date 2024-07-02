#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h>

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

#endif