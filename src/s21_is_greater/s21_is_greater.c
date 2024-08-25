#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result_code = FALSE;

  int sign_1 = s21_get_decimal_sign(value_1),
      sign_2 = s21_get_decimal_sign(value_2);

  value_1 = s21_remove_useless_zeros(value_1);
  value_2 = s21_remove_useless_zeros(value_2);

  if (sign_1 != sign_2 &&
      !s21_is_equal(value_1, s21_get_decimal_with_int_value(0)) &&
      !s21_is_equal(value_2, s21_get_decimal_with_int_value(0))) {
    
    result_code = sign_2;
  } else {
    s21_big_decimal big_value_1 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    result_code = s21_is_greater_big(big_value_1, big_value_2, sign_1, sign_2);

  }

  return result_code;
}
