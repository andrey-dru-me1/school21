#include "s21_string.h"

char *s21_strpbrk(const char *str, const char *sym) {
  const char *res = s21_NULL;

  for (s21_size_t i = 0; i < s21_strlen(str) && res == s21_NULL; i++) {
    char *match = s21_strchr(sym, str[i]);

    if (match != s21_NULL) {
      res = str + i;
    }
  }
  return (char *)res;
}
