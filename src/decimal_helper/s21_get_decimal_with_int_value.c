#include "s21_decimal_helper.h"

s21_decimal s21_get_decimal_with_int_value(int value) {
  s21_decimal decimal = s21_get_new_decimal();

  s21_from_int_to_decimal(value, &decimal);

  return decimal;
}
