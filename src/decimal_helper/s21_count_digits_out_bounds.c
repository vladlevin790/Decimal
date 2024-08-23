#include "s21_decimal_helper.h"

int s21_count_digits_out_bounds(s21_big_decimal value) {
  int count = 0;

  s21_big_decimal ten_big_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};

  while (!s21_is_full_equal_zero(value.decimal[1]) ||
         value.decimal[0].bits[3] != 0) {
    s21_big_decimal tmp = {{s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_div(value, ten_big_decimal, &value, &tmp);
    count++;
  }

  return count;
}
