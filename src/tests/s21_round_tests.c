#include <check.h>
// #include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#include "helper_tests.h"

#define CALCULATION_ERROR 1

START_TEST(s21_round_0) {
  s21_decimal decimal = {{5, 0, 0, 65536}};
  s21_decimal test = {{1, 0, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal decimal = {{864758201, 547961186, 0, 589824}};
  s21_decimal test = {{-1941491922, 0, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal decimal = {{864758201, 547961186, 0, -2146893824}};
  s21_decimal test = {{-1941491922, 0, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal decimal = {{731623216, 232077, 0, 524288}};
  s21_decimal test = {{9967639, 0, 0, 0}};

  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal decimal = {{731623216, 232077, 0, -2146959360}};
  s21_decimal test = {{9967639, 0, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal decimal = {{25, 0, 0, 65536}};
  s21_decimal test = {{3, 0, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal decimal = {{249, 0, 0, 131072}};
  s21_decimal test = {{2, 0, 0, 0}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal decimal = {{249, 0, 0, -2147352576}};
  s21_decimal test = {{2, 0, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal decimal = {{25, 0, 0, -2147418112}};
  s21_decimal test = {{3, 0, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  int res = s21_round(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
  check_decimal_bits(test, result);
}
END_TEST

TCase *s21_round_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, s21_round_0);
  tcase_add_test(test_cases, s21_round_1);
  tcase_add_test(test_cases, s21_round_2);
  tcase_add_test(test_cases, s21_round_3);
  tcase_add_test(test_cases, s21_round_4);
  tcase_add_test(test_cases, s21_round_5);
  tcase_add_test(test_cases, s21_round_6);
  tcase_add_test(test_cases, s21_round_7);
  tcase_add_test(test_cases, s21_round_8);

  return test_cases;
}
