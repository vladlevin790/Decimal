#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>

#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

int get_bit(s21_decimal number, int bit) {
  int sign;
  if ((number.bits[bit / 32] & (1 << bit % 32)) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }
  return sign;
}

void set_bit(s21_decimal *number, int bit, int sign) {
  if (sign == 0) {
    number->bits[bit / 32] = number->bits[bit / 32] & ~(1 << bit % 32);
  } else {
    number->bits[bit / 32] = number->bits[bit / 32] | (1 << bit % 32);
  }
}

void initial_num(s21_decimal *number) {
  for (int i = 0; i < 128; i++) {
    set_bit(number, i, 0);
  }
}

int s21_is_less_simple(s21_decimal dec1, s21_decimal dec2) {
  int is_less = FALSE;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(dec1, i) ^ get_bit(dec2, i)) {
      is_less = get_bit(dec2, i);
      break;
    }
  }

  return is_less;
}

int s21_is_less_or_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_less_simple(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_greater_simple(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_less_or_equal_simple(dec1, dec2);
}

int s21_is_greater_or_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_greater_simple(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_add_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
  initial_num(result);
  int rank = 0;
  for (int i = 0; i < 96; i++) {
    int bit_dec1 = get_bit(dec1, i);
    int bit_dec2 = get_bit(dec2, i);

    set_bit(result, i, bit_dec1 ^ bit_dec2 ^ rank);

    rank = (bit_dec1 && bit_dec2) || (bit_dec1 && rank) || (bit_dec2 && rank);
  }

  return rank;
}

void s21_sub_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
  initial_num(result);
  for (int i = 0; i < 96; i++) {
    int bit_dec1 = get_bit(dec1, i);
    int bit_dec2 = get_bit(dec2, i);

    set_bit(result, i, bit_dec1 ^ bit_dec2);

    if (!bit_dec1 && bit_dec2) {
      int k = i + 1;
      while ((bit_dec1 = get_bit(dec1, k)) != 1) {
        set_bit(&dec1, k, 1);
        k++;
      }
      set_bit(&dec1, k, 0);
    }
  }
}

int shift_left(s21_decimal *number) {
  int is_overflow = get_bit(*number, 95);
  for (int i = 95; i >= 0; i--) {
    if (i != 0) {
      set_bit(number, i, get_bit(*number, i - 1));
    } else {
      set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

int shift_right(s21_decimal *number) {
  int is_overflow = get_bit(*number, 1);
  for (int i = 0; i < 96; i++) {
    if (i != 95) {
      set_bit(number, i, get_bit(*number, i + 1));
    } else {
      set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

int s21_mul_simple(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
  s21_decimal tmp;
  initial_num(&tmp);
  int is_owerfull = 0;
  for (int i = 0; i < 96 && !is_owerfull; i++) {
    if (get_bit(dec2, i) == 1) {
      s21_decimal temp = dec1;
      int k = 0;
      while (k < i) {
        if (shift_left(&temp)) {
          is_owerfull = 1;
          break;
        }
        k++;
      }
      if (is_owerfull || (is_owerfull = s21_add_simple(temp, tmp, &tmp))) {
        break;
      }
    }
  }

  if (!is_owerfull)
    *result = tmp;

  return is_owerfull;
}

s21_decimal s21_div_simple(s21_decimal dec1, s21_decimal dec2,
                           s21_decimal *result) {
  if (result)
    initial_num(result);
  s21_decimal fmod = {0};
  s21_decimal temp = {0};
  if (s21_is_greater_or_equal_simple(dec1, dec2))
    set_bit(&temp, 0, 1);
  if (!s21_is_greater_simple(dec2, dec1)) {
    while (1) {
      s21_decimal copy_dec2 = dec2;
      while (s21_is_greater_or_equal_simple(dec1, copy_dec2) &&
             !(get_bit(dec1, 95) && get_bit(copy_dec2, 95))) {
        shift_left(&copy_dec2);
        shift_left(&temp);
      }

      if (!(get_bit(dec1, 95) && get_bit(copy_dec2, 95)) ||
          (s21_is_greater_or_equal_simple(copy_dec2, dec1))) {
        shift_right(&copy_dec2);
        shift_right(&temp);
      }

      s21_sub_simple(dec1, copy_dec2, &dec1);
      if (result)
        s21_add_simple(*result, temp, result);
      initial_num(&temp);
      set_bit(&temp, 0, 1);
      if (s21_is_less_simple(dec1, dec2)) {
        break;
      }
    }
  }
  fmod = dec1;
  return fmod;
}

void s21_bank_rounding(s21_decimal *value, int count) {
  int system_bit = value->bits[3];
  int exp = get_decimal_exponent(*value) - count;
  while (count > 0) {
    s21_decimal base = {0}, one = {0}, two = {0}, two_res = {0};
    s21_from_int_to_decimal(10, &base);
    s21_from_int_to_decimal(1, &one);
    s21_from_int_to_decimal(2, &two);
    s21_decimal dec_mod = s21_div_simple(*value, base, value);
    if (dec_mod.bits[0] > 5) {
      s21_add_simple(*value, one, value);
    } else if (dec_mod.bits[0] == 5) {
      two_res = s21_div_simple(*value, two, NULL);
      if (s21_is_equal(one, two_res))
        s21_add_simple(*value, one, value);
    }
    count--;
  }
  value->bits[3] = system_bit;
  set_decimal_exponent(value, exp);
}

void normalize(s21_decimal *dec1, s21_decimal *dec2) {
  int scl1 = get_decimal_exponent(*dec1);
  int scl2 = get_decimal_exponent(*dec2);

  int v1 = dec1->bits[3];
  int v2 = dec2->bits[3];

  int min_scl = (scl1 < scl2) ? scl1 : scl2;
  int max_scl = (scl1 > scl2) ? scl1 : scl2;
  s21_decimal *min_val = (scl1 < scl2) ? dec1 : dec2;
  s21_decimal *max_val = (scl1 > scl2) ? dec1 : dec2;
  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);

  while (min_scl != max_scl) {
    if (min_scl < 28 && !s21_mul_simple(*min_val, ten, min_val)) {
      min_scl++;
      set_decimal_exponent(min_val, min_scl);
    } else {
      s21_bank_rounding(max_val, max_scl - min_scl);
      break;
    }
  }

  dec1->bits[3] = v1;
  dec2->bits[3] = v2;
  set_decimal_exponent(min_val, min_scl);
  set_decimal_exponent(max_val, min_scl);
}

int s21_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
  if (result == s21_NULL) {
    return 1;
  }

  int add_res_code = S21_DECIMAL_OK;

  normalize(&dec1, &dec2);
  int exp = get_decimal_exponent(dec1);
  int sign_1 = get_decimal_sign(dec1);
  int sign_2 = get_decimal_sign(dec2);

  if (!(sign_1 ^ sign_2)) {
    add_res_code = s21_add_simple(dec1, dec2, result);
    set_decimal_sign(result, sign_1);
    if (add_res_code && sign_1 && sign_2) {
      add_res_code = ERROR_UNDERFLOW;
    }
  } else if (s21_is_less_or_equal_simple(dec1, dec2)) {
    s21_sub_simple(dec2, dec1, result);
    set_decimal_sign(result, sign_2);
  } else {
    s21_sub_simple(dec1, dec2, result);
    set_decimal_sign(result, sign_1);
  }

  if (add_res_code && get_decimal_exponent(dec1)) {
    s21_bank_rounding(&dec1, 1);
    s21_bank_rounding(&dec2, 1);
    add_res_code = s21_add(dec1, dec2, result);
  } else {
    set_decimal_exponent(result, exp);
  }

  return add_res_code;
}
