#include <math.h>

#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result_code = S21_DECIMAL_OK;

  if (dst == NULL || s21_check_decimal(src) || s21_check_int_range(src)) {
    result_code = CODE_CONVERTATION_ERROR;
  } else if (src.bits[1] != 0 || src.bits[2] != 0) {
    result_code = CODE_CONVERTATION_ERROR;
  } else {
    s21_decimal truncated_decimal = s21_get_new_decimal();
    s21_truncate(src, &truncated_decimal);

    *dst = 0;
    for (int i = 0; i < 32; i++) {
      *dst += s21_get_decimal_digit_by_index(truncated_decimal, i) * pow(2, i);
    }

    if (s21_get_decimal_sign(src) && *dst != -2147483648) {
      *dst *= -1;
    }
  }

  return result_code;
}