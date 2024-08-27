#include "s21_is_equal.h"

int s21_is_equal_big(s21_big_decimal value_1, s21_big_decimal value_2,
                     int sign_1, int sign_2) {
  int result_code = TRUE;

  for (int i = 255; i >= 0 && result_code; i--) {
    int curr_decimal = i / 128;
    int curr_bit = (i % 128) / 32;
    int bit_index = i % 32;

    int bit_1 =
        s21_get_bit(value_1.decimal[curr_decimal].bits[curr_bit], bit_index);
    int bit_2 =
        s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], bit_index);

    if (bit_1 != bit_2) {
      result_code = FALSE;
    }
  }

  if (result_code == TRUE &&
      (!s21_is_equal(value_1.decimal[0], s21_get_decimal_with_int_value(0)) ||
       !s21_is_equal(value_1.decimal[1], s21_get_decimal_with_int_value(0))) &&
      (!s21_is_equal(value_2.decimal[0], s21_get_decimal_with_int_value(0)) ||
       !s21_is_equal(value_2.decimal[1], s21_get_decimal_with_int_value(0)))) {
    result_code = sign_1 == sign_2;
  }

  return result_code;
}
