#include "s21_decimal_helper.h"

s21_decimal s21_decimal_not(s21_decimal decimal) {
  s21_decimal result = s21_get_new_decimal();

  result.bits[0] = ~decimal.bits[0];
  result.bits[1] = ~decimal.bits[1];
  result.bits[2] = ~decimal.bits[2];
  result.bits[3] = ~decimal.bits[3];

  return result;
}
