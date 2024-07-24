#include <check.h>
#include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#include "helper_tests.h"

START_TEST(test_s21_add_simple) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal expected = {{4, 0, 0, 0}};
  s21_decimal result = {0};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_with_scale) {
  s21_decimal num_1 = {{1, 1, 1, 0}};
  s21_set_decimal_exponent(&num_1, 3);
  s21_decimal num_2 = {{2, 1, 1, 0}};
  s21_set_decimal_exponent(&num_2, 3);
  s21_decimal expected = {{3, 2, 2, 0}};
  s21_set_decimal_exponent(&expected, 3);

  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_check_boards_mantissa_1) {
  s21_decimal num_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal expected = {{0, 1, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_check_boards_mantissa_2) {
  s21_decimal num_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 1, 0}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_with_diff_scale) {
  s21_decimal num_1 = {{2, 1, 0, 131072}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal expected = {{21, 10, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

// Тест для сложения больших чисел
START_TEST(test_s21_add_large_numbers) {
  s21_decimal num_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(test_s21_add_negative_numbers) {
  s21_decimal num_1 = {{5, 0, 0, 0x80000000}};
  s21_decimal num_2 = {{10, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_negative_first_num_1) {
  s21_decimal num_1 = {{8, 0, 0, 0}};
  s21_set_decimal_sign(&num_1, 1);
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{6, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_negative_first_num_2) {
  s21_decimal num_1 = {{8, 0, 0, 0}};
  s21_set_decimal_sign(&num_1, 1);
  s21_decimal num_2 = {{19, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{11, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_negative_second_num_1) {
  s21_decimal num_1 = {{25, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_set_decimal_sign(&num_2, 1);
  s21_decimal result = {0};
  s21_decimal expected = {{22, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_s21_add_negative_second_num_2) {
  s21_decimal num_1 = {{8, 0, 0, 0}};
  s21_decimal num_2 = {{19, 0, 0, 0}};
  s21_set_decimal_sign(&num_2, 1);
  s21_decimal result = {0};
  s21_decimal expected = {{11, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

// Тест для сложения с нулем
START_TEST(test_s21_add_with_zero) {
  s21_decimal num_1 = {{123456789, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{123456789, 0, 0, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_0) {
  s21_decimal num_1 = {{0, 5, 3, 0}};
  s21_set_decimal_exponent(&num_1, 3);
  s21_decimal num_2 = {{65, 0, 4, 0}};
  s21_set_decimal_exponent(&num_2, 2);
  s21_decimal result = {0};
  s21_decimal expected = {{650, 5, 43, 0}};
  s21_set_decimal_exponent(&expected, 3);

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_1) {
  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2145779712}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 983040}};
  s21_decimal result = {0};
  s21_decimal expected = {{-465877505, 1387253419, -1173774756, 983040}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_2) {
  s21_decimal num_1 = {{1742750924, -765097718, 2020532269, 720896}};
  s21_decimal num_2 = {{-1135548987, -1729193528, 1968365552, -2146238464}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1640015172, 593591452, 2020532250, 720896}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_3) {
  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147483648}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-878008479, 2111051569, 2007341612, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

/////////////////////////////////////////////// more tests

START_TEST(case_NULL_result) {
  s21_decimal num_1 = {{1, 2, 3, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int res_code = s21_add(num_1, num_2, NULL);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(case_0_add_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_add_minus_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // возможно будет -0
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_0_add_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {
      {0, 0, 0, 0}};  // возможно будет -0 что тоже верно -0 == +0
  int res_code = s21_add(num_2, num_1, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MAX_add_0) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MIN_add_0) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_add_MAX) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 1, 1, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 1, 1, 0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_add_MIN) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MIN_add_MAX) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MAX_add_MIN) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MAX_add_MAX) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MIN_add_MIN) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_1) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, -2147483648}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MAX_add_1) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_0_4) {
  // num_1: -79228162514264337593543950335
  // num_2: -0.4
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{4, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MIN_add_minus_0_5) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{5, 0, 0, -2147418112}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_0_6) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{6, 0, 0, -2147418112}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MAX_add_04) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{4, 0, 0, 65536}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{-1, -1, -1, 0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MAX_add_05) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MAX_add_06) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MAX_add_minus_0_6) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.6
  // result: 79228162514264337593543950334

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{6, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2, -1, -1, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MIN_add_0_6) {
  // num_1: -79228162514264337593543950335
  // num_2: 0.6
  // result: -79228162514264337593543950334

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2, -1, -1, -2147483648}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1e_28_add_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal expected = {{2, 0, 0, 1835008}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_1e_28_add_1e_28) {
  // num_1: -0.0000000000000000000000000001
  // num_2: 0.0000000000000000000000000001
  // result: 0.0000000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, -2145648640}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  result = s21_remove_useless_zeros(result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1e_28_add_minus_1e_28) {
  // num_1: 0.0000000000000000000000000001
  // num_2: -0.0000000000000000000000000001
  // result: 0.0000000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 1835008}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1e_28_add_123) {
  // num_1: 0.0000000000000000000000000001
  // num_2: 123
  // result: 123.00000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{123, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1946157056, 337520979, 666784336, 1703936}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MAX_add_1e_28) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal expected = {{-1, -1, -1, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_MIN_add_5e_28) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 1835008}};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1234567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal expected = {{-1825831516, 0, 0, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_1234567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal expected = {{-1825831516, 0, 0, -2147483648}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_1234567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1234567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_123_4567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal expected = {{-1825831516, 0, 0, 458752}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1234567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1494321198, 2874452, 0, 458752}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_123_4567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1494321198, 2874452, 0, 458752}};
  int res_code = s21_add(num_2, num_1, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_1234567890_add_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, -2147024896}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1494321198, 2874452, 0, -2147024896}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_123_4567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, -2147024896}};
  s21_decimal num_2 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1494321198, 2874452, 0, -2147024896}};
  int res_code = s21_add(num_2, num_1, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_1234567890_add_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, -2147024896}};
  s21_decimal result = {0};
  s21_decimal expected = {{331510318, 2874452, 0, 458752}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_1234567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal result = {0};
  s21_decimal expected = {{331510318, 2874452, 0, -2147024896}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_005_add_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 196608}};
  s21_decimal num_2 = {{555, 0, 0, 196608}};
  s21_decimal expected = {{560, 0, 0, 196608}};
  s21_decimal result = {{0}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_0_005_add_0_555) {
  s21_decimal num_1 = {{5, 0, 0, -2147287040}};
  s21_decimal num_2 = {{555, 0, 0, 196608}};
  s21_decimal result = {0};
  s21_decimal expected = {{550, 0, 0, 196608}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_005_add_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 196608}};
  s21_decimal num_2 = {{555, 0, 0, -2147287040}};
  s21_decimal result = {0};
  s21_decimal expected = {{550, 0, 0, -2147287040}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_minus_0_005_add_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, -2147287040}};
  s21_decimal num_2 = {{555, 0, 0, -2147287040}};
  s21_decimal result = {0};
  s21_decimal expected = {{560, 0, 0, -2147287040}};
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(case_0_9_9_add_0_0_1) {
  // num_1: 0.9999999999999999999999999999
  // num_2: 0.0000000000000000000000000001
  // result: 1.0000000000000000000000000000

  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435456, 1042612833, 542101086, 1835008}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_37) {
  // num_1: 9999999999999999999999999999
  // num_2: 1
  // result: 10000000000000000000000000000

  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435456, 1042612833, 542101086, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_38) {
  // num_1: 10000000000000000000000000000
  // num_2: -0.1
  // result: 10000000000000000000000000000

  s21_decimal num_1 = {{268435456, 1042612833, 542101086, 0}};
  s21_decimal num_2 = {{1, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435456, 1042612833, 542101086, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_39) {
  // num_1: -10000000000000000000000000000
  // num_2: 0.9999999999999999999999999999
  // result: -9999999999999999999999999999

  s21_decimal num_1 = {{268435456, 1042612833, 542101086, -2147483648}};
  s21_decimal num_2 = {{268435455, 1042612833, 542101086, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435455, 1042612833, 542101086, -2147483648}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_10) {
  s21_decimal num_1 = {{852919139, -770113862, -150719240, 65536}};
  s21_decimal num_2 = {{45476013, 1407855207, -953703238, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{807443126, 2116998227, 802983998, 65536}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_11) {
  s21_decimal num_1 = {{743005692, 1340886807, -1742730093, 1769472}};
  s21_decimal num_2 = {{1285328408, 2097886862, -379268184, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1705441845, -1885298344, -1351160182, 1769472}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_12) {
  s21_decimal num_1 = {{1890367386, 1854587228, 834402379, -2147418112}};
  s21_decimal num_2 = {{1454631274, 874104635, -1343889481, -2145976320}};
  s21_decimal result = {0};
  s21_decimal expected = {{1895811164, 1854587228, 834402379, -2147418112}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_13) {
  s21_decimal num_1 = {{581401523, -1230801330, -909589579, 917504}};
  s21_decimal num_2 = {{-1751664840, 1693474836, -345093276, -2145714176}};
  s21_decimal result = {0};
  s21_decimal expected = {{692678317, -1232497788, -909589579, 917504}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_14) {
  s21_decimal num_1 = {{-2091391607, -989442883, 307287636, 983040}};
  s21_decimal num_2 = {{999223026, -1713722674, 230390364, 262144}};
  s21_decimal result = {0};
  s21_decimal expected = {{1570090020, 174621481, -1991063650, 327680}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_15) {
  s21_decimal num_1 = {{-340670285, 119105447, -750466349, 524288}};
  s21_decimal num_2 = {{-2095656996, 1991329625, 173493335, -2145845248}};
  s21_decimal result = {0};
  s21_decimal expected = {{2015196505, 119105440, -750466349, 524288}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_16) {
  s21_decimal num_1 = {{-1053816109, 1466627434, -1068230700, 1703936}};
  s21_decimal num_2 = {{1819945193, 1031658719, -178474118, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1819945788, 1031658719, -178474118, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_17) {
  s21_decimal num_1 = {{547996319, 771047912, 2061758863, -2145976320}};
  s21_decimal num_2 = {{-1039318628, 1596161993, -1943948749, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1038938301, 1596161993, -1943948749, -2147483648}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_18) {
  s21_decimal num_1 = {{-2042446913, -872502412, -1507264745, -2146041856}};
  s21_decimal num_2 = {{-1091840949, -751789964, -1791321454, 1703936}};
  s21_decimal result = {0};
  s21_decimal expected = {{2009963915, 912990672, -1507515109, -2146041856}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_19) {
  s21_decimal num_1 = {{-1468951125, -1478907203, -2076828288, 262144}};
  s21_decimal num_2 = {{1880617516, 1323770903, 1027842776, -2145845248}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1487911478, -1478907203, -2076828288, 262144}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_20) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {0};
  // s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(test_21) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(test_22) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_23) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2, -1, -1, -2147483648}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_24) {
  s21_decimal num_1 = {{1410555356, -1746906726, 1333513254, -2146172928}};
  s21_decimal num_2 = {{28059102, 1191971701, -837972297, -2147221504}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1090428868, 1191972273, -837972297, -2147221504}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_25) {
  s21_decimal num_1 = {{1933125357, -1943690446, 268282559, -2145845248}};
  s21_decimal num_2 = {{1204369500, 1760463144, -896501278, 983040}};
  s21_decimal result = {0};
  s21_decimal expected = {{1486348141, 1645236662, -896501278, 983040}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_26) {
  s21_decimal num_1 = {{1008624570, -1450889517, 236362104, -2146238464}};
  s21_decimal num_2 = {{558947845, 1570396269, -1716899060, 262144}};
  s21_decimal result = {0};
  s21_decimal expected = {{-160500142, 1570395253, -1716899060, 262144}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_27) {
  s21_decimal num_1 = {{-524683496, 1832375850, -1025769078, 1114112}};
  s21_decimal num_2 = {{1341888615, 309348111, -1009911017, -2147090432}};
  s21_decimal result = {0};
  s21_decimal expected = {{-44692372, 168937116, -1009911017, -2147090432}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_28) {
  s21_decimal num_1 = {{-1126701977, 1016504082, -81678682, 851968}};
  s21_decimal num_2 = {{-1137929962, 1514522612, -1726624530, 524288}};
  s21_decimal result = {0};
  s21_decimal expected = {{1947004931, 1025507801, -1726582397, 524288}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_29) {
  s21_decimal num_1 = {{1201750530, -1365279147, -638091748, 524288}};
  s21_decimal num_2 = {{-1921539528, -736441043, -220950866, -2147155968}};
  s21_decimal result = {0};
  s21_decimal expected = {{838922693, 1201954487, -224607741, -2147155968}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_30) {
  s21_decimal num_1 = {{2115506330, -2098404792, 982682896, 1703936}};
  s21_decimal num_2 = {{1093289326, -95708546, 1844568673, 1572864}};
  s21_decimal result = {0};
  s21_decimal expected = {{1973437848, -245541613, 1854395502, 1572864}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_31) {
  s21_decimal num_1 = {{1887922407, 2036740101, -1860482425, -2146172928}};
  s21_decimal num_2 = {{-817394130, 1390073385, -270632853, -2147352576}};
  s21_decimal result = {0};
  s21_decimal expected = {{1141252285, 1390073396, -270632853, -2147352576}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_32) {
  s21_decimal num_1 = {{-2025030002, -530225084, -1645971678, -2146238464}};
  s21_decimal num_2 = {{1438101568, -1527691912, 2138758738, -2146500608}};
  s21_decimal result = {0};
  s21_decimal expected = {{1927954833, 885597189, 2139023638, -2146500608}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_33) {
  s21_decimal num_1 = {{1291994134, 752019444, -1267552062, 1114112}};
  s21_decimal num_2 = {{277112037, -801166982, -1736015997, 1114112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1561076301, 1713072164, 558636653, 1048576}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_34) {
  // Decimal values:
  // num_1: экспонента более 28, некорректная
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 2835008}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_35) {
  // Decimal values:
  // num_1: экспонента 29
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 1900544}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_36) {
  // num_1: 10
  // num_2: 1.0000
  // result: 11.0000

  s21_decimal num_1 = {{10, 0, 0, 0}};
  s21_decimal num_2 = {{10000, 0, 0, 262144}};
  s21_decimal result = {0};
  s21_decimal expected = {{110000, 0, 0, 262144}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

TCase *arithmetic_add_tests(void) {
  TCase *test_cases = tcase_create("test_cases_s21_add");

  // tcase_add_test(test_cases, test_s21_add);
  tcase_add_test(test_cases, test_s21_add_simple);
  tcase_add_test(test_cases, test_s21_add_with_scale);
  tcase_add_test(test_cases, test_s21_add_with_diff_scale);
  tcase_add_test(test_cases, test_s21_add_check_boards_mantissa_1);
  tcase_add_test(test_cases, test_s21_add_check_boards_mantissa_2);
  tcase_add_test(test_cases, test_s21_add_negative_numbers);
  tcase_add_test(test_cases, test_s21_add_negative_first_num_1);
  tcase_add_test(test_cases, test_s21_add_negative_first_num_2);
  tcase_add_test(test_cases, test_s21_add_negative_second_num_1);
  tcase_add_test(test_cases, test_s21_add_negative_second_num_2);
  tcase_add_test(test_cases, test_s21_add_with_zero);
  tcase_add_test(test_cases, test_s21_add_large_numbers);
  tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, test_10);
  tcase_add_test(test_cases, test_11);
  tcase_add_test(test_cases, test_12);
  tcase_add_test(test_cases, test_13);
  tcase_add_test(test_cases, test_14);
  tcase_add_test(test_cases, test_15);
  tcase_add_test(test_cases, test_16);
  tcase_add_test(test_cases, test_17);
  tcase_add_test(test_cases, test_18);
  tcase_add_test(test_cases, test_19);
  tcase_add_test(test_cases, test_20);
  tcase_add_test(test_cases, test_21);
  tcase_add_test(test_cases, test_22);
  tcase_add_test(test_cases, test_23);
  tcase_add_test(test_cases, test_24);
  tcase_add_test(test_cases, test_25);
  tcase_add_test(test_cases, test_26);
  tcase_add_test(test_cases, test_27);
  tcase_add_test(test_cases, test_28);
  tcase_add_test(test_cases, test_29);
  tcase_add_test(test_cases, test_30);
  tcase_add_test(test_cases, test_31);
  tcase_add_test(test_cases, test_32);
  tcase_add_test(test_cases, test_33);
  tcase_add_test(test_cases, test_34);
  tcase_add_test(test_cases, test_35);
  tcase_add_test(test_cases, test_36);
  tcase_add_test(test_cases, test_37);
  tcase_add_test(test_cases, test_38);
  tcase_add_test(test_cases, test_39);
  tcase_add_test(test_cases, case_NULL_result);
  tcase_add_test(test_cases, case_0_add_0);
  tcase_add_test(test_cases, case_0_add_minus_0);
  tcase_add_test(test_cases, case_minus_0_add_0);
  tcase_add_test(test_cases, case_MAX_add_04);
  tcase_add_test(test_cases, case_MIN_add_minus_0_6);
  tcase_add_test(test_cases, case_MIN_add_minus_0_5);
  tcase_add_test(test_cases, case_MIN_add_minus_0_4);
  tcase_add_test(test_cases, case_MAX_add_06);
  tcase_add_test(test_cases, case_MAX_add_05);
  tcase_add_test(test_cases, case_MAX_add_minus_0_6);
  tcase_add_test(test_cases, case_MIN_add_0_6);
  tcase_add_test(test_cases, case_1e_28_add_1e_28);
  tcase_add_test(test_cases, case_minus_1e_28_add_1e_28);
  tcase_add_test(test_cases, case_1e_28_add_minus_1e_28);
  tcase_add_test(test_cases, case_1e_28_add_123);
  tcase_add_test(test_cases, case_MAX_add_1e_28);
  tcase_add_test(test_cases, case_MIN_add_5e_28);
  tcase_add_test(test_cases, case_1234567890_add_1234567890);
  tcase_add_test(test_cases, case_minus_1234567890_add_minus_1234567890);
  tcase_add_test(test_cases, case_minus_1234567890_add_1234567890);
  tcase_add_test(test_cases, case_1234567890_add_minus_1234567890);
  tcase_add_test(test_cases, case_123_4567890_add_123_4567890);
  tcase_add_test(test_cases, case_1234567890_add_123_4567890);
  tcase_add_test(test_cases, case_minus_1234567890_add_123_4567890);
  tcase_add_test(test_cases, case_1234567890_add_minus_123_4567890);
  tcase_add_test(test_cases, case_minus_123_4567890_add_minus_1234567890);
  tcase_add_test(test_cases, case_minus_1234567890_add_minus_123_4567890);
  tcase_add_test(test_cases, case_123_4567890_add_1234567890);
  tcase_add_test(test_cases, case_0_005_add_0_555);
  tcase_add_test(test_cases, case_minus_0_005_add_0_555);
  tcase_add_test(test_cases, case_0_005_add_minus_0_555);
  tcase_add_test(test_cases, case_minus_0_005_add_minus_0_555);
  tcase_add_test(test_cases, case_0_9_9_add_0_0_1);
  tcase_add_test(test_cases, case_MAX_add_0);
  tcase_add_test(test_cases, case_0_add_MAX);
  tcase_add_test(test_cases, case_MIN_add_0);
  tcase_add_test(test_cases, case_0_add_MIN);
  tcase_add_test(test_cases, case_MIN_add_MAX);
  tcase_add_test(test_cases, case_MAX_add_MAX);
  tcase_add_test(test_cases, case_MAX_add_1);
  tcase_add_test(test_cases, case_MIN_add_MIN);
  tcase_add_test(test_cases, case_MIN_add_minus_1);
  tcase_add_test(test_cases, case_MAX_add_MIN);

  return test_cases;
}
