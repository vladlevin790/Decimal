#include "s21_is_greater.h"

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
