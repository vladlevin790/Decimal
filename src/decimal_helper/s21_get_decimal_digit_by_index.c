#include "s21_decimal_helper.h"

int s21_get_decimal_digit_by_index(s21_decimal decimal, int index) {
  
  int res = 0;
  
  if (index >= 0 && index < 97) {
  
  //if (index < 0 || index >= 96) {
  //  return 0;
  //}

  int bit_number = index / 32;
  int bit_index = index % 32;
  res = s21_get_bit(decimal.bits[bit_number], bit_index);
  }
  return res;
}
