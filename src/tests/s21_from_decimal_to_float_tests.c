#include <check.h>

#include "../binary/s21_binary_operations.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_0) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_float_eq(0, value);
}
END_TEST

START_TEST(test_1) {
  s21_decimal decimal = {{5, 0, 0, -2147483648}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_float_eq(-5, value);
}
END_TEST

START_TEST(test_2) {
  s21_decimal decimal = {{-1171510507, 0, 0, 589824}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[32] = {0};
  sprintf(ans, "%f", value);
  ck_assert_int_eq(0, result);
  ck_assert_str_eq("3.123457", ans);
}
END_TEST

START_TEST(test_3) {
  s21_decimal decimal = {{-1395630315, 28744523, 0, 589824}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[64] = {0};
  sprintf(ans, "%.7G", value);

  ck_assert_int_eq(0, result);  // 1.234568E+08 == 1.23457e+08
  ck_assert_str_eq("1.234568E+08", ans);
  //   ck_assert_str_eq(1.234568E+08, ans);
}
END_TEST

START_TEST(test_4) {
  s21_decimal decimal = {{123456789, 0, 0, 589824}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[64] = {0};
  sprintf(ans, "%.7G", value);

  ck_assert_int_eq(0, result);  // 1.234568E+08 == 1.23457e+08
  ck_assert_str_eq("0.1234568", ans);
  //   ck_assert_str_eq(1.234568E+08, ans);
}
END_TEST

START_TEST(test_5) {
  s21_decimal decimal = {{123456789, 0, 0, -2146893824}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[64] = {0};
  sprintf(ans, "%.7G", value);

  ck_assert_int_eq(0, result);  // 1.234568E+08 == 1.23457e+08
  ck_assert_str_eq("-0.1234568", ans);
  //   ck_assert_str_eq(1.234568E+08, ans);
}
END_TEST

START_TEST(test_6) {
  s21_decimal decimal = {{5555, 0, 0, -2147287040}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[64] = {0};
  sprintf(ans, "%.7G", value);

  ck_assert_int_eq(0, result);  // 1.234568E+08 == 1.23457e+08
  ck_assert_str_eq("-5.555", ans);
  //   ck_assert_str_eq(1.234568E+08, ans);
}
END_TEST

START_TEST(test_7) {
  s21_decimal decimal = {{0, 0, 0, -2147024896}};
  float value = 0;

  int result = s21_from_decimal_to_float(decimal, &value);

  char ans[64] = {0};
  sprintf(ans, "%.7G", value);

  ck_assert_int_eq(0, result);  // 1.234568E+08 == 1.23457e+08
  ck_assert_str_eq("0", ans);
  //   ck_assert_str_eq(1.234568E+08, ans);
}
END_TEST

Suite *s21_from_decimal_to_float_tests(void) {
  Suite *s = suite_create("\033[1;35ms21_from_decimal_to_float\033[0m\n");
  TCase *testCase = tcase_create("s21_test_case_from_decimal_to_float");

  suite_add_tcase(s, testCase);
  tcase_add_test(testCase, test_0);
  tcase_add_test(testCase, test_1);
  tcase_add_test(testCase, test_2);
  tcase_add_test(testCase, test_3);
  tcase_add_test(testCase, test_4);
  tcase_add_test(testCase, test_5);
  tcase_add_test(testCase, test_6);
  tcase_add_test(testCase, test_7);

  return s;
}
