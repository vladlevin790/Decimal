#include "s21_sub.h"

s21_big_decimal s21_big_sub(s21_big_decimal decimal1,
                            s21_big_decimal decimal2) {
  s21_big_decimal one = {
      {s21_get_decimal_with_int_value(1), s21_get_new_decimal()}};

  decimal2.decimal[0] = s21_decimal_not(decimal2.decimal[0]);
  decimal2.decimal[1] = s21_decimal_not(decimal2.decimal[1]);

  decimal1 = s21_big_add(decimal1, decimal2);
  decimal1 = s21_big_add(decimal1, one);

  return decimal1;
}
