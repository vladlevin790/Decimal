#include "s21_decimal_helper.h"

s21_big_decimal s21_left_shift_big_decimal(s21_big_decimal value,
                                           int count_shift) {
  while (count_shift > 0) {
    int is_set_one = 0;
    for (int i = 0; i < 8; i++) {
      int decimal_index = i / 4;

      int tmp_is_set_one =
          s21_get_bit(value.decimal[decimal_index].bits[i % 4], 31);

      value.decimal[decimal_index].bits[i % 4] =
          (unsigned int)(value.decimal[decimal_index].bits[i % 4]) << 1;
      if (is_set_one == 1) {
        value.decimal[decimal_index].bits[i % 4] =
            s21_set_bit(value.decimal[decimal_index].bits[i % 4], 0);
      }

      is_set_one = tmp_is_set_one;
    }

    count_shift--;
  }

  return value;
}
