#include <check.h>

#include "../binary/s21_binary.h"
#include "../s21_decimal.h"

START_TEST(test_set_bit_0) {
  s21_decimal decimal = {0};
  decimal.bits[3] = s21_set_bit(decimal.bits[3], 31);

  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 31), 1);
}
END_TEST

START_TEST(test_set_bit_1) {
  s21_decimal decimal = {0};
  decimal.bits[3] = s21_set_bit(decimal.bits[3], 30);

  ck_assert_int_eq(decimal.bits[3], 0x40000000);
}
END_TEST

START_TEST(test_set_bit_2) {
  s21_decimal decimal = {0};
  decimal.bits[3] = s21_set_bit(decimal.bits[3], 0);

  ck_assert_int_eq(decimal.bits[3], 0x1);
}
END_TEST

START_TEST(test_get_bit_0) {
  s21_decimal decimal = {0};
  decimal.bits[3] = 0x1;

  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 0), 1);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 1), 0);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 31), 0);
}
END_TEST

START_TEST(test_get_bit_1) {
  s21_decimal decimal = {0};
  decimal.bits[3] = 0x20000000;

  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 0), 0);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 29), 1);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 31), 0);
}
END_TEST

START_TEST(test_get_bit_2) {
  s21_decimal decimal = {0};
  decimal.bits[3] = 0xE0000002;

  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 0), 0);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 1), 1);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 2), 0);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 28), 0);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 29), 1);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 30), 1);
  ck_assert_int_eq(s21_get_bit(decimal.bits[3], 31), 1);
}
END_TEST

TCase *binary_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_set_bit_0);
  tcase_add_test(test_cases, test_set_bit_1);
  tcase_add_test(test_cases, test_set_bit_2);
  tcase_add_test(test_cases, test_get_bit_0);
  tcase_add_test(test_cases, test_get_bit_1);
  tcase_add_test(test_cases, test_get_bit_2);

  return test_cases;
}
