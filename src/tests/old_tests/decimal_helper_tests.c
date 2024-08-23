#include <check.h>

#include "../binary/s21_binary.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_0) {
  s21_decimal decimal = {0};
  decimal.bits[3] = s21_set_bit(decimal.bits[3], 31);

  ck_assert_int_eq(s21_get_decimal_sign(decimal), NEGATIVE);
}
END_TEST

START_TEST(test_1) {
  s21_decimal decimal = {0};
  decimal.bits[3] = s21_clear_bit(decimal.bits[3], 31);

  ck_assert_int_eq(s21_get_decimal_sign(decimal), POSITIVE);
}
END_TEST

START_TEST(test_2) {
  s21_decimal decimal = {0};

  ck_assert_int_eq(s21_get_decimal_sign(decimal), POSITIVE);
}
END_TEST

TCase *decimal_helper_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);

  return test_cases;
}
