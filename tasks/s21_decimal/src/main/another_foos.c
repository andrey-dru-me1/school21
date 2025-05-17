#include <string.h>

#include "../s21_decimal.h"
#include "arithm/utils/utils.h"
#include "uint_n_arithm/uint_n_arithm.h"
#include "utils/utils.h"

#define OK 0
#define CALC_ERR 1

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return CALC_ERR;
  uint8_t power = get_exp(&value);
  uint32_t rem = 0;
  while (power != 0) {
    rem |= s21_uint_n_div(value.bits, 3, 10, value.bits);
    power--;
  }
  memcpy(result->bits, value.bits, 3 * sizeof(uint32_t));
  set_exp(result, power);
  set_sign(result, get_sign(&value));
  if (is_negative(result) && rem != 0) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(*result, one, result);
  }
  set_sign(result, get_sign(&value));
  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return CALC_ERR;
  uint8_t power = get_exp(&value);
  bool all_zeros = true;
  while (power != 0) {
    all_zeros = bank_ten_div(value.bits, 3, all_zeros, value.bits);
    power--;
  }
  memcpy(result->bits, value.bits, 3 * sizeof(uint32_t));
  set_exp(result, power);
  set_sign(result, get_sign(&value));
  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return CALC_ERR;
  uint8_t power = get_exp(&value);
  while (power != 0) {
    s21_uint_n_div(value.bits, 3, 10, value.bits);
    power--;
  }
  memcpy(result->bits, value.bits, 3 * sizeof(uint32_t));
  set_exp(result, power);
  set_sign(result, get_sign(&value));
  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return CALC_ERR;
  memmove(result, &value, sizeof(value));
  set_sign(result, !get_sign(result));
  return OK;
}
