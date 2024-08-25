#include "s21_mul.h"


int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else {
    int result_sign =
        s21_get_decimal_sign(value_1) != s21_get_decimal_sign(value_2);
    int exponent_1 = s21_get_decimal_exponent(value_1),
        exponent_2 = s21_get_decimal_exponent(value_2);

    s21_set_decimal_sign(&value_1, 0);
    s21_set_decimal_sign(&value_2, 0);

    s21_set_decimal_exponent(&value_1, 0);
    s21_set_decimal_exponent(&value_2, 0);

    s21_big_decimal big_value_1 = {{value_1, s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {{value_2, s21_get_new_decimal()}};

    s21_big_decimal big_result = s21_big_mul(big_value_1, big_value_2);

    int count_out_bounds = s21_count_digits_out_bounds(big_result);
    int result_exponent = exponent_1 + exponent_2 - count_out_bounds;

    if (result_exponent < 0) {
      result_code = ERROR_OVERFLOW;
    } else {
      result_code =
          s21_mul_handle(big_result, result_exponent, count_out_bounds, result);
    }

    if (result_code == 0) {
      s21_set_decimal_sign(result, result_sign);
    } else if (result_code == 1 && result_sign == 1) {
      result_code = ERROR_UNDERFLOW;
    }
  }

  return result_code;
}
