#include <check.h>
#include <limits.h>
#include "../s21_decimal.h"
#include "../decimal_helper/s21_decimal_helper.h"

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
TCase *arithmetic_sub_tests(void) {
  TCase *test_cases = tcase_create("test_cases");

  tcase_add_test(test_cases, test_0);

  return test_cases;
}