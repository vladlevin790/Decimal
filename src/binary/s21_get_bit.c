#include "s21_binary_operations.h"

int s21_get_bit(int src, int index) { 
return (src >> index) & 1; 
}
