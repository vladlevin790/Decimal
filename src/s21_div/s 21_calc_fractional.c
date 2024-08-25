#include "s21_div.h"

int s21_div_calc_fractional(s21_big_decimal *result, s21_big_decimal value_2l,
                            s21_big_decimal *remainder) {
  int exponent = 0;

  s21_big_decimal ten_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};

  int is_end = 0;
  while ((!s21_is_full_equal_zero(remainder->decimal[0]) ||
          !s21_is_full_equal_zero(remainder->decimal[1])) &&
         exponent < 28 && !is_end) {
    s21_big_decimal prev_result = *result;
    s21_big_decimal prev_remainder = *remainder;
    *result = s21_big_mul(*result, ten_decimal);
    *remainder = s21_big_mul(*remainder, ten_decimal);
    s21_big_decimal tmp_div_whole = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_div(*remainder, value_2l, &tmp_div_whole, remainder);
    if (s21_check_decimal(result->decimal[0]) ||
        s21_get_range_bits(result->decimal[0].bits[3], 0, 15) != 0 ||
        s21_get_range_bits(result->decimal[0].bits[3], 24, 30) != 0) {
      *result = prev_result;
      *remainder = prev_remainder;
      is_end = 1;
    } else {
      exponent++;
    }
  }
  return exponent;
}