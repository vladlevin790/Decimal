
#include "helper_tests.h"

#include <check.h>
#include <limits.h>

void check_decimal_bits(s21_decimal result, s21_decimal expected) {
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}