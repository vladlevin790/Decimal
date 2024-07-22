#include <check.h>

#include "../s21_decimal.h"
#include "main.h"

START_TEST(test_1) {
  //1083450.456789
  s21_decimal value_1 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000600}};
  s21_decimal value_2 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000600}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_2) {
  //-1083450.456789
  s21_decimal value_1 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0xD5FAAD42, 0xFC000000, 0x00000000, 0x00000100}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_3) {
  //0
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_4) {
  //1 = 1347348; 2 = 0
  s21_decimal value_1 = {{0x148F1400, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_5) {
  //1 = 135;  2 = 664363
  s21_decimal value_1 = {{0x87000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x2B230A00, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_6) {
  //1 = 5; 2 = -5
  s21_decimal value_1 = {{0x05000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x05000000, 0x00000000, 0x00000000, 0x00000080}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_7) {
  //1 = 0.00000; 2 = -35.9439
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000500}};
  s21_decimal value_2 = {{0x0F7C0500, 0x00000000, 0x00000000, 0x00000480}};

  int comparison = s21_is_equal(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

TCase* is_equal_add_test(void) {
  TCase* result = tcase_create("is_equal_test");

  tcase_add_test(result, test_1);
  tcase_add_test(result, test_2);
  tcase_add_test(result, test_3);
  tcase_add_test(result, test_4);
  tcase_add_test(result, test_5);
  tcase_add_test(result, test_6);
  tcase_add_test(result, test_7);

  return result;
}