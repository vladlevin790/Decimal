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
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
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
	s21_decimal num_2 = {{65, 0, 4, 0}};
  set_decimal_exponent(&num_2, 2);
	s21_decimal result = {0};
	s21_decimal expected = {{650, 5, 43, 0}};
  set_decimal_exponent(&expected, 3);

	int res_code = s21_add(num_1, num_2, &result);
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

START_TEST(test_3) {
        s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147483648}};
        s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 0}};
        s21_decimal result = {0};
        s21_decimal expected = {{-878008479, 2111051569, 2007341612, 0}};

        int res_code = s21_add(num_1, num_2, &result);
        ck_assert_int_eq(res_code, 0);
        for (int i = 0; i < 4; ++i) {
                ck_assert_int_eq(result.bits[i], expected.bits[i]);
        }
}
END_TEST

/////////////////////////////////////////////// more tests

START_TEST(case_NULL_result) {
  s21_decimal num_1 = {{1, 2, 3, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int return_s21 = s21_add(num_1, num_2, NULL);
  ck_assert_int_eq(return_s21, 1);
}
END_TEST

START_TEST(case_0_add_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_add_minus_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_add_0) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_2, num_1, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_add_0) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[1], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[2], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[3], 0);
  ck_assert_int_eq(return_s21, S21_DECIMAL_OK);
}
END_TEST

START_TEST(case_MIN_add_0) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[1], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[2], 0xffffffff);
  ck_assert_int_eq(s21_res.bits[3], 0x80000000);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_add_MAX) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 4294967295);
  ck_assert_int_eq(s21_res.bits[1], 4294967295);
  ck_assert_int_eq(s21_res.bits[2], 4294967295);
  ck_assert_int_eq(s21_res.bits[3], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_add_MIN) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 4294967295);
  ck_assert_int_eq(s21_res.bits[1], 4294967295);
  ck_assert_int_eq(s21_res.bits[2], 4294967295);
  ck_assert_int_eq(s21_res.bits[3], 2147483648);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_add_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_add_MIN) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], 0);
  ck_assert_int_eq(s21_res.bits[1], 0);
  ck_assert_int_eq(s21_res.bits[2], 0);
  ck_assert_int_eq(s21_res.bits[3], 0);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_add_MAX) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MIN_add_MIN) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0x80000000}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MAX_add_1) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_0_5) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MIN_add_minus_0_6) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{6, 0, 0, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(case_MAX_add_05) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MAX_add_06) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(return_s21, ERROR_OVERFLOW);
}
END_TEST

START_TEST(case_MAX_add_minus_0_6) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{6, 0, 0, 2147549184}};
  s21_decimal orig_res = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST
START_TEST(case_MIN_add_0_6) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal orig_res = {{4294967294, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST


START_TEST(case_1e_28_add_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{2, 0, 0, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1e_28_add_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 2149318656}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{0, 0, 0, 2149318656}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_add_minus_1e_28) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 2149318656}};
  s21_decimal orig_res = {{0, 0, 0, 1835008}}; 
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1e_28_add_123) {
  s21_decimal num_1 = {{1, 0, 0, 1769472}};
  s21_decimal num_2 = {{123, 0, 0, 0}};
  s21_decimal orig_res = {{2348810240, 337520979, 666784336, 1703936}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MAX_add_1e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_MIN_add_5e_28) {
  s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 1835008}};
  s21_decimal orig_res = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{2469135780, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{2469135780, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 0}};
  s21_decimal orig_res = {{0, 0, 0, 2147483648}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal orig_res = {{0, 0, 0, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 458752}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{2469135780, 0, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_123_4567890_add_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_2, num_1, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_add_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_123_4567890_add_minus_1234567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{2800646098, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_2, num_1, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1234567890_add_minus_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 0}};
  s21_decimal num_2 = {{1234567890, 0, 0, 2147942400}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 458752}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_1234567890_add_123_4567890) {
  s21_decimal num_1 = {{1234567890, 0, 0, 2147483648}};
  s21_decimal num_2 = {{1234567890, 0, 0, 458752}};
  s21_decimal orig_res = {{331510318, 2874452, 0, 2147942400}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_005_add_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 196608}};
  s21_decimal num_2 = {{555, 0, 0, 196608}};
  s21_decimal orig_res = {{560, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_005_add_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 2147680256}};
  s21_decimal num_2 = {{555, 0, 0, 196608}};
  s21_decimal orig_res = {{550, 0, 0, 196608}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_005_add_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 196608}};
  s21_decimal num_2 = {{555, 0, 0, 2147680256}};
  s21_decimal orig_res = {{550, 0, 0, 2147680256}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_minus_0_005_add_minus_0_555) {
  s21_decimal num_1 = {{5, 0, 0, 2147680256}};
  s21_decimal num_2 = {{555, 0, 0, 2147680256}};
  s21_decimal orig_res = {{560, 0, 0, 2147680256}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_0_9_9_add_0_0_1) {
  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal orig_res = {{268435456, 1042612833, 542101086, 1835008}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_999999999999999999999999999_add_1) {
  s21_decimal num_1 = {{3892314111, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal orig_res = {{3892314112, 2681241660, 54210108, 0}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(case_1000000000000000000000000000_add_minus_0_1) {
  s21_decimal num_1 = {{3892314112, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{1, 0, 0, 2147549184}};
  s21_decimal orig_res = {{268435455, 1042612833, 542101086, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(
    case_minus_1000000000000000000000000000_add_0_999999999999999999999999999) {
  s21_decimal num_1 = {{3892314112, 2681241660, 54210108, 2147483648}};
  s21_decimal num_2 = {{3892314111, 2681241660, 54210108, 1769472}};
  s21_decimal orig_res = {{268435446, 1042612833, 542101086, 2147549184}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
}
END_TEST

START_TEST(
    case_1000000000000000000000000000_add_0_999999999999999999999999999) {
  s21_decimal num_1 = {{3892314112, 2681241660, 54210108, 0}};
  s21_decimal num_2 = {{3892314111, 2681241660, 54210108, 1769472}};
  s21_decimal orig_res = {{268435466, 1042612833, 542101086, 65536}};
  s21_decimal s21_res = {{0, 0, 0, 0}};
  int return_s21 = s21_add(num_1, num_2, &s21_res);
  ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
  ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
  ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
  ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
  ck_assert_int_eq(return_s21, 0);
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
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, case_NULL_result);
  tcase_add_test(test_cases, case_0_add_0);
  tcase_add_test(test_cases, case_0_add_minus_0);
  tcase_add_test(test_cases, case_minus_0_add_0);
  tcase_add_test(test_cases, case_MAX_add_0);
  tcase_add_test(test_cases, case_MIN_add_0);
  tcase_add_test(test_cases, case_0_add_MAX);
  tcase_add_test(test_cases, case_0_add_MIN);
  tcase_add_test(test_cases, case_MAX_add_MIN);
  tcase_add_test(test_cases, case_MIN_add_MAX);
  tcase_add_test(test_cases, case_MAX_add_MAX);
  tcase_add_test(test_cases, case_MIN_add_MIN);
  tcase_add_test(test_cases, case_MIN_add_MIN);
  tcase_add_test(test_cases, case_MIN_add_minus_1);
  tcase_add_test(test_cases, case_MAX_add_1);
  tcase_add_test(test_cases, case_MAX_add_05);
  tcase_add_test(test_cases, case_MAX_add_06);
  tcase_add_test(test_cases, case_MIN_add_minus_0_5);
  tcase_add_test(test_cases, case_MAX_add_minus_0_6);
  tcase_add_test(test_cases, case_MIN_add_0_6);
  tcase_add_test(test_cases, case_MIN_add_minus_0_6);
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
  tcase_add_test(test_cases, case_999999999999999999999999999_add_1);
  tcase_add_test(test_cases, case_1000000000000000000000000000_add_minus_0_1);
  tcase_add_test(
      test_cases,
      case_minus_1000000000000000000000000000_add_0_999999999999999999999999999);
  tcase_add_test(
      test_cases, case_1000000000000000000000000000_add_0_999999999999999999999999999);


  return test_cases;
}
