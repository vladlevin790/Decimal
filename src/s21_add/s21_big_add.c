#include "../binary/s21_binary_operations.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

s21_big_decimal s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal carry = {{s21_get_new_decimal(), s21_get_new_decimal()}};

  while (!s21_is_full_equal_zero(value_2.decimal[0]) ||
         !s21_is_full_equal_zero(value_2.decimal[1])) {
    carry.decimal[0] = s21_decimal_and(value_1.decimal[0], value_2.decimal[0]);
    carry.decimal[1] = s21_decimal_and(value_1.decimal[1], value_2.decimal[1]);

    value_1.decimal[0] =
        s21_decimal_xor(value_1.decimal[0], value_2.decimal[0]);
    value_1.decimal[1] =
        s21_decimal_xor(value_1.decimal[1], value_2.decimal[1]);

    value_2 = s21_left_shift_big_decimal(carry, 1);
  }

  return value_1;
}
