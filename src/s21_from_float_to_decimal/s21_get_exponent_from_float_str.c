#include "s21_from_float_to_decimal.h"

int s21_get_exponent_from_float_str(char* float_str) {
  int exponent = 0;
  if (float_str != NULL) {
    char* p = float_str;
    while (*p && *p != 'e') {
      p++;
    }

    if (*p) {
      p++;
    }

    int sign = *p == '-';
    p++;

    while (*p >= '0' && *p <= '9') {
      exponent = exponent * 10 + (*p - '0');
      p++;
    }
    if (sign) {
      exponent = -exponent;
    }
  }
  return exponent;
}