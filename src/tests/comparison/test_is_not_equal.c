#include <check.h>

#include "../../s21_decimal.h"
#include "../main.h"

START_TEST(test_1) {
  s21_decimal value_1 = {{0x15CD5B07, 0x00000000, 0x00000000, 0x00000600}};
  s21_decimal value_2 = {{0x15CD5B07, 0x00000000, 0x00000000, 0x00000600}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_2) {
  s21_decimal value_1 = {{0xF233DFE1, 0x55E47FF4, 0xFD1E6600, 0x00000080}};
  s21_decimal value_2 = {{0xF233DFE1, 0x55E47FF4, 0xFD1E6600, 0x00000080}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_3) {
  s21_decimal value_1 = {{0xF233DFE1, 0x55E47FF4, 0xFD1E6600, 0x00000080}};
  s21_decimal value_2 = {{0xDEABD355, 0x01000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_4) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_5) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000280}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_6) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000280}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000280}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_7) {
  s21_decimal value_1 = {{0x01000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x01000000, 0x00000000, 0x00000000, 0x00000080}};

  int comparison = s21_is_not_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

TCase* is_not_equal_add_test(void) {
  TCase* result = tcase_create("is_not_equal_test");

  tcase_add_test(result, test_1);
  tcase_add_test(result, test_2);
  tcase_add_test(result, test_3);
  tcase_add_test(result, test_4);
  tcase_add_test(result, test_5);
  tcase_add_test(result, test_6);
  tcase_add_test(result, test_7);

  return result;
}