#include "s21_decimal_helper.h"

s21_big_decimal s21_get_big_decimal_ten_pow(int pow) {
  s21_big_decimal big_decimal = {
      {s21_get_decimal_with_int_value(1), s21_get_new_decimal()}};

  for (int i = 0; i < pow; i++) {
    s21_big_decimal tmp_decimal = big_decimal;
    for (int j = 0; j < 9; j++) {
      big_decimal = s21_big_add(big_decimal, tmp_decimal);
    }
  }

  return big_decimal;
}

