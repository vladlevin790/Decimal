#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_sub.h"
// void print_bits(int digit) {
//     for (int i =31; i>=0; i--) printf("%d", (digit >> i) & 1);
//     // printf(" ");
// }

// void print_decimal(s21_decimal digit) { 
//     for (int i = 3; i >= 0; i--) {
//         print_bits(digit.bits[i]);
//    if (i==3) printf("    <-знаковый бит     ");}
//    printf("\n");
// }



START_TEST(test_0) {
	s21_decimal num_1 = {{3, 0, 0, 0}};
	s21_decimal num_2 = {{4, 0, 0, 0}};
	s21_decimal result = {0};
	s21_decimal expected = {{1, 0, 0, -2147483648}};

	int res_code = s21_sub(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	// for (int i = 0; i < 4; ++i) {
  //       for (int j = 31; j >= 0; j--) {
  //           printf("%d", s21_get_bit(result.bits[i], j));
  //       }
  //       printf("\n");
	// }
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

START_TEST(test_9) {
 s21_decimal num_1 = {{1112504210, 954546471, 1206919124, 458752}};
 s21_decimal num_2 = {{162280484, 845859420, 1662463566, 458752}};
 s21_decimal result = {0};
 s21_decimal expected = {{-950223726, -108687052, 455544441, -2147024896}};

 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
}
END_TEST

START_TEST(test_10) {
 s21_decimal num_1 = {{-1577745379, 1410906814, 1975917157, -2146304000}};
 s21_decimal num_2 = {{287529920, 500118750, 933490658, -2146500608}};
 s21_decimal result = {0};
 s21_decimal expected = {{-943547949, -175602023, 931514740, 983040}};
 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
}
END_TEST

START_TEST(test_11) {
 s21_decimal num_1 = {{216264318, 1453433234, -382457762, -2146762752}};
 s21_decimal num_2 = {{-200511848, -1589875853, 376050698, -2146959360}};
 s21_decimal result = {0};
 s21_decimal expected = {{-1921381777, -193712550, -573585406, 589824}};

 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
}
END_TEST

START_TEST(test_12) {
 s21_decimal num_1 = {{-969384219, -1116816725, -1141911415, -2146959360}};
 s21_decimal num_2 = {{-737191410, -913941580, -500833696, -2147155968}};
 s21_decimal result = {0};
 s21_decimal expected = {{2064096651, -406018622, -503986752, 327680}};

 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
}
END_TEST

START_TEST(test_13) {
 s21_decimal num_1 = {{1000107844, -1162599740, 1410826771, -2146959360}};
 s21_decimal num_2 = {{-1858300870, 316841255, -538758498, -2146107392}};
 s21_decimal result = {0};
 s21_decimal expected = {{-694116872, -1164213020, 1410826771, -2146959360}};

 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
}
END_TEST

START_TEST(test_14) {
 s21_decimal num_1 = {{2136792646, -1426024798, 591412174, -2147155968}};
 s21_decimal num_2 = {{1712236787, -2079848253, -1939707652, 0}};
 s21_decimal result = {0};
 s21_decimal expected = {{1884142746, -1556950245, -1939701738, -2147483648}};

 int res_code = s21_sub(num_1, num_2, &result);
 ck_assert_int_eq(res_code, 0);
 for (int i = 0; i < 4; ++i) {
  ck_assert_int_eq(result.bits[i], expected.bits[i]);
 }
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
  tcase_add_test(test_cases, test_9);
  tcase_add_test(test_cases, test_10);
  tcase_add_test(test_cases, test_11);
  tcase_add_test(test_cases, test_12);
  tcase_add_test(test_cases, test_13);
  tcase_add_test(test_cases, test_14);

  return test_cases;
}