#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"
#include "uint_n_arithm/uint_n_arithm.h"
#include "utils/utils.h"

#define OK 0
#define CONVERTATION_ERR 1

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return CONVERTATION_ERR;
  }

  memset(dst, 0, sizeof(*dst));

  long long src_long = (long long)src;
  if (src < 0) {
    set_sign(dst, 1);
    src_long *= -1;
  }

  dst->bits[0] = src_long;
  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal result = {};
  int ret_val = OK;
  char str_for_float[36] = "";
  sprintf(str_for_float, "%+.28e", src);
  char first_dig_exp = str_for_float[33] - '0';
  char second_dig_exp = str_for_float[34] - '0';
  int8_t dig_exp = first_dig_exp * 10 + second_dig_exp;
  if (str_for_float[32] == '-') {
    dig_exp *= -1;
  }
  int8_t exp = 28 - dig_exp;

  for (int i = 1; i <= 30; i++) {
    s21_decimal before_result = result;
    if (str_for_float[i] == '.') i = i + 1;
    char digit = str_for_float[i] - '0';
    int overflow = s21_uint_n_mul(result.bits, 3, 10, false, result.bits);
    overflow |= s21_uint_n_add(result.bits, 3, (uint32_t[1]){digit}, 1, false,
                               result.bits);
    if (overflow > 0) {
      result = before_result;
      exp--;
      break;
    }
  }
  if (str_for_float[0] == '+') {
    set_sign(&result, 0);
  } else
    set_sign(&result, 1);

  while (exp < 0) {
    int over_mul_dec = s21_uint_n_mul(result.bits, 3, 10, false, result.bits);
    exp++;
    if (over_mul_dec > 0) return CONVERTATION_ERR;
  }
  while (exp > 28) {
    s21_uint_n_div(result.bits, 3, 10, result.bits);
    exp--;
  }
  set_exp(&result, exp);
  *dst = result;
  return ret_val;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return CONVERTATION_ERR;
  }

  int sign = get_sign(&src);
  unsigned int int_max = 2147483647;

  if ((src.bits[0] > int_max && sign == 0) ||
      (src.bits[0] > (int_max + 1) && sign == 1)) {
    return CONVERTATION_ERR;
  }

  uint8_t exp = get_exp(&src);
  size_t number_bits = 3;
  uint32_t divisor = 10;

  for (; exp != 0; exp--) {
    s21_uint_n_div(src.bits, number_bits, divisor, src.bits);
  }

  if ((src.bits[1] != 0) || (src.bits[2] != 0)) {
    return CONVERTATION_ERR;
  }

  *dst = src.bits[0];

  if (sign == 1) {
    *dst *= -1;
  }

  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return CONVERTATION_ERR;
  }
  const int exp = get_exp(&src);

  float res = src.bits[0] + src.bits[1] * 0x1p32 + src.bits[2] * 0x1p64;
  if (is_negative(&src)) res *= -1;
  for (int i = 0; i < exp; i++) {
    res /= 10;
  }
  *dst = res;
  return OK;
}
