

// Получение бита из числа по индексу
int s21_get_bit(int src, int index) {
    return (src >> index) & 1;
}

// Устанавливает бит числа по индексу
int s21_set_bit(int src, int index)  {
    return src | (1 << index);
}

// Сбрасывает бит числа по индексу
int s21_clear_bit(int src, int index)  {
    return src & ~(1 << index);
}
