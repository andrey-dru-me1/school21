#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return s21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t res_len = src_len + str_len;

  if (start_index > src_len) return s21_NULL;

  char *insert_result = (char *)calloc(res_len + 1, sizeof(char));

  if (!insert_result) return s21_NULL;

  s21_memcpy(insert_result, src, start_index);
  s21_memcpy(&insert_result[start_index], str, str_len);
  s21_memcpy(&insert_result[start_index + str_len], &src[start_index],
             src_len - start_index);
  insert_result[res_len] = '\0';

  return (void *)insert_result;
}