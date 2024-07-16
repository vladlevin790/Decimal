#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

void print_bit(int digit) {
    for (int i =31; i>=0; i--) printf("%d", (digit >> i) & 1);
    printf(" ");
}

void print_decimal(s21_decimal digit) { 
    for (int i = 3; i >= 0; i--) {
        print_bit(digit.bits[i]);
   if (i==3) printf("    <-знаковый бит     ");}
}
	// printf("\n");
	// print_decimal(result);
	// printf("\n");
// --------------------------------------------

START_TEST(test_0) {
	s21_decimal num_1 = {{3, 0, 0, 0}};
	s21_decimal num_2 = {{4, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1, 0, 0, -2147483648}};

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
        for (int j = 31; j >= 0; j--) {
            printf("%d", s21_get_bit(result.bits[i], j));
        }
        printf("\n");
	}
		ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_1) {
	s21_decimal num_1 = {0};
	s21_decimal num_2 = {0};
	s21_decimal result = {0};
	num_1.bits[0] =0b1;
	num_2.bits[0] =0b101;
	s21_decimal expected = {0};
	expected.bits[0] = 0b100;
	set_decimal_sign(&expected, 1);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_2) {
	s21_decimal num_1 = {0};
	s21_decimal num_2 = {0};
	s21_decimal result = {0};
	num_1.bits[0] = 0b101;
	num_2.bits[0] = 0b1;
	s21_decimal expected = {0};
	expected.bits[0] = 0b100;
	set_decimal_sign(&expected, 0);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_3) {
	s21_decimal num_1 = {{4294967295, 4294967295, 4294967295, 0}};
	s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {0};
	set_decimal_sign(&expected, 0);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_4) {
	s21_decimal num_1 = {{0,0,0,0}};
	s21_decimal num_2 = {{4294967295, 4294967295, 4294967295, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{4294967295, 4294967295, 4294967295, 0}};
	set_decimal_sign(&expected, 1);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_5) {
	s21_decimal num_1 = {{0, 0, 0, 0}};
	s21_decimal num_2 = {{0, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 0, 0}};
	set_decimal_sign(&expected, 0);
	set_decimal_sign(&num_2, 1);
	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_6) {
	s21_decimal num_1 = {{2, 1, 0, 0}};
	s21_decimal num_2 = {{1, 2, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {0};
	expected.bits[0] = 0b11111111111111111111111111111111;
	set_decimal_sign(&expected, 1);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_7) {
	s21_decimal num_1 = {{1, 2, 0, 0}};
	s21_decimal num_2 = {{2, 1, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {0};
	expected.bits[0] = 0b11111111111111111111111111111111;
	set_decimal_sign(&expected, 0);

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST

START_TEST(test_8) {
	s21_decimal num_1 = {{1, 0, 0, 0}};
	set_decimal_exponent(&num_1, 2);
	s21_decimal num_2 = {{30, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {0};
	expected.bits[0] = 0b00000000000000000000101110110111;
	set_decimal_sign(&expected, 1);
 	set_decimal_exponent(&expected, 2);
	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	ck_assert_int_eq(result.bits[0], expected.bits[0]);
	ck_assert_int_eq(result.bits[1], expected.bits[1]);
	ck_assert_int_eq(result.bits[2], expected.bits[2]);
	ck_assert_int_eq(s21_get_bit(result.bits[3], 31), s21_get_bit(expected.bits[3], 31));
}
END_TEST






TCase *arithmetic_sub_tests(void) {
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



  return test_cases;
}