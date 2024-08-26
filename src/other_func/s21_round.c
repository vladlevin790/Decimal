#include "s21_other_func.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  //int result_code = 0;
  int result_code = 1;
  
  if (result != NULL && !s21_check_decimal(value)) {
  //if (result == NULL || s21_check_decimal(value)) {
  //  result_code = 1;
  //} else if (!s21_get_decimal_sign(value)) {
      result_code = 0;
  if (!s21_get_decimal_sign(value)) {
    s21_clear_decimal(result);
    s21_decimal tmp = {{5, 0, 0, 65536}};
    s21_add(value, tmp, result);
    s21_truncate(*result, result);
  } else {
    s21_clear_decimal(result);
    s21_decimal tmp = {{5, 0, 0, -2147418112}};
    s21_add(value, tmp, result);
    s21_truncate(*result, result);
  }
 }
  return result_code;
}
