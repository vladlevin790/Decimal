#include <check.h>

#include "../binary/s21_binary.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_0) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(test_1) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 1;
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, value);
}
END_TEST

START_TEST(test_2) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 2147483647;
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(2147483647, value);
}
END_TEST

START_TEST(test_3) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 1;
  s21_set_decimal_sign(&decimal, 1);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(-1, value);
}
END_TEST

START_TEST(test_4) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 0X80000000;
  s21_set_decimal_sign(&decimal, 1);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(-2147483648, value);
}
END_TEST

START_TEST(test_5) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 0XFFFFFFFF;
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(1, result);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(test_6) {
  s21_decimal decimal = {0};
  decimal.bits[1] = 1;
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(1, result);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(test_7) {
  s21_decimal decimal = {0};
  s21_set_decimal_sign(&decimal, 1);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(test_8) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 12345;
  s21_set_decimal_sign(&decimal, 1);
  s21_set_decimal_exponent(&decimal, 1);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(-1234, value);
}
END_TEST

START_TEST(test_9) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 12345;
  s21_set_decimal_sign(&decimal, 1);
  s21_set_decimal_exponent(&decimal, 7);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(test_10) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 199999999;
  s21_set_decimal_sign(&decimal, 1);
  s21_set_decimal_exponent(&decimal, 3);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(-199999, value);
}
END_TEST

START_TEST(test_11) {
  s21_decimal decimal = {0};
  decimal.bits[0] = 0b00000000000000000000000000001111;
  s21_set_decimal_exponent(&decimal, 1);
  int value = 0;

  int result = s21_from_decimal_to_int(decimal, &value);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, value);
}
END_TEST

TCase *s21_from_decimal_to_int_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, test_4);
  tcase_add_test(test_cases, test_5);
  tcase_add_test(test_cases, test_6);
  tcase_add_test(test_cases, test_7);
  tcase_add_test(test_cases, test_8);
  tcase_add_test(test_cases, test_9);
  tcase_add_test(test_cases, test_10);
  tcase_add_test(test_cases, test_11);

  return test_cases;
}