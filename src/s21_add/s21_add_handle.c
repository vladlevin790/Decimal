#include "s21_add.h"

int s21_add_handle(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  int exponent_1 = s21_get_decimal_exponent(value_1),
      exponent_2 = s21_get_decimal_exponent(value_2);
  int result_exponent = exponent_1 > exponent_2 ? exponent_1 : exponent_2;

  s21_big_decimal big_value_1 = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};
  s21_big_decimal big_value_2 = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};
  s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

  s21_big_decimal big_result = s21_big_add(big_value_1, big_value_2);

  int count_out_bounds = s21_count_digits_out_bounds(big_result);
  result_exponent -= count_out_bounds;

  if (result_exponent < 0) {
    result_code = ERROR_OVERFLOW;
  } else {
    s21_big_decimal div_whole = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal div_remainder = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_div(big_result, s21_get_big_decimal_ten_pow(count_out_bounds),
                &div_whole, &div_remainder);

    s21_set_decimal_exponent(&div_remainder.decimal[0], count_out_bounds);
    div_whole =
        s21_round_banking(div_whole.decimal[0], div_remainder.decimal[0]);

    if (!s21_is_full_equal_zero(div_whole.decimal[1]) ||
        div_whole.decimal[0].bits[3] != 0) {
      result_code = ERROR_OVERFLOW;
    } else {
      *result = div_whole.decimal[0];
      s21_set_decimal_exponent(result, result_exponent);
    }
  }

  return result_code;
}
