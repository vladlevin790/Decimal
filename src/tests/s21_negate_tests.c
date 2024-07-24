#include <check.h>

#include "../other_func/s21_other_func.h"
#include "../s21_decimal.h"

START_TEST(test_negate_0) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  int x = 65634235;
  s21_from_int_to_decimal(x, &decimal);
  s21_negate(decimal, &result);

  ck_assert_int_eq(0, get_decimal_sign(decimal));
  ck_assert_int_eq(1, get_decimal_sign(result));
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  int x = -65634235;
  s21_from_int_to_decimal(x, &decimal);
  s21_negate(decimal, &result);

  ck_assert_int_eq(1, get_decimal_sign(decimal));
  ck_assert_int_eq(0, get_decimal_sign(result));
}
END_TEST

TCase *s21_negate_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_negate_0);
  tcase_add_test(test_cases, test_negate_1);

  return test_cases;
}
