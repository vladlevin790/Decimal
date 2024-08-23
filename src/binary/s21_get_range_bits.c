#include "s21_binary_operations.h"

int s21_get_range_bits(int src, int start, int end) {
  return (src >> start) & ((1 << (end - start + 1)) - 1);
}
