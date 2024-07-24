#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int result_code = 0;

  if (result == NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);

    *result = value;
    set_decimal_sign(result, !(get_decimal_sign(value)));
  }
  return result_code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int result_code = 0;

  if (result == NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);
    int exponent = get_decimal_exponent(value);
    int sign = get_decimal_sign(value);
    set_decimal_exponent(&value, 0);
    set_decimal_sign(&value, 0);
    s21_big_decimal div_1 = {
        {get_decimal_with_int_value(10), get_new_decimal()}};
    s21_big_decimal big_value = {{value, get_new_decimal()}};
    s21_big_decimal rev_value = {{get_new_decimal(), get_new_decimal()}};
    s21_big_decimal big_result = big_value;
    while (exponent != 0) {
      s21_big_div(big_result, div_1, &big_result, &rev_value);
      exponent--;
    }
    *result = big_result.decimal[0];
    set_decimal_sign(result, sign);
    set_decimal_exponent(result, 0);
  }

  return result_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int result_code = 0;
  if (result == NULL || check_decimal(value)) {
    result_code = 1;
  } else if (!get_decimal_sign(value)) {
    clear_decimal(result);
    s21_decimal tmp = {{5, 0, 0, 65536}};
    s21_add(value, tmp, result);
    s21_truncate(*result, result);
  } else {
    clear_decimal(result);
    s21_decimal tmp = {{5, 0, 0, -2147418112}};
    s21_add(value, tmp, result);
    s21_truncate(*result, result);
  }
  return result_code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int result_code = 0;

  if (result == NULL || check_decimal(value)) {
    result_code = 1;
  } else {
    clear_decimal(result);
    if (get_decimal_exponent(value)) {
      if (get_decimal_sign(value)) {
        s21_truncate(value, &value);
        s21_add(value, get_decimal_with_int_value(-1), &value);
      } else {
        s21_truncate(value, &value);
      }
    }
    *result = value;
  }
  return result_code;
}