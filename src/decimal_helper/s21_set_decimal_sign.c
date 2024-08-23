#include "s21_decimal_helper.h"

void s21_set_decimal_sign(s21_decimal* decimal, int sign) {
  if (sign == 0) {
    decimal->bits[3] = s21_clear_bit(decimal->bits[3], 31);
  } else {
    decimal->bits[3] = s21_set_bit(decimal->bits[3], 31);
  }
}
