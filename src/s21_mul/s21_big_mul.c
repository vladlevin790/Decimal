#include "s21_mul.h"

s21_big_decimal s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal result = {{s21_get_new_decimal(), s21_get_new_decimal()}};

  int max_index = s21_get_count_full_digits(value_2.decimal[1]) - 1;
  max_index = max_index == -1
                  ? s21_get_count_full_digits(value_2.decimal[0]) - 1
                  : DECIMAL_MAX_BITS + max_index;

  for (int i = 0; i <= max_index; i++) {
    int curr_decimal = i / 128;
    int curr_bit = (i % 128) / 32;
    int curr_index = i % 32;

    if (s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], curr_index)) {
      result = s21_big_add(result, value_1);
    }
    value_1 = s21_left_shift_big_decimal(value_1, 1);
  }

  return result;
}