#include "s21_div.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else if (s21_is_equal(value_2, s21_get_decimal_with_int_value(0))) {
    result_code = ERROR_DIVISION_BY_ZERO;
  } else {
    *result = s21_get_new_decimal();
    int sign1 = s21_get_decimal_sign(value_1),
        sign2 = s21_get_decimal_sign(value_2);

    s21_big_decimal big_value_1 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    s21_big_decimal div_remainder = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal div_whole = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};

    
    s21_big_div(big_value_1, big_value_2, &div_whole, &div_remainder);

    if (div_whole.decimal[0].bits[3] != 0 ||
        !s21_is_full_equal_zero(div_whole.decimal[1])) {
      if (sign1 != sign2) {
        result_code = ERROR_UNDERFLOW;
      } else {
        result_code = ERROR_OVERFLOW;
      }
    } else {
    
      result_code =
          s21_div_handle(big_value_2, div_whole, div_remainder, result);

      if (result_code == 0 && sign1 != sign2) {
        s21_set_decimal_sign(result, 1);
      } else if (result_code == 1 && sign1 != sign2) {
        result_code = 2;
      }
    }
  }

  return result_code;
}

