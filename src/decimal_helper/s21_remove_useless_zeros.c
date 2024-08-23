#include "s21_decimal_helper.h"

s21_decimal s21_remove_useless_zeros(s21_decimal value) {
  s21_decimal result = value;

  int exponent = s21_get_decimal_exponent(value);
  int sign = s21_get_decimal_sign(value);

  s21_big_decimal ten_big_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};

  if (exponent > 0 && !s21_check_decimal(value)) {
    s21_decimal div_integral = value;

    s21_set_decimal_exponent(&div_integral, 0);
    s21_set_decimal_sign(&div_integral, 0);

    int has_useless_zeros = 1;
    while (has_useless_zeros && exponent > 0) {
      s21_big_decimal tmp_div_integral = {
          {div_integral, s21_get_new_decimal()}};
      s21_big_decimal tmp_div_remainder = {
          {s21_get_new_decimal(), s21_get_new_decimal()}};

      s21_big_div(tmp_div_integral, ten_big_decimal, &tmp_div_integral,
                  &tmp_div_remainder);

      div_integral = tmp_div_integral.decimal[0];
      s21_decimal div_remainder = tmp_div_remainder.decimal[0];

      if (s21_is_equal(div_remainder, s21_get_decimal_with_int_value(0))) {
        result = div_integral;
        exponent--;
      } else {
        has_useless_zeros = 0;
      }
    }

    s21_set_decimal_exponent(&result, exponent);
    s21_set_decimal_sign(&result, sign);
  }

  return result;
}
