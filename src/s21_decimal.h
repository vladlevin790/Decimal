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


// typedef struct s21_bigdecimal {
//     int bits[8];
// } s21_bigdecimal;

typedef enum s21_decimal_sign {
    POSITIVE = 0,
    NEGATIVE = 1
} s21_decimal_sign;

enum s21_arithmetic_code_error {
    S21_DECIMAL_OK = 0,
    // CODE_CONVERTATION_ERROR = 1,
    FALSE = 0,
    // TRUE = 1,
    ERROR_OVERFLOW = 1, //  the number is too large or equal to infinity
    ERROR_UNDERFLOW = 2, // the number is too small or equal to negative infinity;
    ERROR_DIVISION_BY_ZERO = 3
};
// #define S21_DECIMAL_OK 0
// #define S21_DECIMAL_OVERFLOW 1
// #define S21_DECIMAL_UNDERFLOW 2
// #define S21_DECIMAL_DIVISION_BY_ZERO 3


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