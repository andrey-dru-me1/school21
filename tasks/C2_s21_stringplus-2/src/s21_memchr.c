#include "s21_string.h"

void *s21_memchr(const void *stroc, int c, s21_size_t n) {
  const void *res = s21_NULL;
  for (s21_size_t i = 0; i < n && res == s21_NULL; i++) {
    if (((char *)stroc)[i] == c) {
      res = (char *)stroc + i;
    }
  }
  return (void *)res;
}
