#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return s21_NULL;
  char trim_default[7] = " \t\n\v\r\f\0";
  s21_size_t cut_left, cut_right, size_src, size_res;
  // Detrmine variables
  cut_left = 0;
  cut_right = 0;
  if (src == s21_NULL)
    size_src = 0;
  else
    size_src = s21_strlen(src);
  if (trim_chars == s21_NULL || s21_strlen(trim_chars) == 0)
    trim_chars = trim_default;

  s21_size_t i;
  // Count right characters to trim
  for (i = size_src; i > 0 && s21_strchr(trim_chars, src[i - 1]); i--) {
    cut_right++;
  }
  size_res = size_src - cut_right;

  // Count left characters to trim
  for (i = 0; i < size_res && s21_strchr(trim_chars, src[i]); i++) {
    cut_left++;
  }
  size_res -= cut_left;
  // Calculate result
  char *res = (char *)calloc(size_res + 1, sizeof(char));
  if (res != s21_NULL) {
    for (i = cut_left; i < size_src - cut_right; i++) {
      res[i - cut_left] = src[i];
    }
  }
  return res;
}
