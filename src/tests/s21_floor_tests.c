#include <check.h>

// #include <limits.h>

#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

#define CALCULATION_ERROR 1

START_TEST(s21_floor_to_1) {
  s21_decimal dec = {{14500, 0, 0, 0}};
  set_decimal_exponent(&dec, 4);
  s21_decimal dec_res;
  // 1.45 -> 1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_1_8_to_1) {
  s21_decimal dec = {{18, 0, 0, 0}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // 1.8 -> 1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_to_minus_2) {
  s21_decimal dec = {{18, 0, 0, 0x80000000}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // -1.8 -> -2
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 2 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
}
END_TEST

START_TEST(s21_floor_zero_to_zero) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_decimal dec_res;
  // 0 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_099999999999999999999_to_0) {
  s21_decimal dec = {{1661992959, 1808227885, 5, 1310720}};
  s21_decimal dec_res;
  // 0.99999999999999999999 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_minus_099999999999999999999_to_minus_1) {
  s21_decimal dec = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
  s21_decimal dec_res;
  // -0.99999999999999999999 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
}
END_TEST

START_TEST(s21_floor_09_to_0) {
  s21_decimal dec = {{9, 0, 0, 0}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // 0.9 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_minus_09_to_minus_1) {
  s21_decimal dec = {{9, 0, 0, 0x80000000}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // -0.9 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
}
END_TEST

START_TEST(s21_floor_minus_05_to_minus_1) {
  s21_decimal dec = {{0x5, 0x0, 0x0, 0x80010000}};
  s21_decimal dec_res;
  // -0.5 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_minus_051_to_minus_1) {
  s21_decimal dec = {{0x32, 0x0, 0x0, 0x80020000}};
  s21_decimal dec_res;
  // -0.51 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_049_to_0) {
  s21_decimal dec = {{0x31, 0x0, 0x0, 0x20000}};
  s21_decimal dec_res;
  // 0.49 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_minus_049_to_minus_1) {
  s21_decimal dec = {{0x31, 0x0, 0x0, 0x80020000}};
  s21_decimal dec_res;
  // -0.49 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_051_to_0) {
  s21_decimal dec = {{0x33, 0x0, 0x0, 0x20000}};
  s21_decimal dec_res;
  // 0.51 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_050_to_0) {
  s21_decimal dec = {{0x32, 0x0, 0x0, 0x20000}};
  s21_decimal dec_res;
  // 0.50 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_1_low_to_1) {
  s21_decimal dec = {{268435457, 1042612833, 542101086, 1835008}};
  s21_decimal dec_res;
  // 1.0000000000000000000000000001 -> 1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_pos_to_zero) {
  s21_decimal dec = {{0x1, 0x0, 0x0, 851968}};
  s21_decimal dec_res;
  // 0.0000000000001 -> 0
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_neg_to_1) {
  s21_decimal dec = {{0x1, 0x0, 0x0, 2148401152}};
  s21_decimal dec_res;
  // -0.00000000000001 -> -1
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_0_max_to_7) {
  s21_decimal dec = {{4294967295, 4294967295, 4294967295, 1835008}};
  s21_decimal dec_res;
  // 7.9228162514264337593543950335 -> 7
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 7 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_max_to_max) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal dec_res;
  // 79228162514264337593543950335
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && (unsigned int)dec_res.bits[0] == 0xffffffff &&
            (unsigned int)dec_res.bits[1] == 0xffffffff && (unsigned int)dec_res.bits[2] == 0xffffffff &&
            dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_42949_67295_to_42949) {
  s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
  s21_decimal dec_res;
  // 42949.67295 -> 42949
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 42949 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
}
END_TEST

START_TEST(s21_floor_minus_42949_67295_to_minus_42950) {
  s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
  s21_decimal dec_res;
  // -42949.67295 -> -42950
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0xA7C6 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
}
END_TEST

START_TEST(s21_floor_1234567_1234567_to_1234567) {
  s21_decimal dec = {{0x73593407, 0xB3A, 0x0, 0x70000}};
  s21_decimal dec_res;
  // 1234567.1234567 -> 1234567
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x12D687 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
}
END_TEST

START_TEST(s21_floor_minus_1234567_1234567_to_minus_1234568) {
  s21_decimal dec = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
  s21_decimal dec_res;
  // -1234567.1234567 -> -1234568
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1234568 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_1234567890_1234567890_to_1234567890) {
  s21_decimal dec = {{3944680146, 2874452364, 0, 655360}};
  s21_decimal dec_res;
  // 1234567890.1234567890 -> 1234567890
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1234567890 &&
            dec_res.bits[1] == 0 && dec_res.bits[2] == 0 &&
            dec_res.bits[3] == 0x0);
}
END_TEST

START_TEST(s21_floor_minus_1234567890_1234567890_to_minus_1234567890) {
  s21_decimal dec = {{3944680146, 2874452364, 0, 2148139008}};
  s21_decimal dec_res;
  // -1234567890.1234567890 -> -1234567891
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1234567891 &&
            dec_res.bits[1] == 0 && dec_res.bits[2] == 0 &&
            dec_res.bits[3] == 2147483648);
}
END_TEST

START_TEST(s21_floor_1234_5_to_1234) {
  s21_decimal dec = {{0x3039, 0x0, 0x0, 0x0}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // 1234.5 -> -1234
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x4d2 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
}
END_TEST

START_TEST(s21_floor_1235_5_to_1235) {
  s21_decimal dec = {{0x3043, 0x0, 0x0, 0x0}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // 1235.5 -> 1235
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1235 && dec_res.bits[1] == 0 &&
            dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
}
END_TEST

START_TEST(s21_floor_wrong_dec) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal dec_res;
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_floor_null_dec) {
  s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
  int res = s21_floor(dec, NULL);

  ck_assert(res == CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_floor_big00_5_to_big00) {
  s21_decimal dec = {{0x55555555, 0x0, 0x55555555, 0x10000}};
  set_decimal_exponent(&dec, 1);
  s21_decimal dec_res;
  // 2640938749860586450804312200.5 -> 2640938749860586450804312200
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x8888888 &&
            (unsigned int)dec_res.bits[1] == 0x80000000 && (unsigned int)dec_res.bits[2] == 0x8888888 &&
            dec_res.bits[3] == 0x0);
}
END_TEST

START_TEST(s21_floor_big93_5_to_big93) {
  s21_decimal dec = {{4294967295, 4294967295, 4294967295, 589824}};
  s21_decimal dec_res;
  // 79228162514264337593.543950335 -> 79228162514264337593
  int res = s21_floor(dec, &dec_res);

  ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 3047500985 &&
            dec_res.bits[1] == 1266874889 && dec_res.bits[2] == 4 &&
            dec_res.bits[3] == 0);
}
END_TEST

TCase *s21_floor_tests(void)  {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, s21_floor_to_1);
  tcase_add_test(test_cases, s21_floor_1_8_to_1);
  tcase_add_test(test_cases, s21_floor_to_minus_2);
  tcase_add_test(test_cases, s21_floor_zero_to_zero);
  tcase_add_test(test_cases, s21_floor_pos_to_zero);
  tcase_add_test(test_cases, s21_floor_neg_to_1);
  tcase_add_test(test_cases, s21_floor_0_max_to_7);
  tcase_add_test(test_cases, s21_floor_max_to_max);
  tcase_add_test(test_cases, s21_floor_099999999999999999999_to_0);
  tcase_add_test(test_cases, s21_floor_minus_099999999999999999999_to_minus_1);
  tcase_add_test(test_cases, s21_floor_09_to_0);
  tcase_add_test(test_cases, s21_floor_minus_09_to_minus_1);
  tcase_add_test(test_cases, s21_floor_minus_049_to_minus_1);
  tcase_add_test(test_cases, s21_floor_minus_05_to_minus_1);
  tcase_add_test(test_cases, s21_floor_minus_051_to_minus_1);
  tcase_add_test(test_cases, s21_floor_049_to_0);
  tcase_add_test(test_cases, s21_floor_050_to_0);
  tcase_add_test(test_cases, s21_floor_051_to_0);
  tcase_add_test(test_cases, s21_floor_1_low_to_1);
  tcase_add_test(test_cases, s21_floor_42949_67295_to_42949);
  tcase_add_test(test_cases, s21_floor_minus_42949_67295_to_minus_42950);
  tcase_add_test(test_cases, s21_floor_minus_1234567890_1234567890_to_minus_1234567890);
  tcase_add_test(test_cases, s21_floor_1234567890_1234567890_to_1234567890);
  tcase_add_test(test_cases, s21_floor_minus_1234567_1234567_to_minus_1234568);
  tcase_add_test(test_cases, s21_floor_1234567_1234567_to_1234567);
  tcase_add_test(test_cases, s21_floor_1235_5_to_1235);
  tcase_add_test(test_cases, s21_floor_1234_5_to_1234);
  tcase_add_test(test_cases, s21_floor_wrong_dec);
  tcase_add_test(test_cases, s21_floor_null_dec);
  tcase_add_test(test_cases, s21_floor_big00_5_to_big00);
  tcase_add_test(test_cases, s21_floor_big93_5_to_big93);


  return test_cases;
}
