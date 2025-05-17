#include <stdbool.h>

#include "s21_string.h"

char *s21_strchr(const char *stroc, int c) {
  const char *res = s21_NULL;
  for (s21_size_t i = 0; i <= s21_strlen(stroc) && (res == s21_NULL); i++) {
    if (stroc[i] == c) {
      res = stroc + i;
    }
  }
  return (char *)res;
}
