#include <check.h>

// #include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

#define CALCULATION_ERROR 1

START_TEST(s21_floor_0) {
  s21_decimal decimal = {{149, 0, 0, 131072}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal decimal = {{150, 0, 0, 131072}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal decimal = {{149, 0, 0, -2147352576}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal decimal = {{150, 0, 0, -2147352576}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal decimal = {{-1097928128, 28, 0, 393216}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal decimal = {{-1097528128, 28, 0, 393216}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal decimal = {{-1097928128, 28, 0, -2147090432}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal decimal = {{-1097528128, 28, 0, -2147090432}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal decimal = {{1, 0, 0, -2147483648}};
  s21_decimal result = s21_get_new_decimal();
  
  int res = s21_floor(decimal, &result);
  ck_assert_int_eq(res, S21_DECIMAL_OK);
}
END_TEST

Suite *s21_floor_tests(void) {
  Suite *s = suite_create("\033[1;35ms21_floor\033[0m\n");
  TCase *testCase = tcase_create("s21_test_floor");

  suite_add_tcase(s, testCase);
  tcase_add_test(testCase, s21_floor_0);
  tcase_add_test(testCase, s21_floor_1);
  tcase_add_test(testCase, s21_floor_2);
  tcase_add_test(testCase, s21_floor_3);
  tcase_add_test(testCase, s21_floor_4);
  tcase_add_test(testCase, s21_floor_5);
  tcase_add_test(testCase, s21_floor_6);
  tcase_add_test(testCase, s21_floor_7);
  tcase_add_test(testCase, s21_floor_8);

  return s;
}
