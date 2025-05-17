#include "s21_string.h"

char *s21_strstr(const char *str_1, const char *str_2) {
  const char *res = s21_NULL;
  while (*str_1 != '\0' && res == s21_NULL) {
    if (*str_1 == *str_2 || *str_2 == 0) {
      const char *match_1 = str_1;
      const char *match_2 = str_2;
      while (*match_2 != '\0' && *match_1 == *match_2) {
        match_1++;
        match_2++;
      }
      if (*match_2 == '\0') {
        res = str_1;
      }
    }
    str_1++;
  }
  return (char *)res;
}
