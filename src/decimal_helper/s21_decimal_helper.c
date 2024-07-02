#include "s21_decimal_helper.h"

int get_decimal_sign(s21_decimal decimal) {
    return s21_get_bit(decimal.bits[3], 31);
}

int get_decimal_exponent(s21_decimal decimal) {
    return s21_get_range_bits(decimal.bits[3], 16, 23);
}

void set_decimal_sign(s21_decimal* decimal, int sign) {
    if (sign == 0) {
        decimal->bits[3] = s21_clear_bit(decimal->bits[3], 31);
    } else {
        decimal->bits[3] = s21_set_bit(decimal->bits[3], 31);
    }
}

void set_decimal_exponent(s21_decimal* decimal, int exponent) {
    if (exponent < 0 || exponent > 28) {
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (s21_get_bit(exponent, i)) {
            decimal->bits[3] = s21_set_bit(decimal->bits[3], 16 + i);
        } else {
            decimal->bits[3] = s21_clear_bit(decimal->bits[3], 16 + i);
        }
    }
}

int get_decimal_digit_by_index(s21_decimal decimal, int index) {
    if (index < 0 || index >= 96) {
        return 0;
    }

    int bit_number = index / 32;
    int bit_index = index % 32;

    return s21_get_bit(decimal.bits[bit_number], bit_index);
}

void set_decimal_digit_by_index(s21_decimal* decimal, int index, int value) {
    if (index < 0 || index >= 96) {
        return;
    }

    int bit_number = index / 32;
    int bit_index = index % 32;

    if (value != 0) {
        decimal->bits[bit_number] = s21_set_bit(decimal->bits[bit_number], bit_index);
    } else {
        decimal->bits[bit_number] = s21_clear_bit(decimal->bits[bit_number], bit_index);
    }
}

void clear_decimal_digit(s21_decimal* decimal) {
    decimal->bits[0] = 0;
    decimal->bits[1] = 0;
    decimal->bits[2] = 0;
}


int check_int_range(s21_decimal decimal) {
    int is_error = 0;

    decimal.bits[0] = decimal.bits[0]; // TODO: Это заглушка, нужно удалить, когда все функции доделаются!

    // s21_decimal truncated_decimal = {0};
    // TODO: s21_truncate(decimal, &truncated_decimal);

    // TODO: убрать комментарий у 6 нижних строчек
    // s21_decimal min_decimal_for_int = {0};
    // min_decimal_for_int.bits[0] = 0X80000000; // 1000...000
    // set_decimal_sign(&min_decimal_for_int, 1);

    // s21_decimal max_decimal_for_int = {0};
    // min_decimal_for_int.bits[0] = 0X7FFFFFFF; // 0111...111
    // set_decimal_sign(&min_decimal_for_int, 0);
    
    // TODO: if (s21_is_greater(truncated_decimal, max_decimal_for_int) || s21_is_less(truncated_decimal, max_decimal_for_int))
    if (0) {
        is_error = 1;
    }

    return is_error;
}