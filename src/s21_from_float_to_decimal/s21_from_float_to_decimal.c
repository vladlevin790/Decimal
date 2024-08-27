#include "s21_from_float_to_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int result_code = S21_DECIMAL_OK;

  if (dst == NULL || isnan(src) || isinf(src) ||
      fabsf(src) > 79228162514264337593543950335.0f) {
    result_code = 1;
  } else if (fabsf(src) > 0 && fabsf(src) < 1e-28) {
    result_code = CODE_CONVERTATION_ERROR;
    *dst = s21_get_new_decimal();
  } else {
    s21_clear_decimal(dst);
    char float_str[64] = {0};
    sprintf(float_str, "%.6e", fabs(src));

    int exponent = s21_get_exponent_from_float_str(float_str);
    if (exponent < 0) {
      sprintf(float_str, "%.28f", src);
    }

    *dst = s21_parse_float_str_to_decimal(float_str, exponent);
    s21_set_decimal_sign(dst, signbit(src) != 0);
  }

  return result_code;
}
