#include "s21_decimal_helper.h"

int s21_get_decimal_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[3], 31);
}
