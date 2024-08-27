#include "s21_from_float_to_decimal.h"

s21_decimal s21_parse_float_str_to_decimal(char* float_str, int exponent) {
  s21_decimal decimal = s21_get_new_decimal();
  s21_decimal decimal_tmp = s21_get_new_decimal();

  int is_fractional = 0, curr_fractional_pow = 1, count_digits = 7,
      count_writed_digits = 0;
  while (*float_str && *float_str != 'e' && count_digits > 0) {
    if (*float_str >= '0' && *float_str <= '9' &&
        (*float_str != '0' || count_digits < 7)) {
      if (is_fractional && *float_str == '0') {
        curr_fractional_pow++;
      } else {
        s21_clear_decimal(&decimal_tmp);

        s21_from_int_to_decimal(pow(10, curr_fractional_pow), &decimal_tmp);
        s21_mul(decimal, decimal_tmp, &decimal);

        s21_from_int_to_decimal(*float_str - '0', &decimal_tmp);
        s21_add(decimal, decimal_tmp, &decimal);

        count_writed_digits += curr_fractional_pow;
        curr_fractional_pow = 1;
      }
      count_digits--;
    } else if (*float_str == '.') {
      is_fractional = 1;
    }

    float_str++;
  }

  while (count_writed_digits < exponent + 1) {
    s21_clear_decimal(&decimal_tmp);

    s21_from_int_to_decimal(10, &decimal_tmp);
    s21_mul(decimal, decimal_tmp, &decimal);

    count_writed_digits++;
  }

  if (exponent < 0) {
    exponent = -exponent;
    s21_set_decimal_exponent(&decimal, exponent + (count_writed_digits - 1));
  } else {
    s21_set_decimal_exponent(&decimal, count_writed_digits - (exponent + 1));
  }

  return decimal;
}