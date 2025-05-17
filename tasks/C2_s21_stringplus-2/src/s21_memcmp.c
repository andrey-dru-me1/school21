#include "s21_string.h"

int s21_memcmp(const void *arr1, const void *arr2, s21_size_t n) {
  int res = 0;
  const unsigned char *ptr1, *ptr2;
  ptr1 = arr1;
  ptr2 = arr2;

  while (n) {
    res = *ptr1 - *ptr2;
    if (res) break;
    ptr1++;
    ptr2++;
    n--;
  }

  return res;
}