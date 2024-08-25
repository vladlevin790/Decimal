#include "s21_is_less.h"

int s21_is_less_big(s21_big_decimal value_1, s21_big_decimal value_2,
                    int sign_1, int sign_2) {
  return !s21_is_greater_big(value_1, value_2, sign_1, sign_2) &&
         !s21_is_equal_big(value_1, value_2, sign_1, sign_2);
}
