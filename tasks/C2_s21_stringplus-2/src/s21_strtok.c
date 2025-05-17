#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *str_ptr = s21_NULL;
  char *result = s21_NULL;

  if (str != s21_NULL) str_ptr = str;
  if (str_ptr == s21_NULL || *str_ptr == '\0') return s21_NULL;

  while (*str_ptr != '\0' && s21_strchr(delim, *str_ptr) != s21_NULL) {
    str_ptr++;
  }

  if (*str_ptr == '\0') return s21_NULL;

  result = str_ptr;

  while (*str_ptr != '\0' && s21_strchr(delim, *str_ptr) == s21_NULL) {
    str_ptr++;
  }

  if (*str_ptr == '\0') {
    str_ptr = s21_NULL;
  } else {
    *str_ptr = '\0';
    str_ptr++;
  }

  return result;
}
