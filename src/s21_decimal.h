#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

typedef struct s21_decimal {
    int bits[4];
} s21_decimal;

typedef enum s21_decimal_sign {
    POSITIVE = 0,
    NEGATIVE = 1
} s21_decimal_sign;

#endif