#include "s21_is_grather_or_equal.h"

int s21_is_greater_or_equal_big(s21_big_decimal value_1,
                                s21_big_decimal value_2, int sign_1,
                                int sign_2) {
  return !s21_is_less_big(value_1, value_2, sign_1, sign_2);
}
