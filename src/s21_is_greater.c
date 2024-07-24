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
    // Если второе число отрицательное, то возвращаем 1 - TRUE
    result_code = sign_2;
  } else {
    s21_big_decimal big_value_1 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    result_code = s21_is_greater_big(big_value_1, big_value_2, sign_1, sign_2);

    // 12345000000000
    // 0.123456789
  }

  return result_code;
}

int s21_is_greater_big(s21_big_decimal value_1, s21_big_decimal value_2,
                       int sign_1, int sign_2) {
  int is_greater = -1;

  for (int i = 255; i >= 0 && is_greater == -1; i--) {
    int curr_decimal = i / 128;
    int curr_bit = (i % 128) / 32;
    int bit_index = i % 32;

    int bit_1 =
        s21_get_bit(value_1.decimal[curr_decimal].bits[curr_bit], bit_index);
    int bit_2 =
        s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], bit_index);

    if (bit_1 != bit_2) {
      is_greater = (sign_2 && bit_1 < bit_2) || (!sign_1 && bit_1 > bit_2);
    }
  }

  if (is_greater == -1) {
    is_greater = 0;
  }

  return is_greater;
}