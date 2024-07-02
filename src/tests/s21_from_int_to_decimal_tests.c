#include <check.h>
#include "../s21_decimal.h"
#include "../binary/s21_binary.h"
#include "../decimal_helper/s21_decimal_helper.h"

START_TEST(test_0) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(0, &decimal);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, get_decimal_sign(decimal));
  ck_assert_int_eq(0, decimal.bits[0]);
}
END_TEST

START_TEST(test_1) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(3, &decimal);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, get_decimal_sign(decimal));
  ck_assert_int_eq(3, decimal.bits[0]);
}
END_TEST

START_TEST(test_2) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(INT_MAX, &decimal);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, get_decimal_sign(decimal));
  ck_assert_int_eq(INT_MAX, decimal.bits[0]);
}
END_TEST

START_TEST(test_3) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(-1, &decimal);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, get_decimal_sign(decimal));
  ck_assert_int_eq(-1, decimal.bits[0] * -1);
}
END_TEST

START_TEST(test_4) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(-123, &decimal);

  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, get_decimal_sign(decimal));
  ck_assert_int_eq(-123, decimal.bits[0] * -1);
}
END_TEST

START_TEST(test_5) {
  s21_decimal decimal = {0};
  int result = s21_from_int_to_decimal(INT_MIN, &decimal);
  
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, get_decimal_sign(decimal));
for (int i = 31; i >= 0; i--)
    {
        printf("%d", s21_get_bit(decimal.bits[0], i));
    }
    
    printf("\n");
  ck_assert_int_eq(INT_MIN, ((unsigned int)decimal.bits[0]) * -1);
}
END_TEST

TCase *s21_from_int_to_decimal_get_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, test_4);
  tcase_add_test(test_cases, test_5);

  return test_cases;
}
