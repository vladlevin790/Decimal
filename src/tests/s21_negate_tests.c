#include <check.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_negate_0) {
  s21_decimal decimal = s21_get_new_decimal();
  s21_decimal result = s21_get_new_decimal();
  int x = 65634235;
  s21_from_int_to_decimal(x, &decimal);
  s21_negate(decimal, &result);

  ck_assert_int_eq(0, s21_get_decimal_sign(decimal));
  ck_assert_int_eq(1, s21_get_decimal_sign(result));
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal decimal = s21_get_new_decimal();
  s21_decimal result = s21_get_new_decimal();
  int x = -65634235;
  s21_from_int_to_decimal(x, &decimal);
  s21_negate(decimal, &result);

  ck_assert_int_eq(1, s21_get_decimal_sign(decimal));
  ck_assert_int_eq(0, s21_get_decimal_sign(result));
}
END_TEST

Suite *s21_negate_tests(void) {
  Suite *s = suite_create("\033[1;35ms21_negate\033[0m\n");
  TCase *testCase = tcase_create("s21_test_negate");

  suite_add_tcase(s, testCase);
  tcase_add_test(testCase, test_negate_0);
  tcase_add_test(testCase, test_negate_1);

  return s;
}
