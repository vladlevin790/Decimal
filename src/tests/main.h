#ifndef MAIN_H_
#define MAIN_H_

#include <check.h>
#include "../s21_decimal.h"

TCase* binary_get_tests(void);
TCase* decimal_helper_get_tests(void);

TCase* s21_from_int_to_decimal_get_tests(void);
TCase* s21_from_decimal_to_int_get_tests(void);

#endif