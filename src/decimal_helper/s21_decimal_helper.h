#ifndef S21_DECIMAL_HELPER_H_
#define S21_DECIMAL_HELPER_H_

#include "../binary/s21_binary.h"
#include "../s21_decimal.h"

// @brief Получение знака десятичного числа
// @param s21_decimal число, в котором лежат bits
// @return 0 - положительное, 1 - отрицательное
int s21_get_decimal_sign(s21_decimal decimal);

// @brief Получение степени 10
// @param s21_decimal число, в котором лежат bits
// @return Степень 10
int s21_get_decimal_exponent(s21_decimal decimal);

// @brief Устанавливает знак числа
// @param s21_decimal* число, в котором лежат bits
// @param sign знак числа. Допустимые значения: 0 (для положительного знака), 1
// (для отрицательного знака)
void s21_set_decimal_sign(s21_decimal* decimal, int sign);

// @brief Устанавливает степени 10
// @param s21_decimal* число, в котором лежат bits
// @param exponent новая степень 10
void s21_set_decimal_exponent(s21_decimal* decimal, int exponent);

// @brief Получает значение бита у decimal в указанной позиции
// @param s21_decimal Указатель на структуру s21_decimal, в которой
// устанавливается значение разряда
// @param index Индекс разряда (0 - 95)
// @return Значение бита (0 или 1)
int s21_get_decimal_digit_by_index(s21_decimal decimal, int index);

// @brief Создает и инициализирует новый экземпляр структуры s21_decimal
// @return Новый экземпляр структуры s21_decimal
s21_decimal s21_get_new_decimal();

// @brief Создает и инициализирует новый экземпляр структуры s21_decimal со
// значением
// @param value Значение decimal
// @return Новый экземпляр структуры s21_decimal
s21_decimal s21_get_decimal_with_int_value(int value);

// @brief Сбрасывает все биты у s21_decimal
// @param s21_decimal* Указатель на структуру s21_decimal
void s21_clear_decimal(s21_decimal* decimal);

int s21_get_count_full_digits(s21_decimal decimal);

// @brief Проверяет, является ли s21_decimal корректным
// @param s21_decimal число
// @return 0 - число является корректным, 1 - в противном случае
int s21_check_decimal(s21_decimal decimal);

// @brief Проверяет, находится ли int в допустимом диапазоне
// @param decimal - число, которое нужно проверить
// @return 0 - число находится в диапазоне, 1 - в противном случае
int s21_check_int_range(s21_decimal decimal);

void s21_decimal_equalize(s21_decimal value_1, s21_decimal value_2,
                          s21_big_decimal* big_value_1,
                          s21_big_decimal* big_value_2);
s21_big_decimal s21_left_shift_big_decimal(s21_big_decimal value,
                                           int shift_count);
s21_big_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional);
s21_big_decimal s21_get_big_decimal_ten_pow(int pow);
s21_decimal s21_decimal_not(s21_decimal decimal);
s21_decimal s21_decimal_and(s21_decimal decimal, s21_decimal decimal2);
s21_decimal s21_decimal_xor(s21_decimal decimal, s21_decimal decimal2);
s21_decimal s21_remove_useless_zeros(s21_decimal value);
int s21_count_digits_out_bounds(s21_big_decimal value);

#endif