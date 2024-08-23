#include "s21_binary_operations.h"

int s21_clear_bit(int src, int index) { return src & ~(1 << index); }
