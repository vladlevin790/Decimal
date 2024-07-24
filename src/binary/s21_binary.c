#include "s21_binary.h"

int s21_get_bit(int src, int index) { return (src >> index) & 1; }

int s21_get_range_bits(int src, int start, int end) {
  return (src >> start) & ((1 << (end - start + 1)) - 1);
}

int s21_set_bit(int src, int index) { return src | (1 << index); }

int s21_clear_bit(int src, int index) { return src & ~(1 << index); }