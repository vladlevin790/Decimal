#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

// START_TEST(test_0) {
// 	s21_decimal num_1 = {{1, 0, 0, 0}};
// 	s21_decimal num_2 = {{3, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{3, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_1) {
// 	s21_decimal num_1 = {{3, 0, 0, 0}};
// 	s21_decimal num_2 = {{1, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{3, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_2) {
// 	s21_decimal num_1 = {{3, 0, 0, 0}};
// 	s21_decimal num_2 = {{3, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{9, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_3) {
// 	s21_decimal num_1 = {{9, 0, 0, 0}};
// 	s21_decimal num_2 = {{9, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{81, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_4) {
// 	s21_decimal num_1 = {{123456789, 0, 0, 0}};
// 	s21_decimal num_2 = {{987654321, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-67153019, 28389652, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_5) {
// 	s21_decimal num_1 = {{1912284813, 287, 0, 0}};
// 	s21_decimal num_2 = {{-1881568455, 2299, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{794764389, 526544783, 660998, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_6) {
// 	s21_decimal num_1 = {{1942978950, 2874, 0, 0}};
// 	s21_decimal num_2 = {{-1635815360, 22995, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-1308294784, 1114979995, 66099812, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_7) {
// 	s21_decimal num_1 = {{-2045046977, 28744, 0, 0}};
// 	s21_decimal num_2 = {{821715591, 229956, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 1);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_8) {
// 	s21_decimal num_1 = {{1653732529, 2874452, 0, -2147483648}};
// 	s21_decimal num_2 = {{567180565, 22995619, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 2);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_9) {
// 	s21_decimal num_1 = {{123456, 0, 0, -2147287040}};
// 	s21_decimal num_2 = {{3, 0, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{370368, 0, 0, -2147287040}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_10) {
// 	s21_decimal num_1 = {{-1019794767, 77, 0, 589824}};
// 	s21_decimal num_2 = {{-1883992299, 77, 0, -2146893824}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-1210884219, 1585209676, 6031, -2146304000}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_11) {
// 	s21_decimal num_1 = {{1233169989, 1016507639, 669, -2146304000}};
// 	s21_decimal num_2 = {{-1533265724, 1552338606, 294476024, -2145976320}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-1885176809, -1419499196, -659590793, 1310720}};

// 	int res_code = s21_mul(num_1, num_2, &result);
//     print_m_decimal(result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_12) {
// 	s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
// 	s21_decimal num_2 = {{1719348742, -1633477906, 263338225, 1835008}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-539633203, -1805983613, 193930895, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_13) {
// 	s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
// 	s21_decimal num_2 = {{1719348196, -1633477906, 263338225, 1835008}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-539633605, -1805983613, 193930895, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_14) {
// 	s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
// 	s21_decimal num_2 = {{920244317, 29013649, 0, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{464574131, 1636883631, 497479962, 720896}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_15) {
// 	s21_decimal num_1 = {{1, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{-1, -1, -1, 0}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-1, -1, -1, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_16) {
// 	s21_decimal num_1 = {{1, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{-1, -1, -1, -2145648640}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_17) {
// 	s21_decimal num_1 = {{-1, -1, -1, 0}};
// 	s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 2);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_18) {
// 	s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
// 	s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 0}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 1);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

START_TEST(test_19) {
	s21_decimal num_1 = {{1, 0, 0, 1835008}};
	s21_decimal num_2 = {{1, 0, 0, 1835008}};
	s21_decimal result = {0};
	s21_decimal expected = {{0, 0, 0, 0}};

	int res_code = s21_mul(num_1, num_2, &result);
	ck_assert_int_eq(res_code, 0);
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(result.bits[i], expected.bits[i]);
	}
}
END_TEST

// START_TEST(test_20) {
// 	s21_decimal num_1 = {{4, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_21) {
// 	s21_decimal num_1 = {{5, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{0, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_22) {
// 	s21_decimal num_1 = {{6, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{1, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_23) {
// 	s21_decimal num_1 = {{55, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{6, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_24) {
// 	s21_decimal num_1 = {{54, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{5, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_25) {
// 	s21_decimal num_1 = {{56, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{6, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_26) {
// 	s21_decimal num_1 = {{550, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{55, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_27) {
// 	s21_decimal num_1 = {{551, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{55, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_28) {
// 	s21_decimal num_1 = {{555, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{56, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

// START_TEST(test_29) {
// 	s21_decimal num_1 = {{556, 0, 0, 1835008}};
// 	s21_decimal num_2 = {{1, 0, 0, 65536}};
// 	s21_decimal result = {0};
// 	s21_decimal expected = {{56, 0, 0, 1835008}};

// 	int res_code = s21_mul(num_1, num_2, &result);
// 	ck_assert_int_eq(res_code, 0);
// 	for (int i = 0; i < 4; ++i) {
// 		ck_assert_int_eq(result.bits[i], expected.bits[i]);
// 	}
// }
// END_TEST

TCase *arithmetic_mul_tests(void) {
  TCase *test_cases = tcase_create("test_cases");
  
//    tcase_add_test(test_cases, test_0);
//    tcase_add_test(test_cases, test_1);
//    tcase_add_test(test_cases, test_2);
//    tcase_add_test(test_cases, test_3);
//    tcase_add_test(test_cases, test_4);
//    tcase_add_test(test_cases, test_5);
//    tcase_add_test(test_cases, test_6);
//    tcase_add_test(test_cases, test_7);
//    tcase_add_test(test_cases, test_8);
//    tcase_add_test(test_cases, test_9);
//    tcase_add_test(test_cases, test_10);
//    tcase_add_test(test_cases, test_11);
//    tcase_add_test(test_cases, test_12);
//    tcase_add_test(test_cases, test_13);
//    tcase_add_test(test_cases, test_14);
//    tcase_add_test(test_cases, test_15);
//    tcase_add_test(test_cases, test_16);
//    tcase_add_test(test_cases, test_17);
//    tcase_add_test(test_cases, test_18);
   tcase_add_test(test_cases, test_19);
//    tcase_add_test(test_cases, test_20);
//    tcase_add_test(test_cases, test_21);
//    tcase_add_test(test_cases, test_22);
//    tcase_add_test(test_cases, test_23);
//    tcase_add_test(test_cases, test_24);
//    tcase_add_test(test_cases, test_25);
//    tcase_add_test(test_cases, test_26);
//    tcase_add_test(test_cases, test_27);
//    tcase_add_test(test_cases, test_28);
//    tcase_add_test(test_cases, test_29);


  return test_cases;
}
