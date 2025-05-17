#include "uint_n_arithm.h"

#define BASE (1L << 32)

#define MAX(A, B) ((A) > (B) ? (A) : (B))

char s21_uint_n_cmp(uint32_t *a, size_t a_len, uint32_t *b, size_t b_len) {
  size_t i = MAX(a_len, b_len);
  uint32_t a_i, b_i;
  do {
    a_i = (i <= a_len) ? a[i - 1] : 0;
    b_i = (i <= b_len) ? b[i - 1] : 0;
    i--;
  } while (i > 0 && a_i == b_i);
  return (a_i > b_i) - (a_i < b_i);
}

uint32_t s21_uint_n_mul(uint32_t *a, uint32_t a_len, uint32_t b,
                        bool additional_int, uint32_t *res) {
  uint64_t x = 0;
  for (size_t i = 0; i < a_len; i++) {
    x += (uint64_t)a[i] * b;
    res[i] = (uint32_t)x;
    x /= BASE;
  }

  uint32_t ret_val = 0;
  if (additional_int)
    res[a_len] = x;
  else
    ret_val = x;
  return ret_val;
}

uint32_t s21_uint_n_add(uint32_t *a, size_t a_len, uint32_t *b, size_t b_len,
                        bool additional_int, uint32_t *res) {
  uint32_t until = MAX(a_len, b_len);
  uint64_t x = 0;
  for (size_t i = 0; i < until; i++) {
    uint32_t a_i = (i < a_len) ? a[i] : 0, b_i = (i < b_len) ? b[i] : 0;
    x += (uint64_t)a_i + (uint64_t)b_i;
    res[i] = (uint32_t)x;
    x /= BASE;
  }

  uint32_t ret_val = 0;
  if (additional_int)
    res[until] = x;
  else
    ret_val = x;
  return ret_val;
}

uint32_t s21_uint_n_sub(uint32_t *minuend, size_t minuend_len,
                        uint32_t *subtrahend, size_t subtrahend_len,
                        uint32_t *res) {
  if (s21_uint_n_cmp(minuend, minuend_len, subtrahend, subtrahend_len) < 0)
    return (uint32_t)-1;

  size_t until = MAX(minuend_len, subtrahend_len);
  char overflow = 0;
  for (size_t i = 0; i < until; i++) {
    uint32_t a_i = (i < minuend_len) ? minuend[i] : 0,
             b_i = (i < subtrahend_len) ? subtrahend[i] : 0;
    if (a_i >= (uint64_t)b_i + overflow) {
      res[i] = a_i - overflow - b_i;
      overflow = 0;
    } else {
      res[i] = (uint64_t)BASE - b_i + a_i - overflow;
      overflow = 1;
    }
  }
  return 0;
}

uint32_t s21_uint_n_div(uint32_t *dividend, size_t divisible_len,
                        uint32_t divisor, uint32_t *res) {
  uint64_t x = 0;
  uint32_t rem = 0;
  for (int i = divisible_len - 1; i >= 0; i--) {
    x = ((uint64_t)rem << 32) | dividend[i];
    res[i] = x / divisor;
    rem = x % divisor;
  }
  return rem;
}
