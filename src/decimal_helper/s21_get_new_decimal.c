#include "s21_decimal_helper.h"

s21_decimal s21_get_new_decimal() {
  s21_decimal decimal = {0};
  s21_clear_decimal(&decimal);

  return decimal;
}
