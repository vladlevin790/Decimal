#include "s21_is_equal.h"

int s21_is_full_equal_zero(s21_decimal value_1) {
  return value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 &&
         value_1.bits[3] == 0;
}