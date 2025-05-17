#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t length = 0;
  int i = 0;
  while (*(str1 + length)) {
    for (i = 0; *(str2 + i) && (*(str1 + length) != *(str2 + i)); i++)
      ;
    if (*(str1 + length) == *(str2 + i)) break;
    length++;
  }
  return length;
}