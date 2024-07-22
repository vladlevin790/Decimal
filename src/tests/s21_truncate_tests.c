#include "../other_func/s21_other_func.h"
#include "../s21_decimal.h"
#include <check.h>

START_TEST(test_round_0) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = 65634.937884;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

START_TEST(test_truncate_1) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = -65634.937884;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = -65634.937884;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = -6563456.000;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

START_TEST(test_truncate_4) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = 0.22113434;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

START_TEST(test_truncate_5) {
  s21_decimal decimal = get_new_decimal();
  s21_decimal result = get_new_decimal();
  s21_decimal test = get_new_decimal();
  float x = 0.000000000;
  s21_from_float_to_decimal(x, &decimal);
  int ix = (int)x;
  s21_from_int_to_decimal(ix, &test);

  ck_assert_int_eq(0, s21_truncate(decimal, &result));
  ck_assert_int_eq(1, s21_is_equal(result, test));
}
END_TEST

TCase *s21_truncate_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_round_0);
  tcase_add_test(test_cases, test_truncate_1);
  tcase_add_test(test_cases, test_truncate_2);
  tcase_add_test(test_cases, test_truncate_3);
  tcase_add_test(test_cases, test_truncate_4);
  tcase_add_test(test_cases, test_truncate_5);
  return test_cases;
}
