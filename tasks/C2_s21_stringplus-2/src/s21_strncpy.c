#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int src_len = s21_strlen(src);
  int change_len = src_len < (int)n ? (src_len + 1) : (int)n;

  for (int i = 0; i < change_len; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  return dest;
}