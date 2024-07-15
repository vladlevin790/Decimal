#ifndef S21_DECIMAL_HELPER_H_
#define S21_DECIMAL_HELPER_H_

#include "../s21_decimal.h"
#include "../binary/s21_binary.h"

// @brief Получение знака десятичного числа
// @param s21_decimal число, в котором лежат bits
// @return 0 - положительное, 1 - отрицательное
int get_decimal_sign(s21_decimal decimal);

// @brief Получение степени 10
// @param s21_decimal число, в котором лежат bits
// @return Степень 10
int get_decimal_exponent(s21_decimal decimal);

// @brief Устанавливает знак числа
// @param s21_decimal* число, в котором лежат bits
// @param sign знак числа. Допустимые значения: 0 (для положительного знака), 1 (для отрицательного знака)
void set_decimal_sign(s21_decimal* decimal, int sign);

// @brief Устанавливает степени 10
// @param s21_decimal* число, в котором лежат bits
// @param exponent новая степень 10
void set_decimal_exponent(s21_decimal* decimal, int exponent);

// @brief Получает значение бита у decimal в указанной позиции
// @param s21_decimal Указатель на структуру s21_decimal, в которой устанавливается значение разряда
// @param index Индекс разряда (0 - 95)
// @return Значение бита (0 или 1)
int get_decimal_digit_by_index(s21_decimal decimal, int index);

// @brief Устанавливает бит для decimal в указанной позиции
// @param s21_decimal* Указатель на структуру s21_decimal, в которой устанавливается значение разряда
// @param index Индекс разряда (0 - 95)
// @param value Значение, которое устанавливается в разряд (0 или 1)
void set_decimal_digit_by_index(s21_decimal* decimal, int index, int value);

// @brief Побитово сдвигает число влево
// @param s21_decimal* Указатель на структуру s21_decimal
// @param shift Количество позиций для сдвига
// @return Код результата операции (0, если сдвиг возможен без потерь битов, 1 в противном случае)
int left_shift_decimal(s21_decimal *decimal, int shift);

// @brief Создает и инициализирует новый экземпляр структуры s21_decimal
// @return Новый экземпляр структуры s21_decimal
s21_decimal get_new_decimal();

// @brief Создает и инициализирует новый экземпляр структуры s21_decimal со значением
// @param value Значение decimal
// @return Новый экземпляр структуры s21_decimal
s21_decimal get_decimal_with_int_value(int value);

// @brief Создает и инициализирует новый экземпляр структуры s21_decimal со значением
// @param value Значение decimal
// @return Новый экземпляр структуры s21_decimal
s21_decimal get_decimal_with_float_value(float value);

// @brief Сбрасывает все биты у s21_decimal
// @param s21_decimal* Указатель на структуру s21_decimal
void clear_decimal(s21_decimal* decimal);

// @brief Получает количество битов в десятичном числе
// @param s21_decimal число
// @return Количество битов в десятичном числе
int get_count_digits(s21_decimal decimal);

// @brief Проверяет, является ли s21_decimal корректным
// @param s21_decimal число
// @return 0 - число является корректным, 1 - в противном случае
int check_decimal(s21_decimal decimal);

// @brief Проверяет, находится ли int в допустимом диапазоне
// @param decimal - число, которое нужно проверить
// @return 0 - число находится в диапазоне, 1 - в противном случае
int check_int_range(s21_decimal decimal);

#endif