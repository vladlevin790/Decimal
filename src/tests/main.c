#include "main.h"

int main(void) {
  Suite *suite = suite_create("s21_decimal_tests");
  SRunner *runner;

  suite_add_tcase(suite, binary_get_tests());
  suite_add_tcase(suite, decimal_helper_get_tests());

  suite_add_tcase(suite, s21_from_int_to_decimal_get_tests());
  suite_add_tcase(suite, s21_from_decimal_to_int_get_tests());
  suite_add_tcase(suite, s21_from_float_to_decimal_get_tests());
  suite_add_tcase(suite, s21_from_decimal_to_float_get_tests());

  suite_add_tcase(suite, is_equal_add_test());
  suite_add_tcase(suite, is_not_equal_add_test());
  suite_add_tcase(suite, is_greater_add_test());
  suite_add_tcase(suite, is_greater_or_equal_add_test());
  suite_add_tcase(suite, is_less_add_test());
  suite_add_tcase(suite, is_less_or_equal_add_test());

  suite_add_tcase(suite, arithmetic_add_tests());
  suite_add_tcase(suite, arithmetic_sub_tests());
  suite_add_tcase(suite, arithmetic_div_tests());
  suite_add_tcase(suite, arithmetic_mul_tests());

  suite_add_tcase(suite, s21_round_get_tests());
  suite_add_tcase(suite, s21_floor_get_tests());
  suite_add_tcase(suite, s21_truncate_get_tests());
  suite_add_tcase(suite, s21_negate_get_tests());

  runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);

  return 0;
}