#ifndef S21_DECIMAL_UTILS_H_984613
#define S21_DECIMAL_UTILS_H_984613

#include <stdbool.h>
#include <stdint.h>

#include "../../s21_decimal.h"

uint8_t get_exp(s21_decimal *self);

uint8_t get_sign(s21_decimal *self);

char set_exp(s21_decimal *self, uint8_t exp);

char set_sign(s21_decimal *self, uint8_t sign);

bool is_positive(s21_decimal *self);

bool is_negative(s21_decimal *self);

#endif
