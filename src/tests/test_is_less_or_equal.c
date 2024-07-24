#include <check.h>

#include "../s21_decimal.h"
#include "main.h"

START_TEST(test_1) {
  // 1083450.456789
  s21_decimal value_1 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000600}};
  s21_decimal value_2 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000600}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_2) {
  //-1083450.456789
  s21_decimal value_1 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000100}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_3) {
  // 0
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_4) {
  // 1 = 1347348; 2 = 0
  s21_decimal value_1 = {{0x148F1400, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_5) {
  // 1 = 135;  2 = 664363
  s21_decimal value_1 = {{0x8000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x2B230A00, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_6) {
  // 1 = 5; 2 = -5
  s21_decimal value_1 = {{0x05000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x05000000, 0x00000000, 0x00000000, 0x00000080}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_7) {
  // 1 = 0.00000; 2 = -35.9439
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000500}};
  s21_decimal value_2 = {{0x0F7C0500, 0x00000000, 0x00000000, 0x00000480}};

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_8) {
  s21_decimal value_1 = {{5, 0, 0, 0}};            // 5
  s21_decimal value_2 = {{5, 0, 0, -2147483648}};  // -5

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_9) {
  s21_decimal value_1 = {{5, 0, 0, -2147483648}};  // -5
  s21_decimal value_2 = {{5, 0, 0, 0}};            // 5

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_10) {
  s21_decimal value_1 = {{5, 0, 0, -2147483648}};  // -5
  s21_decimal value_2 = {{5, 0, 0, -2147483648}};  // -5

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_11) {
  s21_decimal value_1 = {{5, 0, 0, 0}};  // 5
  s21_decimal value_2 = {{5, 0, 0, 0}};  // 5

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_12) {
  s21_decimal value_1 = {{51, 0, 0, -2147418112}};   // -5.1
  s21_decimal value_2 = {{511, 0, 0, -2147352576}};  // -5.11

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_13) {
  s21_decimal value_1 = {{511, 0, 0, 131072}};       // 5.11
  s21_decimal value_2 = {{511, 0, 0, -2147352576}};  // -5.11

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_14) {
  s21_decimal value_1 = {{5101, 0, 0, 196608}};  // 5.101
  s21_decimal value_2 = {{5101, 0, 0, 131072}};  // 51.01

  int comparison = s21_is_less_or_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

TCase* is_less_or_equal_add_test(void) {
  TCase* result = tcase_create("is_less_or_equal_test");

  tcase_add_test(result, test_1);
  tcase_add_test(result, test_2);
  tcase_add_test(result, test_3);
  tcase_add_test(result, test_4);
  tcase_add_test(result, test_5);
  tcase_add_test(result, test_6);
  tcase_add_test(result, test_7);
  tcase_add_test(result, test_8);
  tcase_add_test(result, test_9);
  tcase_add_test(result, test_10);
  tcase_add_test(result, test_11);
  tcase_add_test(result, test_12);
  tcase_add_test(result, test_13);
  tcase_add_test(result, test_14);

  return result;
}