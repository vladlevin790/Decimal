#include "s21_decimal_helper.h"

int s21_check_decimal(s21_decimal decimal) {
  int result_code = 0;

  int exponent = s21_get_decimal_exponent(decimal);
  if (exponent < 0 || exponent > 28) {
    result_code = 1;
  }

  return result_code;
}
