#include <stdlib.h>

#include "decimal_helper/s21_decimal_helper.h"
#include "s21_decimal.h"
#define DECIMAL_MAX_BITS 128

int s21_div_handle(s21_big_decimal value_2l, s21_big_decimal res,
                   s21_big_decimal remainder, s21_decimal *result);
int s21_div_calc_fractional(s21_big_decimal *res, s21_big_decimal value_2l,
                            s21_big_decimal *remainder);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  if (s21_check_decimal(value_1) || s21_check_decimal(value_2) ||
      result == NULL) {
    result_code = S21_DECIMAL_ERROR;
  } else if (s21_is_equal(value_2, s21_get_decimal_with_int_value(0))) {
    result_code = ERROR_DIVISION_BY_ZERO;
  } else {
    *result = s21_get_new_decimal();
    int sign1 = s21_get_decimal_sign(value_1),
        sign2 = s21_get_decimal_sign(value_2);

    s21_big_decimal big_value_1 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal big_value_2 = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    s21_big_decimal div_remainder = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_decimal div_whole = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};

    // Делим делимое на делитель
    // div_whole - целая часть деления, div_remainder - остаток от деления
    s21_big_div(big_value_1, big_value_2, &div_whole, &div_remainder);

    // Если целая часть деления не влезает в s21_decimal
    if (div_whole.decimal[0].bits[3] != 0 ||
        !s21_is_full_equal_zero(div_whole.decimal[1])) {
      if (sign1 != sign2) {
        result_code = ERROR_UNDERFLOW;
      } else {
        result_code = ERROR_OVERFLOW;
      }
    } else {
      // Получаем конечный результат на основе целой части и остатка от деления
      result_code =
          s21_div_handle(big_value_2, div_whole, div_remainder, result);

      if (result_code == 0 && sign1 != sign2) {
        s21_set_decimal_sign(result, 1);
      } else if (result_code == 1 && sign1 != sign2) {
        result_code = 2;
      }
    }
  }

  return result_code;
}

/// @brief Устанавливает целую часть деления и остаток на основе делимого и
/// делителя
/// @param decimal1 Делимое
/// @param decimal2 Делитель
/// @param div_whole Целая часть деления
/// @param div_remainder Остаток от деления
void s21_big_div(s21_big_decimal decimal1, s21_big_decimal decimal2,
                 s21_big_decimal *div_whole, s21_big_decimal *div_remainder) {
  s21_big_decimal whole = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};  // частное
  s21_big_decimal remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};  // остаток

  if (s21_is_less_big(decimal1, decimal2, 0, 0)) {
    remainder = decimal1;
  } else if (!s21_is_full_equal_zero(decimal1.decimal[0]) ||
             !s21_is_full_equal_zero(decimal1.decimal[1])) {
    // Деление целых чисел (без знака) с остатком

    int left_1 = s21_get_count_full_digits(decimal1.decimal[1]) - 1;
    left_1 = left_1 == -1 ? s21_get_count_full_digits(decimal1.decimal[0]) - 1
                          : DECIMAL_MAX_BITS + left_1;

    while (left_1 >= 0) {
      remainder = s21_left_shift_big_decimal(remainder, 1);

      if (s21_get_bit(decimal1.decimal[left_1 / 128].bits[(left_1 % 128) / 32],
                      left_1 % 32)) {
        remainder.decimal[0].bits[0] =
            s21_set_bit(remainder.decimal[0].bits[0], 0);
      }

      if (s21_is_greater_or_equal_big(remainder, decimal2, 0, 0)) {
        remainder = s21_big_sub(remainder, decimal2);
        whole.decimal[left_1 / 128].bits[(left_1 % 128) / 32] = s21_set_bit(
            whole.decimal[left_1 / 128].bits[(left_1 % 128) / 32], left_1 % 32);
      }

      left_1--;
    }
  }

  *div_whole = whole;
  *div_remainder = remainder;
}

/// @brief Получает дробную часть деления на основе остатка
/// @param value_2 Делитель
/// @param whole Целая часть деления (частное)
/// @param remainder Остаток от деления
/// @param result Результат высчитывания числа
/// @return Код ошибки
int s21_div_handle(s21_big_decimal value_2, s21_big_decimal whole,
                   s21_big_decimal remainder, s21_decimal *result) {
  int result_code = S21_DECIMAL_OK;

  // Получаем дробную часть из остатка
  // и записываем в remainder остаток, который не влез в decimal
  int power1 = s21_div_calc_fractional(&whole, value_2, &remainder);

  s21_big_decimal second_remainder = {
      {s21_get_new_decimal(), s21_get_new_decimal()}};

  // Получаем дробную часть, которая не влезла в decimal
  // и используем ее в банковском округлении
  int power2 = s21_div_calc_fractional(&second_remainder, value_2, &remainder);
  s21_set_decimal_exponent(&second_remainder.decimal[0], power2);
  whole = s21_round_banking(whole.decimal[0], second_remainder.decimal[0]);

  // Удаляем лишние нули из дробной части
  if (!s21_is_full_equal_zero(whole.decimal[0])) {
    s21_set_decimal_exponent(&whole.decimal[0], power1);
    whole.decimal[0] = s21_remove_useless_zeros(whole.decimal[0]);
  }

  if (!s21_is_full_equal_zero(whole.decimal[1]) ||
      s21_check_decimal(whole.decimal[0]) ||
      s21_get_range_bits(whole.decimal[0].bits[3], 0, 15) != 0 ||
      s21_get_range_bits(whole.decimal[0].bits[3], 24, 30) != 0) {
    result_code = 1;
  } else {
    *result = whole.decimal[0];
  }

  return result_code;
}

/// @brief Высчитывание дробной части на основе остатка и запись её в res
/// @param res частное
/// @param value_2l делитель
/// @param remainder остаток от деления
/// @return количество знаков после запятой у res
int s21_div_calc_fractional(s21_big_decimal *result, s21_big_decimal value_2l,
                            s21_big_decimal *remainder) {
  int exponent = 0;

  s21_big_decimal ten_decimal = {
      {s21_get_decimal_with_int_value(10), s21_get_new_decimal()}};

  // Пока остаток не равен 0 или пока decimal не переполнен
  int is_end = 0;
  while ((!s21_is_full_equal_zero(remainder->decimal[0]) ||
          !s21_is_full_equal_zero(remainder->decimal[1])) &&
         exponent < 28 && !is_end) {
    // Сохранение чисел, чтобы их вернуть, если будет переполнение decimal
    s21_big_decimal prev_result = *result;
    s21_big_decimal prev_remainder = *remainder;

    // Готовим место под новое число
    *result = s21_big_mul(*result, ten_decimal);
    // Умножаем текущий остаток на 10
    *remainder = s21_big_mul(*remainder, ten_decimal);

    // Делим остаток на делитель и получаем целую часть и остаток
    s21_big_decimal tmp_div_whole = {
        {s21_get_new_decimal(), s21_get_new_decimal()}};
    s21_big_div(*remainder, value_2l, &tmp_div_whole, remainder);

    // Целую часть от деления прибавляем к результату
    *result = s21_big_add(*result, tmp_div_whole);

    // Если decimal переполнен, то возвращаем предыдущий результат и выходим из
    // цикла
    if (s21_check_decimal(result->decimal[0]) ||
        s21_get_range_bits(result->decimal[0].bits[3], 0, 15) != 0 ||
        s21_get_range_bits(result->decimal[0].bits[3], 24, 30) != 0) {
      *result = prev_result;
      *remainder = prev_remainder;

      is_end = 1;
    } else {
      exponent++;
    }
  }

  return exponent;
}