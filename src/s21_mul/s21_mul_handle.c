#include "s21_mul.h"

int s21_mul_handle(s21_big_decimal big_result, int result_exponent,
                   int count_out_bounds, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;
  s21_big_decimal ten_big_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};
  s21_big_decimal tmp = {{s21_get_new_decimal(), s21_get_new_decimal()}};
  if (result_exponent > 28) {
    count_out_bounds = result_exponent - 28 + count_out_bounds;
    result_exponent = 28;
  }
  while (count_out_bounds > 17) {
    s21_big_div(big_result, ten_big_decimal, &big_result, &tmp);
    count_out_bounds--;
  }

  s21_big_decimal div_remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};
  s21_big_decimal big_ten_pow = s21_get_big_decimal_ten_pow(count_out_bounds);
  s21_big_div(big_result, big_ten_pow, &big_result, &div_remainder);
  s21_set_decimal_exponent(&div_remainder.decimal[0], count_out_bounds);
  big_result =
      s21_round_banking(big_result.decimal[0], div_remainder.decimal[0]);
  if (!s21_is_full_equal_zero(big_result.decimal[1]) ||
      big_result.decimal[0].bits[3] != 0) {
    result_code = ERROR_OVERFLOW;
  } else {
    *result = big_result.decimal[0];
    s21_set_decimal_exponent(result, result_exponent);
    if (s21_is_equal(*result, s21_get_decimal_with_int_value(0)) &&
        s21_is_equal(div_remainder.decimal[0],
                     s21_get_decimal_with_int_value(0))) {
      *result = s21_remove_useless_zeros(*result);
    }
  }

  return result_code;
}