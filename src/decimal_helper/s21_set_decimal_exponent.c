#include "s21_decimal_helper.h"

void s21_set_decimal_exponent(s21_decimal* decimal, int exponent) {
  if (exponent >= 0 && exponent < 29) {
  
  //if (exponent < 0 || exponent > 28) {
  //  return;
  //}

  for (int i = 0; i < 8; i++) {
    if (s21_get_bit(exponent, i)) {
      decimal->bits[3] = s21_set_bit(decimal->bits[3], 16 + i);
    } else {
      decimal->bits[3] = s21_clear_bit(decimal->bits[3], 16 + i);
    }
  }
  }
}
