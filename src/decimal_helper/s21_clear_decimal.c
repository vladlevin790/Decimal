#include "s21_decimal_helper.h"

void s21_clear_decimal(s21_decimal* decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}
