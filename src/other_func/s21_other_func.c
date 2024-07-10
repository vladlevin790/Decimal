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

    float tmp = 0.0;
    s21_from_decimal_to_float(value, &tmp);
    int tmp_res = (int)tmp;
    s21_from_int_to_decimal(tmp_res, result);
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
    s21_add(value, tmp, *result);
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
    s21_decimal tmp = {0};
    s21_decimal tmp_sub = {0};
    s21_truncate(value, &tmp);
    s21_sub(value, tmp, &tmp_sub);
    for (int i = 0; i < 95; i++) {
      if (!(s21_get_bit)) {
        s21_decimal tmp_1 = {0};
        s21_from_int_to_decimal(1, &tmp_1);
        s21_sub(value, tmp_1, &value);
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
//     int result_code = 0;

//     if (result == s21_NULL || check_decimal(value)) {
//         result_code = 1;
//     } else {
//         clear_decimal(result);

//         int current_exponent = get_decimal_exponent(value);
//         set_decimal_exponent(&value, 0);

//         s21_decimal decimal_ten_div = get_new_decimal();
//         s21_from_int_to_decimal(10, &decimal_ten_div);

//         while (current_exponent > 0) {
//             s21_div(value, decimal_ten_div, &value);

//             current_exponent--;
//         }

//         *result = value;
//     }

//     return result_code;
// }