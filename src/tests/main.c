#include "main.h"

int main(void) {
  // Suite* suite = suite_create("s21_decimal_tests");
  // SRunner* runner;
  
  // suite_add_tcase(suite, binary_get_tests());
  // suite_add_tcase(suite, decimal_helper_get_tests());

  // suite_add_tcase(suite, s21_from_int_to_decimal_get_tests());

  // runner = srunner_create(suite);
  // srunner_run_all(runner, CK_NORMAL);
  // srunner_free(runner);

  int a = (0b00000001000000000110000000001100);
  printf("a = %d\n", a);

  return 0;
}