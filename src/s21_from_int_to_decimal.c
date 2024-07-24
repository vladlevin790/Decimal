#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == NULL) {
        return 1;
    }

    clear_decimal(dst);
    set_decimal_sign(dst, src < 0);
    set_decimal_exponent(dst, 0);

    if (src < 0 && src != -2147483648) {
        src = -src;
    }

    dst->bits[0] = src;

    return 0;
}
