#include <math.h>

#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_code = S21_DECIMAL_OK;

  if (dst == NULL || s21_check_decimal(src)) {
    result_code = CODE_CONVERTATION_ERROR;
  } else {
    *dst = 0;

    for (int i = 0; i < 96; i++) {
      *dst += s21_get_decimal_digit_by_index(src, i) * pow(2, i);
    }

    *dst /= pow(10, s21_get_decimal_exponent(src));
    if (*dst != 0 && s21_get_decimal_sign(src)) {
      *dst *= -1;
    }
  }

  return result_code;
}