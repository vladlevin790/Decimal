#include "s21_div.h"

int s21_div_handle(s21_big_decimal value_2, s21_big_decimal whole,
                   s21_big_decimal remainder, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  int power1 = s21_div_calc_fractional(&whole, value_2, &remainder);

  s21_big_decimal second_remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};

  int power2 = s21_div_calc_fractional(&second_remainder, value_2, &remainder);
  s21_set_decimal_exponent(&second_remainder.decimal[0], power2);
  whole = s21_round_banking(whole.decimal[0], second_remainder.decimal[0]);

  if (!s21_is_full_equal_zero(whole.decimal[0])) {
    s21_set_decimal_exponent(&whole.decimal[0], power1);
    whole.decimal[0] = s21_remove_useless_zeros(whole.decimal[0]);
  }

  if (!s21_is_full_equal_zero(whole.decimal[1]) ||
      s21_check_decimal(whole.decimal[0]) ||
      s21_get_range_bits(whole.decimal[0].bits[3], 0, 15) != 0 ||
      s21_get_range_bits(whole.decimal[0].bits[3], 24, 30) != 0) {
    result_code = 1;
  } else {
    *result = whole.decimal[0];
  }

  return result_code;
}
