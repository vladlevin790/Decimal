#include "s21_div.h"

void s21_big_div(s21_big_decimal decimal1, s21_big_decimal decimal2,
                 s21_big_decimal *div_whole, s21_big_decimal *div_remainder) {
  s21_big_decimal whole = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};  
  s21_big_decimal remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};  

  if (s21_is_less_big(decimal1, decimal2, 0, 0)) {
    remainder = decimal1;
  } else if (!s21_is_full_equal_zero(decimal1.decimal[0]) ||
             !s21_is_full_equal_zero(decimal1.decimal[1])) {

    int left_1 = s21_get_count_full_digits(decimal1.decimal[1]) - 1;
    left_1 = left_1 == -1 ? s21_get_count_full_digits(decimal1.decimal[0]) - 1
                          : DECIMAL_MAX_BITS + left_1;

    while (left_1 >= 0) {
      remainder = s21_left_shift_big_decimal(remainder, 1);

      if (s21_get_bit(decimal1.decimal[left_1 / 128].bits[(left_1 % 128) / 32],
                      left_1 % 32)) {
        remainder.decimal[0].bits[0] =
            s21_set_bit(remainder.decimal[0].bits[0], 0);
      }

      if (s21_is_greater_or_equal_big(remainder, decimal2, 0, 0)) {
        remainder = s21_big_sub(remainder, decimal2);
        whole.decimal[left_1 / 128].bits[(left_1 % 128) / 32] = s21_set_bit(
            whole.decimal[left_1 / 128].bits[(left_1 % 128) / 32], left_1 % 32);
      }

      left_1--;
    }
  }

  *div_whole = whole;
  *div_remainder = remainder;
}
