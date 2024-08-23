#include <check.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#include "helper_tests.h"
START_TEST(test_truncate_0) {
  s21_decimal decimal = {{1302546422, -1587415236, 4052, -2146762752}};
  s21_decimal test = {{254048838, 174, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(test_truncate_1) {
  s21_decimal decimal = {{1302546422, -1587415236, 4052, 720896}};
  s21_decimal test = {{254048838, 174, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal decimal = {{2023177216, -2034508782, 40, 589824}};
  s21_decimal test = {{254048838, 174, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal decimal = {{0, 0, 0, 589824}};
  s21_decimal test = {{0, 0, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(test_truncate_4) {
  s21_decimal decimal = {{-1530661241, 1528, 0, 0}};
  s21_decimal test = {{-1530661241, 1528, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(test_truncate_5) {
  s21_decimal decimal = {{-1530661241, 1528, 0, -2147483648}};
  s21_decimal test = {{-1530661241, 1528, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_truncate(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

TCase *s21_truncate_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_truncate_0);
  tcase_add_test(test_cases, test_truncate_1);
  tcase_add_test(test_cases, test_truncate_2);
  tcase_add_test(test_cases, test_truncate_3);
  tcase_add_test(test_cases, test_truncate_4);
  tcase_add_test(test_cases, test_truncate_5);
  return test_cases;
}
