#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int result_code = 1;

  if (result != NULL && !s21_check_decimal(value)) {
  //if (result == NULL || s21_check_decimal(value)) {
  //  result_code = 1;
  //} else {
    result_code = 0;
    s21_clear_decimal(result);

    *result = value;
    s21_set_decimal_sign(result, !(s21_get_decimal_sign(value)));
  }

  return result_code;
}
