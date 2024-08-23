#include "s21_decimal_helper.h"

void s21_decimal_equalize(s21_decimal value_1, s21_decimal value_2,
                          s21_big_decimal* big_value_1,
                          s21_big_decimal* big_value_2) {
  int exponent_1 = s21_get_decimal_exponent(value_1),
      exponent_2 = s21_get_decimal_exponent(value_2);

  s21_set_decimal_exponent(&value_1, 0);
  s21_set_decimal_exponent(&value_2, 0);

  s21_set_decimal_sign(&value_1, 0);
  s21_set_decimal_sign(&value_2, 0);

  big_value_1->decimal[0] = value_1;
  big_value_2->decimal[0] = value_2;

  if (exponent_1 > exponent_2) {
    *big_value_2 = s21_big_mul(
        *big_value_2, s21_get_big_decimal_ten_pow(exponent_1 - exponent_2));
  } else if (exponent_1 < exponent_2) {
    *big_value_1 = s21_big_mul(
        *big_value_1, s21_get_big_decimal_ten_pow(exponent_2 - exponent_1));
  }
}
