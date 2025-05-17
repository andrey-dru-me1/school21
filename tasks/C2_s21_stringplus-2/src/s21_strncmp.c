#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  if (n <= 0) return 0;
  int i = 0;

  while (i < (int)n && str1[i] && str2[i]) {
    if (str1[i] - str2[i]) {
      break;
    }
    i++;
  }

  return ((int)str1[i]) - ((int)str2[i]);
}