#include "s21_decimal_helper.h"

s21_big_decimal s21_round_banking(s21_decimal integral,
                                  s21_decimal fractional) {
  s21_decimal half_one = s21_get_decimal_with_int_value(5);
  s21_set_decimal_exponent(&half_one, 1);

  s21_big_decimal big_one = {
      {s21_get_decimal_with_int_value(1), s21_get_new_decimal()}};
  s21_big_decimal big_integral = {{integral, s21_get_new_decimal()}};
  s21_big_decimal big_result = {{s21_get_new_decimal(), s21_get_new_decimal()}};

  if (s21_is_equal(fractional, half_one)) {
    if ((integral.bits[0] & 1) == 0) {
      big_result.decimal[0] = integral;
    } else {
      big_result = s21_big_add(big_integral, big_one);
    }
  } else if (s21_is_greater(fractional, half_one)) {
    big_result = s21_big_add(big_integral, big_one);
  } else {
    big_result.decimal[0] = integral;
  }

  return big_result;
}
