#include "s21_core_test.h"

int main() {
  int fail = 0;

  all_suite(&fail);

  return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void all_suite(int *const fail) {
  Suite *arr_test_func[] = {
      s21_from_decimal_to_int_tests(), s21_from_int_to_decimal_tests(),
      s21_from_decimal_to_float_tests(), s21_from_float_to_decimal_tests(),
      s21_is_equal_tests(), s21_is_greater_tests(),
      s21_is_less_or_equal_tests(), s21_is_not_equal_tests(),
      s21_is_greater_or_equal_tests(), s21_sub_tests(),
      s21_mul_tests(), s21_div_tests(), 
      s21_add_tests(), s21_negate_tests(),
      s21_floor_tests(), s21_round_tests(),
      NULL};

  for (int i = 0; arr_test_func[i] != NULL; ++i) {
    printf("\n==================================================\n\n");
    SRunner *runner = srunner_create(arr_test_func[i]);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);

    *fail += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n==================================================\n\n");
  }
}

