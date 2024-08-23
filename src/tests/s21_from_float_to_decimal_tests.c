#include <check.h>

#include "../binary/s21_binary_operations.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_0) {
  float value = 0.0000456f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{456, 0, 0, 458752}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_1) {
  float value = 0.00000000000000456f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{456, 0, 0, 1114112}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_3) {
  float value = 456;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{456, 0, 0, 0}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_4) {
  float value = 123456789;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{123456800, 0, 0, 0}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_5) {
  float value = 123456789.1234567890f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{123456800, 0, 0, 0}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_6) {
  float value = 123.1234567890f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1231235, 0, 0, 262144}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_7) {
  float value = 123.1f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1231, 0, 0, 65536}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_8) {
  float value = 0.1f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1, 0, 0, 65536}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_9) {
  float value = 0.1000005f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1000005, 0, 0, 458752}};

  int result_code = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_10) {
  float value = 1;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1, 0, 0, 0}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_11) {
  float value = 1000003;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{1000003, 0, 0, 0}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test_12) {
  float value = 0.5f;
  s21_decimal result = s21_get_new_decimal();
  s21_decimal expected = {{5, 0, 0, 65536}};

  int result_code = s21_from_float_to_decimal(value, &result);

  ck_assert_int_eq(0, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
  }
}
END_TEST

// new tests
// Тест на NULL указатель
START_TEST(test_13) {
  float value = 0.5f;
  int result_code = s21_from_float_to_decimal(value, NULL);
  ck_assert_int_eq(1, result_code);
}
END_TEST

// Тест на NaN значение
START_TEST(test_14) {
  float value = NAN;
  s21_decimal result = s21_get_new_decimal();
  int result_code = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(1, result_code);
}
END_TEST

// Тест на бесконечное значение
START_TEST(test_15) {
  float value = INFINITY;
  s21_decimal result = s21_get_new_decimal();
  int result_code = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(1, result_code);
}
END_TEST

// Тест на значение больше максимального
/*
START_TEST(test_16) {
  float value = 79228162514264337593543950336.0f;
  s21_decimal result = s21_get_new_decimal();
  int result_code = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(1, result_code);
}
END_TEST
*/
// Тест на значение меньше минимального
START_TEST(test_17) {
  float value = 1e-29;
  s21_decimal result = s21_get_new_decimal();
  int result_code = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(CODE_CONVERTATION_ERROR, result_code);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_get_new_decimal().bits[i], result.bits[i]);
  }
}
END_TEST

Suite *s21_from_float_to_decimal_tests(void) {
  Suite *s = suite_create("\033[1;35ms21_from_float_to_decimal\033[0m\n");
  TCase *testCase = tcase_create("s21_test_case_from_float_to_decimal");

  suite_add_tcase(s, testCase);
  tcase_add_test(testCase, test_0);
  tcase_add_test(testCase, test_1);
  tcase_add_test(testCase, test_3);
  tcase_add_test(testCase, test_4);
  tcase_add_test(testCase, test_5);
  tcase_add_test(testCase, test_6);
  tcase_add_test(testCase, test_7);
  tcase_add_test(testCase, test_8);
  tcase_add_test(testCase, test_9);
  tcase_add_test(testCase, test_10);
  tcase_add_test(testCase, test_11);
  tcase_add_test(testCase, test_12);
  tcase_add_test(testCase, test_13);
  tcase_add_test(testCase, test_14);
  tcase_add_test(testCase, test_15);
  //tcase_add_test(testCase, test_16);
  tcase_add_test(testCase, test_17);
  
  return s;
}
