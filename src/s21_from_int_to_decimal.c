#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_code = S21_DECIMAL_OK;

  if (dst == NULL) {
    return_code = CODE_CONVERTATION_ERROR;
  } else {
    s21_clear_decimal(dst);
    s21_set_decimal_sign(dst, src < 0);
    s21_set_decimal_exponent(dst, 0);

    if (src < 0 && src != -2147483648) {
      src = -src;
    }

    dst->bits[0] = src;
  }

  return return_code;
}
