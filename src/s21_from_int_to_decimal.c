#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == s21_NULL) {
        return 1;
    }

    clear_decimal_digit(dst);
    set_decimal_sign(dst, src < 0);
    set_decimal_exponent(dst, 0);

    int is_min_value = src == INT_MIN;

    if (src < 0) {
        src += is_min_value; // Добавляем 1, чтобы не выйти за пределы int
        src *= -1;
    }
    
    for (int i = 0; i < 31; i++) {
        set_decimal_digit_by_index(dst, i, s21_get_bit(src, i));
    }

    // Если число == INT_MIN, то добавляем 1
    if (is_min_value) {
        s21_decimal tmp_decimal = {0};
        tmp_decimal.bits[0] = s21_set_bit(tmp_decimal.bits[0], 0);

        // TODO: s21_add(*dst, tmp_decimal, dst);
    }

    return 0;
}
