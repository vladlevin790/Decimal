#include "main.h"

int main(void) {
  Suite* suite = suite_create("s21_decimal_tests");
  SRunner* runner;
  
  suite_add_tcase(suite, binary_get_tests());
  suite_add_tcase(suite, decimal_helper_get_tests());

  runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);

  return 0;
}