#include "s21_sub.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else {
    int sign_1 = s21_get_decimal_sign(value_1),
        sign_2 = s21_get_decimal_sign(value_2);

    if (sign_1 == 0 && sign_2 == 0) {
      if (s21_is_less(value_1, value_2)) {
        result_code = s21_sub_handle(value_2, value_1, result);
        result_code =
            result_code == ERROR_OVERFLOW ? ERROR_UNDERFLOW : result_code;
        s21_set_decimal_sign(result, 1);
      } else {
        result_code = s21_sub_handle(value_1, value_2, result);
      }
    } else if (sign_1 == 0 && sign_2 == 1) {
      s21_set_decimal_sign(&value_2, 0);
      result_code = s21_add(value_2, value_1, result);
    } else if (sign_1 == 1 && sign_2 == 0) {
      s21_set_decimal_sign(&value_1, 0);
      result_code = s21_add(value_1, value_2, result);

      result_code =
          result_code == ERROR_OVERFLOW ? ERROR_UNDERFLOW : result_code;
      s21_set_decimal_sign(result, 1);
    } else if (sign_1 == 1 && sign_2 == 1) {
      s21_set_decimal_sign(&value_1, 0);
      s21_set_decimal_sign(&value_2, 0);

      if (s21_is_less_or_equal(value_1, value_2)) {  // 3 - 5
        result_code = s21_sub_handle(value_2, value_1, result);
      } else {
        result_code = s21_sub_handle(value_1, value_2, result);
        s21_set_decimal_sign(result, 1);
        result_code =
            result_code == ERROR_OVERFLOW ? ERROR_UNDERFLOW : result_code;
      }
    }
  }

  return result_code;
}

