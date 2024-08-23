#ifndef S21_TEST_CORE
#define S21_TEST_CORE

#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

void all_suite(int *const fail);

Suite *s21_from_decimal_to_int_tests(void);

Suite *s21_from_int_to_decimal_tests(void);

Suite *s21_from_decimal_to_float_tests(void);

Suite *s21_from_float_to_decimal_tests(void);

Suite *s21_is_equal_tests(void);

Suite *s21_is_greater_tests(void);

Suite *s21_is_less_or_equal_tests(void);

Suite *s21_is_not_equal_tests(void);

Suite *s21_is_greater_or_equal_tests(void);

Suite *s21_sub_tests(void);

Suite *s21_mul_tests(void);

Suite *s21_div_tests(void);

Suite *s21_add_tests(void);

Suite *s21_negate_tests(void);

Suite *s21_floor_tests(void);

Suite *s21_round_tests(void);
#endif
