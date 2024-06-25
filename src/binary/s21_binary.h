#ifndef S21_BINARY_H_
#define S21_BINARY_H_

// @brief Получение бита из числа по индексу
// @param src число, из которого нужно получить бит
// @param index индекс бита
// @return Возвращает значение бита числа по индексу (0 или 1)
int s21_get_bit(int src, int index);

// @brief Получение диапазона бит из числа с start до en
// @param src число, из которого нужно получить бит
// @param start начальный индекс бита
// @param end конечный индекс бита
// @return Возвращает диапазон бит в виде числа
int s21_get_range(int src, int start, int end);

// @brief Установка бита числа по индексу
// @param src число, для которого нужно установить бит
// @param index индекс бита
void s21_set_bit(int src, int index);

// @brief Сброс бита числа по индексу
// @param src число, для которого нужно сбросить бит
// @param index индекс бита
void s21_clear_bit(int src, int index);

#endif