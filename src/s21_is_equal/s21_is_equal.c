#include "s21_is_equal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result_code = TRUE;

  value_1 = s21_remove_useless_zeros(value_1);
  value_2 = s21_remove_useless_zeros(value_2);

  int sign_1 = s21_get_decimal_sign(value_1),
      sign_2 = s21_get_decimal_sign(value_2);
  int exp_1 = s21_get_decimal_exponent(value_1),
      exp_2 = s21_get_decimal_exponent(value_2);

  if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 &&
      value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    result_code = TRUE;
  } else {
    result_code = value_1.bits[0] == value_2.bits[0] &&
                  value_1.bits[1] == value_2.bits[1] &&
                  value_1.bits[2] == value_2.bits[2] && sign_1 == sign_2 &&
                  exp_1 == exp_2;
  }

  return result_code;
}
