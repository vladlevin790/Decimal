#include "s21_decimal_helper.h"

s21_decimal s21_decimal_and(s21_decimal decimal1, s21_decimal decimal2) {
  s21_decimal result = s21_get_new_decimal();

  result.bits[0] = decimal1.bits[0] & decimal2.bits[0];
  result.bits[1] = decimal1.bits[1] & decimal2.bits[1];
  result.bits[2] = decimal1.bits[2] & decimal2.bits[2];
  result.bits[3] = decimal1.bits[3] & decimal2.bits[3];

  return result;
}
