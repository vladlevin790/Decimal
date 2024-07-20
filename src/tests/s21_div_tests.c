#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

START_TEST(test_0) {
	s21_decimal num_1 = {{5, 0, 0, 0}};
	s21_decimal num_2 = {{1, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{5, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_1) {
	s21_decimal num_1 = {{150, 0, 0, 0}};
	s21_decimal num_2 = {{10, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{15, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_2) {
	s21_decimal num_1 = {{150, 0, 0, 0}};
	s21_decimal num_2 = {{0, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 3);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_3) {
	s21_decimal num_1 = {{150, 0, 0, 0}};
	s21_decimal num_2 = {{0, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 3);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_4) {
	s21_decimal num_1 = {{1144189273, 1421741867, 0, 0}};
	s21_decimal num_2 = {{237856235, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-97427253, 5, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_5) {
	s21_decimal num_1 = {{1, 5, 0, 0}};
	s21_decimal num_2 = {{7, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-1227133513, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_6) {
	s21_decimal num_1 = {{100, 5, 4, 0}};
	s21_decimal num_2 = {{2, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-2147483598, 2, 2, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_7) {
	s21_decimal num_1 = {{100, 5, 4, 0}};
	s21_decimal num_2 = {{4, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1073741849, 1, 1, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_8) {
	s21_decimal num_1 = {{100, 500, 999, 0}};
	s21_decimal num_2 = {{4, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{25, -1073741699, 249, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_9) {
	s21_decimal num_1 = {{999, 999, 999, 0}};
	s21_decimal num_2 = {{333, 333, 333, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{3, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_10) {
	s21_decimal num_1 = {{999999999, 999999999, 999999999, 0}};
	s21_decimal num_2 = {{3, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{333333333, 333333333, 333333333, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_11) {
	s21_decimal num_1 = {{999999999, 999999999, 999999999, 0}};
	s21_decimal num_2 = {{999999999, 999999999, 999999999, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_12) {
	s21_decimal num_1 = {{2147483647, 2147483647, 2147483647, 0}};
	s21_decimal num_2 = {{2147483647, 2147483647, 2147483647, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_13) {
	s21_decimal num_1 = {{-2147483648, -2147483648, -2147483648, 0}};
	s21_decimal num_2 = {{-2147483648, -2147483648, -2147483648, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_14) {
	s21_decimal num_1 = {{0, 0, 0, 0}};
	s21_decimal num_2 = {{333, 3, 3, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 0, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_15) {
	s21_decimal num_1 = {{0, 0, 3, 0}};
	s21_decimal num_2 = {{3, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 1, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_16) {
	s21_decimal num_1 = {{125, 0, 0, 0}};
	s21_decimal num_2 = {{15, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-1923787435, 868844027, 451750905, 1769472}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_17) {
	s21_decimal num_1 = {{258762357, 0, 0, 0}};
	s21_decimal num_2 = {{92715829, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-478350233, -969422137, 1512960152, 1835008}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_18) {
	s21_decimal num_1 = {{258762357, 0, 0, 0}};
	s21_decimal num_2 = {{-554643571, 215, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{672578757, 63958515, 151296, 1835008}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_19) {
	s21_decimal num_1 = {{3, 0, 0, 196608}};
	s21_decimal num_2 = {{-554643571, 215, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-1349256028, 7533, 0, 1835008}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_20) {
	s21_decimal num_1 = {{-1, -1, -1, 0}};
	s21_decimal num_2 = {{3, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1431655765, 1431655765, 1431655765, 0}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_21) {
	s21_decimal num_1 = {{125, 0, 0, 0}};
	s21_decimal num_2 = {{3, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{-1029002581, 49252841, -2036212770, 1769472}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_22) {
	s21_decimal num_1 = {{100, 0, 0, 0}};
	s21_decimal num_2 = {{3, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{894784853, -819591186, 1807003620, 1769472}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_23) {
	s21_decimal num_1 = {{100, 0, 0, -2147483648}};
	s21_decimal num_2 = {{3, 0, 0, -2147483648}};
	s21_decimal result = {0};
	s21_decimal expected = {{894784853, -819591186, 1807003620, 1769472}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_24) {
	s21_decimal num_1 = {{100000000, 0, 0, 0}};
	s21_decimal num_2 = {{3, 0, 0, -2147483648}};
	s21_decimal result = {0};
	s21_decimal expected = {{894784853, -819591186, 1807003620, -2146107392}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

START_TEST(test_25) {
	s21_decimal num_1 = {{100000000, 0, 0, -2147483648}};
	s21_decimal num_2 = {{30000, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{894784853, -819591186, 1807003620, -2145845248}};

	int res_code = s21_div(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST


TCase *arithmetic_div_tests(void) {
  TCase *test_cases = tcase_create("test_cases");
  
   tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, test_4);
  tcase_add_test(test_cases, test_5);
  tcase_add_test(test_cases, test_6);
  tcase_add_test(test_cases, test_7);
  tcase_add_test(test_cases, test_8);
  tcase_add_test(test_cases, test_9);
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



  return test_cases;
}
