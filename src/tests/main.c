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

  char s[1024] = {0};
  float a = 0.000000000000000000000000000123451234567899873654321f * pow(10, 23);
  sprintf(s, "%.15f", a);
  printf("%s\n", s);

  return 0;
}