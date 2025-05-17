#ifndef DECIMAL_ARITH_UTILS_H
#define DECIMAL_ARITH_UTILS_H

#include <stdbool.h>
#include <stddef.h>

#include "../../../s21_decimal.h"

int negate(int ret_val, s21_decimal *number);

bool bank_ten_div(uint32_t *number, size_t int_len, bool all_zeros,
                  uint32_t *res);

void equalize_exp(s21_decimal *value_1, s21_decimal *value_2);

bool is_zero(uint32_t *number, size_t int_count);

#endif
