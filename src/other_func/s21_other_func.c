#include "s21_other_func.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int result_code = 0;

  if (result == s21_NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);

    *result = value;
    set_decimal_sign(result, ~(get_decimal_sign(value)));
  }
  return result_code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int result_code = 0;

    if (result == s21_NULL || check_decimal(value)) {
        result_code = 1;
    } else {
        clear_decimal(result);

        int current_exponent = get_decimal_exponent(value);
        set_decimal_exponent(&value, 0);

        s21_decimal decimal_ten_div = get_new_decimal();
        s21_from_int_to_decimal(10, &decimal_ten_div);

        while (current_exponent > 0) {
            s21_div(value, decimal_ten_div, &value);

            current_exponent--;
        }

        *result = value;
    }

    return result_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int result_code = 0;
  if (result == s21_NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);
    s21_decimal tmp = {0};
    s21_from_float_to_decimal(0.5, &tmp);
    s21_add(value, tmp, result);
    s21_truncate(*result, result);
  }
  return result_code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int result_code = 0;

  if (result == s21_NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);

    s21_decimal tmp = get_new_decimal();
    s21_decimal tmp_sub = get_new_decimal();;

    result_code = s21_truncate(value, &tmp);
    if (result_code == 0) {
      result_code = s21_sub(value, tmp, &tmp_sub);
    }

    for (int i = 0; i < 96 && result_code == 0; i++) {
      if (get_decimal_digit_by_index(tmp_sub, i)) {
        s21_sub(value, get_decimal_with_int_value(1), &value);
        break;
      }
    }
    *result = value;
  }
  return result_code;
}

// #include "s21_decimal.h"
// #include "decimal_helper/s21_decimal_helper.h"

// int s21_truncate(s21_decimal value, s21_decimal *result) {

// }
