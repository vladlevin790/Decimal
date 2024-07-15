#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

// #include "../arithmetic/s21_arithmetic.h"
// #include "../binary/s21_binary.h"
// #include "../s21_decimal.h"
// #include "../s21_decimal.h"

// Helper function to initialize s21_decimal
// void init_decimal(s21_decimal *decimal, int bits[4]) {
//   for (int i = 0; i < 4; ++i) {
//     decimal->bits[i] = bits[i];
//   }
// }

// Test case for s21_add

START_TEST(test_s21_add_simple) {
    s21_decimal num_1 = {{1, 0, 0, 0}};
    s21_decimal num_2 = {{3, 0, 0, 0}};
   
    s21_decimal expected = {{4, 0, 0, 0}};
    s21_decimal result = {0};
    
    int res_code = s21_add(num_1, num_2, &result);
    ck_assert_int_eq(res_code, S21_DECIMAL_OK);
    for (int i = 0; i < 4; ++i) {
      ck_assert_int_eq(result.bits[i], expected.bits[i]);
    }
}
END_TEST

START_TEST(test_s21_add_with_scale) {
    s21_decimal num_1 = {{1, 1, 1, 0}};
    set_decimal_exponent(&num_1, 3);

    s21_decimal num_2 = {{2, 1, 1, 0}};
    set_decimal_exponent(&num_2, 3);

    s21_decimal expected = {{3, 2, 2, 0}};
    set_decimal_exponent(&expected, 3);

    s21_decimal result = {0};
    
    int res_code = s21_add(num_1, num_2, &result);
    ck_assert_int_eq(res_code, S21_DECIMAL_OK);
    for (int i = 0; i < 4; ++i) {
      ck_assert_int_eq(result.bits[i], expected.bits[i]);
    }
}
END_TEST

START_TEST(test_s21_add_check_boards_mantissa_1) {

    s21_decimal num_1 = {{0xFFFFFFFF, 0, 0, 0}};
    s21_decimal num_2 = {{1, 0, 0, 0}};
    s21_decimal expected = {{0, 1, 0, 0}};
    s21_decimal result = {0};
    
    int res_code = s21_add(num_1, num_2, &result);
    ck_assert_int_eq(res_code, S21_DECIMAL_OK);
    for (int i = 0; i < 4; ++i) {
      ck_assert_int_eq(result.bits[i], expected.bits[i]);
    }
}
END_TEST

START_TEST(test_s21_add_check_boards_mantissa_2) {

    s21_decimal num_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
    s21_decimal num_2 = {{1, 0, 0, 0}};
    s21_decimal expected = {{0, 0, 1, 0}};
    s21_decimal result = {0};
    
    int res_code = s21_add(num_1, num_2, &result);
    ck_assert_int_eq(res_code, S21_DECIMAL_OK);
    for (int i = 0; i < 4; ++i) {
      ck_assert_int_eq(result.bits[i], expected.bits[i]);
    }
}
END_TEST


START_TEST(test_s21_add_with_diff_scale) {

    s21_decimal num_1 = {{2, 1, 0, 131072}};
    s21_decimal num_2 = {{1, 0, 0, 196608}};
    s21_decimal expected = {{21, 10, 0, 196608}};

    s21_decimal result = {0};
    
    int res_code = s21_add(num_1, num_2, &result);
    ck_assert_int_eq(res_code, S21_DECIMAL_OK);
    for (int i = 0; i < 4; ++i) {
      ck_assert_int_eq(result.bits[i], expected.bits[i]);
    }
}
END_TEST


// Тест для сложения больших чисел
START_TEST(test_s21_add_large_numbers) {
  // Инициализация num_1 = 79,228,162,514,264,337,593,543,950,335
  s21_decimal num_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  // Выполнение сложения (должно вызвать переполнение)
  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 1);
}
END_TEST


// Тест для сложения с отрицательными числами
START_TEST(test_s21_add_negative_numbers) {
 
  s21_decimal num_1 = {{5, 0, 0, 0x80000000}};
  s21_decimal num_2 = {{10, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_s21_add_negative_first_num_1) {
 
  s21_decimal num_1 = {{8, 0, 0, 0}};
  
  set_decimal_sign(&num_1, 1);
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{6, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_s21_add_negative_first_num_2) {
 
  s21_decimal num_1 = {{8, 0, 0, 0}};
  set_decimal_sign(&num_1, 1);
  s21_decimal num_2 = {{19, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{11, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_s21_add_negative_second_num_1) {
 
  s21_decimal num_1 = {{25, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  set_decimal_sign(&num_2, 1);
  s21_decimal result = {0};
  s21_decimal expected = {{22, 0, 0, 0}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_s21_add_negative_second_num_2) {
 
  s21_decimal num_1 = {{8, 0, 0, 0}};
  s21_decimal num_2 = {{19, 0, 0, 0}};
  set_decimal_sign(&num_2, 1);
  s21_decimal result = {0};
  s21_decimal expected = {{11, 0, 0, 0x80000000}};
  int res_code = s21_add(num_1, num_2, &result);

  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

// Тест для сложения с нулем
START_TEST(test_s21_add_with_zero) {

  s21_decimal num_1 = {{123456789, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{123456789, 0, 0, 0}};

  int res_code = s21_add(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_0) {
	s21_decimal num_1 = {{0, 5, 3, 0}};
  set_decimal_exponent(&num_1, 3);
	s21_decimal num_2 = {{65, 0, 4, 131072}};
  set_decimal_exponent(&num_2, 2);
	s21_decimal result = {0};
	s21_decimal expected = {{650, 5, 43, 0}};
  set_decimal_exponent(&result, 3);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_1) {
	s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2145779712}};
	s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 983040}};
	s21_decimal result = {0};
	s21_decimal expected = {{-465877505, 1387253419, -1173774756, 983040}};

	int res_code = s21_add(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_2) {
	s21_decimal num_1 = {{1742750924, -765097718, 2020532269, 720896}};
	s21_decimal num_2 = {{-1135548987, -1729193528, 1968365552, -2146238464}};
	s21_decimal result = {0};
	s21_decimal expected = {{-1640015172, 593591452, 2020532250, 720896}};

	int res_code = s21_add(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

TCase *arithmetic_add_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

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

  return test_cases;
}
