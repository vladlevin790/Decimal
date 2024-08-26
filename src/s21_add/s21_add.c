#include "s21_add.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else {
    int sign_1 = s21_get_decimal_sign(value_1),
        sign_2 = s21_get_decimal_sign(value_2);

    // + +    a + b    5 + 3
    // + -    a - b    5 - 3
    // - +    b - a    -5 + 3
    // - -    a + b
    if (sign_1 == 0 && sign_2 == 0) {
      result_code = s21_add_handle(value_1, value_2, result);
    } else if (sign_1 == 0 && sign_2 == 1) {
      s21_set_decimal_sign(&value_2, 0);
      result_code = s21_sub(value_1, value_2, result);
    } else if (sign_1 == 1 && sign_2 == 0) {
      s21_set_decimal_sign(&value_1, 0);
      result_code = s21_sub(value_2, value_1, result);
    } else if (sign_1 == 1 && sign_2 == 1) {
      s21_set_decimal_sign(&value_1, 0);
      s21_set_decimal_sign(&value_2, 0);

      result_code = s21_add_handle(value_1, value_2, result);
      if (result_code == S21_DECIMAL_OK) {
        s21_set_decimal_sign(result, 1);
      } else if (result_code == ERROR_OVERFLOW) {
        result_code = ERROR_UNDERFLOW;
      }
    }
  }

  return result_code;
}
