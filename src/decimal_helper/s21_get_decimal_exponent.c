#include "s21_decimal_helper.h"

int s21_get_decimal_exponent(s21_decimal decimal) {
  return s21_get_range_bits(decimal.bits[3], 16, 23);
}
