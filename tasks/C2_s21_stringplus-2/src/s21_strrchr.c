#include <stdbool.h>

#include "s21_string.h"

char *s21_strrchr(const char *stroc, int c) {
  const char *res = s21_NULL;
  for (s21_size_t i = 0; i <= s21_strlen(stroc); i++) {
    if (stroc[i] == c) {
      res = stroc + i;
    }
  }
  return (char *)res;
}
