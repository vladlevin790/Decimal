#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"

int s21_mul_handle(s21_big_decimal big_result, int result_exponent,
                   int count_out_bounds, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else {
    int result_sign =
        s21_get_decimal_sign(value_1) != s21_get_decimal_sign(value_2);
    int exponent_1 = s21_get_decimal_exponent(value_1),
        exponent_2 = s21_get_decimal_exponent(value_2);

    s21_set_decimal_sign(&value_1, 0);
    s21_set_decimal_sign(&value_2, 0);

    s21_set_decimal_exponent(&value_1, 0);
    s21_set_decimal_exponent(&value_2, 0);

    s21_big_decimal big_value_1 = {{value_1, s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {{value_2, s21_get_new_decimal()}};

    s21_big_decimal big_result = s21_big_mul(big_value_1, big_value_2);

    int count_out_bounds = s21_count_digits_out_bounds(big_result);
    int result_exponent = exponent_1 + exponent_2 - count_out_bounds;

    if (result_exponent < 0) {
      result_code = ERROR_OVERFLOW;
    } else {
      result_code =
          s21_mul_handle(big_result, result_exponent, count_out_bounds, result);
    }

    if (result_code == 0) {
      s21_set_decimal_sign(result, result_sign);
    } else if (result_code == 1 && result_sign == 1) {
      result_code = ERROR_UNDERFLOW;
    }
  }

  return result_code;
}

int s21_mul_handle(s21_big_decimal big_result, int result_exponent,
                   int count_out_bounds, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;
  s21_big_decimal ten_big_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};
  s21_big_decimal tmp = {{s21_get_new_decimal(), s21_get_new_decimal()}};

  // Если в decimal переполнение дробной части,
  // то прибавляем переполненную часть как вышедшую за границы
  if (result_exponent > 28) {
    count_out_bounds = result_exponent - 28 + count_out_bounds;
    result_exponent = 28;
  }

  // Отрасываем числа, переполненные более чем на 45 знака после запятой
  // 45 взято из шарпа, почему-то он отбрасывает знак после 45 при умножении
  while (count_out_bounds > 17) {
    s21_big_div(big_result, ten_big_decimal, &big_result, &tmp);
    count_out_bounds--;
  }

  s21_big_decimal div_remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};
  s21_big_decimal big_ten_pow = s21_get_big_decimal_ten_pow(count_out_bounds);

  // Окончательно убираем переполненную часть
  // Сохраняем остаток для округления и округляем
  s21_big_div(big_result, big_ten_pow, &big_result, &div_remainder);
  s21_set_decimal_exponent(&div_remainder.decimal[0], count_out_bounds);

  big_result =
      s21_round_banking(big_result.decimal[0], div_remainder.decimal[0]);

  if (!s21_is_full_equal_zero(big_result.decimal[1]) ||
      big_result.decimal[0].bits[3] != 0) {
    result_code = ERROR_OVERFLOW;
  } else {
    *result = big_result.decimal[0];
    s21_set_decimal_exponent(result, result_exponent);

    if (s21_is_equal(*result, s21_get_decimal_with_int_value(0)) &&
        s21_is_equal(div_remainder.decimal[0],
                     s21_get_decimal_with_int_value(0))) {
      *result = s21_remove_useless_zeros(*result);
    }
  }

  return result_code;
}

s21_big_decimal s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_big_decimal result = {{s21_get_new_decimal(), s21_get_new_decimal()}};

  int max_index = s21_get_count_full_digits(value_2.decimal[1]) - 1;
  max_index = max_index == -1
                  ? s21_get_count_full_digits(value_2.decimal[0]) - 1
                  : DECIMAL_MAX_BITS + max_index;

  for (int i = 0; i <= max_index; i++) {
    int curr_decimal = i / 128;
    int curr_bit = (i % 128) / 32;
    int curr_index = i % 32;

    if (s21_get_bit(value_2.decimal[curr_decimal].bits[curr_bit], curr_index)) {
      result = s21_big_add(result, value_1);
    }
    value_1 = s21_left_shift_big_decimal(value_1, 1);
  }

  return result;
}