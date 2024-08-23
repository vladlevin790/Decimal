#include "s21_decimal_helper.h"

int s21_get_count_full_digits(s21_decimal decimal) {
  int count = 0;

  for (int i = 127; i >= 0 && count == 0; i--) {
    if (s21_get_bit(decimal.bits[i / 32], i % 32)) {
      count = i + 1;
    }
  }

  return count;
}
