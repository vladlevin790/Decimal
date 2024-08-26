#include "s21_other_func.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  //int result_code = 0;
  int result_code = 1;
  
  if (result != NULL && !s21_check_decimal(value)) {
  //if (result == NULL || s21_check_decimal(value)) {
  //  result_code = 1;
  //} else {
    result_code = 0;
    s21_clear_decimal(result);
    if (s21_get_decimal_exponent(value)) {
      if (s21_get_decimal_sign(value)) {
        s21_truncate(value, &value);
        s21_add(value, s21_get_decimal_with_int_value(-1), &value);
      } else {
        s21_truncate(value, &value);
      }
    }
    *result = value;
  }

  return result_code;
}
