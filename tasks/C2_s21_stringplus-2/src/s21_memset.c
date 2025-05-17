#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  for (int i = 0; i < (int)n; i++) {
    ((char *)str)[i] = (unsigned char)c;
  }

  return str;
}