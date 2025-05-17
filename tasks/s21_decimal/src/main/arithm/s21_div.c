#include <stdbool.h>
#include <string.h>

#include "../../s21_decimal.h"
#include "../uint_n_arithm/uint_n_arithm.h"
#include "../utils/utils.h"
#include "ret_values.h"
#include "utils/utils.h"

#define DIGIT_COUNT 9
#define FRACT_DIG_CNT (DIGIT_COUNT - 3)

static uint32_t search_for_quot_digit(uint32_t minuend[4], uint32_t divisor[3],
                                      uint32_t subtrahend[4]);
static int shift_exp(uint32_t quotient[DIGIT_COUNT], int res_exp);
static int round_result(uint32_t quotient[DIGIT_COUNT], int res_exp);

int div_non_zeros(s21_decimal dividend, s21_decimal divisor,
                  s21_decimal *result) {
  memset(result, 0, sizeof(*result));

  int res_exp = get_exp(&dividend) - get_exp(&divisor);

  uint32_t minuend[4] = {0};
  uint32_t quotient[DIGIT_COUNT] = {0};
  for (int res_idigit = DIGIT_COUNT - 1; res_idigit >= 0; res_idigit--) {
    memmove(minuend + 1, minuend, 3 * sizeof(unsigned));

    minuend[0] = res_idigit < FRACT_DIG_CNT
                     ? 0
                     : dividend.bits[res_idigit - FRACT_DIG_CNT];

    uint32_t subtrahend[4];
    quotient[res_idigit] =
        search_for_quot_digit(minuend, divisor.bits, subtrahend);

    s21_uint_n_sub(minuend, 4, subtrahend, 4, minuend);
  }

  res_exp = shift_exp(quotient, res_exp);
  res_exp = round_result(quotient, res_exp);

  char res_sign = get_sign(&dividend) ^ get_sign(&divisor);
  if (res_exp < 0) return res_sign == 1 ? NEG_INF : INF;

  memcpy(result->bits, quotient + FRACT_DIG_CNT, 3 * sizeof(uint32_t));

  set_exp(result, res_exp);
  set_sign(result, res_sign);
  return OK;
}

int s21_div(s21_decimal dividend, s21_decimal divisor, s21_decimal *result) {
  int ret_val = OK;
  if (is_zero(divisor.bits, 3)) {
    ret_val = ARITHM_ERR;
  } else if (is_zero(dividend.bits, 3)) {
    memset(result->bits, 0, 4 * sizeof(unsigned));
    ret_val = OK;
  } else
    ret_val = div_non_zeros(dividend, divisor, result);
  return ret_val;
}

static uint32_t search_for_quot_digit(uint32_t minuend[4], uint32_t divisor[3],
                                      uint32_t subtrahend[4]) {
  uint64_t l = 0, r = (uint64_t)1 << 32;
  uint32_t digit_guess;
  while (l + 1 < r) {
    digit_guess = (l + r) / 2;
    memset(subtrahend, 0, 4 * sizeof(uint32_t));
    s21_uint_n_mul(divisor, 3, digit_guess, true, subtrahend);
    if (s21_uint_n_cmp(minuend, 4, subtrahend, 4) < 0) {
      r = digit_guess;
    } else {
      l = digit_guess;
    }
  }

  if (digit_guess > l) {
    digit_guess--;
    s21_uint_n_sub(subtrahend, 4, divisor, 3, subtrahend);
  }
  return digit_guess;
}

static int shift_exp(uint32_t quotient[DIGIT_COUNT], int res_exp) {
  uint32_t prev_quot[DIGIT_COUNT];
  uint32_t overflow = 0;
  while (res_exp < 28 && overflow == 0) {
    memcpy(prev_quot, quotient, DIGIT_COUNT * sizeof(uint32_t));
    overflow = s21_uint_n_mul(quotient, DIGIT_COUNT, 10, false, quotient);
    res_exp++;
  }

  if (overflow != 0) {
    memcpy(quotient, prev_quot, DIGIT_COUNT * sizeof(uint32_t));
    res_exp--;
  }
  return res_exp;
}

static bool to_round_up(uint32_t num_to_round[DIGIT_COUNT]) {
  static uint32_t half[FRACT_DIG_CNT] = {0};
  half[FRACT_DIG_CNT - 1] = 1u << 31;
  char res_cmp;
  return ((res_cmp = s21_uint_n_cmp(num_to_round, FRACT_DIG_CNT, half,
                                    FRACT_DIG_CNT)) > 0 ||
          (res_cmp == 0 && num_to_round[FRACT_DIG_CNT] % 2 == 1));
}

static int round_result(uint32_t quotient[DIGIT_COUNT], int res_exp) {
  uint32_t prev_quot[3] = {0};
  memcpy(prev_quot, quotient + FRACT_DIG_CNT, 3 * sizeof(uint32_t));
  while (to_round_up(quotient) &&
         s21_uint_n_add(quotient + FRACT_DIG_CNT, 3, (uint32_t[1]){1}, 1, false,
                        quotient + FRACT_DIG_CNT) > 0) {
    memcpy(quotient + FRACT_DIG_CNT, prev_quot, 3 * sizeof(uint32_t));
    bank_ten_div(quotient, DIGIT_COUNT, true, quotient);
    res_exp--;
    memcpy(prev_quot, quotient + FRACT_DIG_CNT, 3 * sizeof(uint32_t));
  }
  return res_exp;
}
