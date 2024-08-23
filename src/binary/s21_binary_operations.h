#ifndef S21_BINARY_H_
#define S21_BINARY_H_

// @brief Получение бита из числа по индексу
// @param src число, из которого нужно получить бит
// @param index индекс бита
// @return Значение бита числа по индексу (0 или 1)
int s21_get_bit(int src, int index);

// @brief Получение диапазона бит из числа с start до end
// @param src число, из которого нужно получить бит
// @param start начальный индекс бита (включительно)
// @param end конечный индекс бита (включительно)
// @return Диапазон бит в виде числа
int s21_get_range_bits(int src, int start, int end);

// @brief Установка бита числа по индексу
// @param src число, для которого нужно установить бит
// @param index индекс бита
// @return Число с установленным битом
int s21_set_bit(int src, int index);

// @brief Сброс бита числа по индексу
// @param src число, для которого нужно сбросить бит
// @param index индекс бита
// @return Число со сброшенным битом
int s21_clear_bit(int src, int index);

#endif