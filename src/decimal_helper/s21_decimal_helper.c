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

s21_decimal get_new_decimal() {
    s21_decimal decimal = {0};
    clear_decimal(&decimal);

    return decimal;
}

s21_decimal get_decimal_with_int_value(int value) {
    s21_decimal decimal = get_new_decimal();

    s21_from_int_to_decimal(value, &decimal);

    return decimal;
}

void clear_decimal(s21_decimal* decimal) {
    decimal->bits[0] = 0;
    decimal->bits[1] = 0;
    decimal->bits[2] = 0;
    decimal->bits[3] = 0;
}

int get_count_full_digits(s21_decimal decimal) {
    int count = 0;

    for (int i = 127; i >= 0 && count == 0; i--) {
        if (s21_get_bit(decimal.bits[i / 32], i % 32)) {
            count = i + 1;
        }
    }

    return count;
}

int check_decimal(s21_decimal decimal) {
    int result_code = 0;

    int exponent = get_decimal_exponent(decimal);
    if (exponent < 0 || exponent > 28) {
        result_code = 1;
    }

    return result_code;
}

int check_int_range(s21_decimal decimal) {
    int is_error = 0;

    s21_decimal truncated_decimal = {0};
    s21_truncate(decimal, &truncated_decimal);
    
    s21_decimal min_decimal_for_int = {0};
    min_decimal_for_int.bits[0] = 0X80000000; // 1000...000
    set_decimal_sign(&min_decimal_for_int, 1);

    s21_decimal max_decimal_for_int = {0};
    max_decimal_for_int.bits[0] = 0X7FFFFFFF; // 0111...111
    set_decimal_sign(&max_decimal_for_int, 0);
    
    if (s21_is_greater(truncated_decimal, max_decimal_for_int) || s21_is_less(truncated_decimal, min_decimal_for_int)) {
        is_error = 1;
    }

    return is_error;
}

void s21_decimal_equalize(s21_decimal value_1, s21_decimal value_2, s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
    int exponent_1 = get_decimal_exponent(value_1), exponent_2 = get_decimal_exponent(value_2);

    set_decimal_exponent(&value_1, 0);
    set_decimal_exponent(&value_2, 0);

    set_decimal_sign(&value_1, 0);
    set_decimal_sign(&value_2, 0);

    big_value_1->decimal[0] = value_1;
    big_value_2->decimal[0] = value_2;
    
    if (exponent_1 > exponent_2) {
       *big_value_2 = s21_big_mul(*big_value_2, s21_get_big_decimal_ten_pow(exponent_1 - exponent_2));
    } else if (exponent_1 < exponent_2) {
        *big_value_1 = s21_big_mul(*big_value_1, s21_get_big_decimal_ten_pow(exponent_2 - exponent_1));
    }
}

s21_big_decimal s21_get_big_decimal_ten_pow(int pow) {
    s21_big_decimal big_decimal = {{get_decimal_with_int_value(1), get_new_decimal()}};

    for (int i = 0; i < pow; i++) {
        s21_big_decimal tmp_decimal = big_decimal;
        for (int j = 0; j < 9; j++) {
            big_decimal = s21_big_add(big_decimal, tmp_decimal);
        }
    }
    
    return big_decimal;
}

s21_big_decimal s21_left_shift_big_decimal(s21_big_decimal value, int count_shift) {
    while (count_shift > 0) {
        int is_set_one = 0;
        for (int i = 0; i < 8; i++) {
            int decimal_index = i / 4;
            
            int tmp_is_set_one = s21_get_bit(value.decimal[decimal_index].bits[i % 4], 31);

            value.decimal[decimal_index].bits[i % 4] = (unsigned int)(value.decimal[decimal_index].bits[i % 4]) << 1;
            if (is_set_one == 1) {
                value.decimal[decimal_index].bits[i % 4] = s21_set_bit(value.decimal[decimal_index].bits[i % 4], 0);
            }

            is_set_one = tmp_is_set_one;
        }

        count_shift--;
    }

    return value;
}

s21_big_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
    s21_decimal half_one = get_decimal_with_int_value(5);
    set_decimal_exponent(&half_one, 1);
    
    s21_big_decimal big_one = {{get_decimal_with_int_value(1), get_new_decimal()}};
    s21_big_decimal big_integral = {{integral, get_new_decimal()}};
    s21_big_decimal big_result = {{get_new_decimal(), get_new_decimal()}};

    if (s21_is_equal(fractional, half_one)) {
        if ((integral.bits[0] & 1) == 0) {
            big_result.decimal[0] = integral;
        } else {
            big_result = s21_big_add(big_integral, big_one);
            // result_code = s21_add(integral, get_decimal_with_int_value(1), result);
        }
    } else if (s21_is_greater(fractional, half_one)) {
        big_result = s21_big_add(big_integral, big_one);
        // result_code = s21_add(integral, get_decimal_with_int_value(1), result);
    } else {
        big_result.decimal[0] = integral;
    }

    return big_result;
}

s21_decimal s21_decimal_not(s21_decimal decimal) {
    s21_decimal result = get_new_decimal();
    result.bits[0] = ~decimal.bits[0];
    result.bits[1] = ~decimal.bits[1];
    result.bits[2] = ~decimal.bits[2];
    result.bits[3] = ~decimal.bits[3];

    return result;
}

s21_decimal s21_decimal_and(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = get_new_decimal();
    result.bits[0] = decimal1.bits[0] & decimal2.bits[0];
    result.bits[1] = decimal1.bits[1] & decimal2.bits[1];
    result.bits[2] = decimal1.bits[2] & decimal2.bits[2];
    result.bits[3] = decimal1.bits[3] & decimal2.bits[3];

    return result;
}

s21_decimal s21_decimal_xor(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = get_new_decimal();
    result.bits[0] = decimal1.bits[0] ^ decimal2.bits[0];
    result.bits[1] = decimal1.bits[1] ^ decimal2.bits[1];
    result.bits[2] = decimal1.bits[2] ^ decimal2.bits[2];
    result.bits[3] = decimal1.bits[3] ^ decimal2.bits[3];

    return result;
}

s21_decimal s21_remove_useless_zeros(s21_decimal value) {
    s21_decimal result = value;

    int exponent = get_decimal_exponent(value);
    int sign = get_decimal_sign(value);

    s21_big_decimal ten_big_decimal = {{get_decimal_with_int_value(10), get_new_decimal()}};

    if (exponent > 0 && !check_decimal(value)) {
        s21_decimal div_integral = value;

        set_decimal_exponent(&div_integral, 0);
        set_decimal_sign(&div_integral, 0);
        
        int has_useless_zeros = 1;
        while (has_useless_zeros && exponent > 0) {
            s21_big_decimal tmp_div_integral = {{div_integral, get_new_decimal()}};
            s21_big_decimal tmp_div_remainder = {{get_new_decimal(), get_new_decimal()}};

            s21_big_div(tmp_div_integral, ten_big_decimal, &tmp_div_integral, &tmp_div_remainder);

            div_integral = tmp_div_integral.decimal[0];
            s21_decimal div_remainder = tmp_div_remainder.decimal[0];

            if (s21_is_equal(div_remainder, get_decimal_with_int_value(0))) {
                result = div_integral;
                exponent--;
            } else {
                has_useless_zeros = 0;
            }
        }
        
        set_decimal_exponent(&result, exponent);
        set_decimal_sign(&result, sign);
    }

    return result;
}

int s21_count_digits_out_bounds(s21_big_decimal value) {
    int count = 0;

    s21_big_decimal ten_big_decimal = {{get_decimal_with_int_value(10), get_new_decimal()}};
    
    while (!s21_is_full_equal_zero(value.decimal[1]) || value.decimal[0].bits[3] != 0) {
        s21_big_decimal tmp = {{get_new_decimal(), get_new_decimal()}};
        s21_big_div(value, ten_big_decimal, &value, &tmp);
        count++;
    }
    
    return count;
}