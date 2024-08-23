#include "s21_decimal_helper.h"

int s21_check_int_range(s21_decimal decimal) {
  int is_error = 0;

  s21_decimal truncated_decimal = {0};
  s21_truncate(decimal, &truncated_decimal);

  s21_decimal min_decimal_for_int = {0};
  min_decimal_for_int.bits[0] = 0X80000000;  // 1000...000
  s21_set_decimal_sign(&min_decimal_for_int, 1);

  s21_decimal max_decimal_for_int = {0};
  max_decimal_for_int.bits[0] = 0X7FFFFFFF;  // 0111...111
  s21_set_decimal_sign(&max_decimal_for_int, 0);

  if (s21_is_greater(truncated_decimal, max_decimal_for_int) ||
      s21_is_less(truncated_decimal, min_decimal_for_int)) {
    is_error = 1;
  }

  return is_error;
}
