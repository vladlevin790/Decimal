#include <check.h>

#include "../../s21_decimal.h"
#include "../main.h"

START_TEST(test_1) {
  s21_decimal value_1 = {{0xD3040000, 0x00000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0xD1040000, 0x00000000, 0x00000000, 0x00000100}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_2) {
  s21_decimal value_1 = {{0xD3040000, 0x00000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0xD1040000, 0x00000000, 0x00000000, 0x00000180}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_3) {
  s21_decimal value_1 = {{0xD3040000, 0x00000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0xD1040000, 0x00000000, 0x00000000, 0x00000180}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_4) {
  s21_decimal value_1 = {{0xD3040000, 0x00000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_5) {
  s21_decimal value_1 = {{0xD3040000, 0x00000000, 0x00000000, 0x00000100}};
  s21_decimal value_2 = {{0x6258DC1F, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 1);
}
END_TEST

START_TEST(test_6) {
  //числа равны друг другу (534534242)
  s21_decimal value_1 = {{0x6258DC1F, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x6258DC1F, 0x00000000, 0x00000000, 0x00000000}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

START_TEST(test_7) {
  //сравнение с -0.00
  s21_decimal value_1 = {{0x6258DC1F, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000280}};

  int comparison = s21_is_less(value_1, value_2);

  ck_assert_int_eq(comparison, 0);
}
END_TEST

TCase* is_less_add_test(void) {
  TCase* result = tcase_create("is_less_test");

  tcase_add_test(result, test_1);
  tcase_add_test(result, test_2);
  tcase_add_test(result, test_3);
  tcase_add_test(result, test_4);
  tcase_add_test(result, test_5);
  tcase_add_test(result, test_6);
  tcase_add_test(result, test_7);

  return result;
}