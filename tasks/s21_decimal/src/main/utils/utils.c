#include "utils.h"

#define EXP_MASK 0x00ff0000
#define SIGN_MASK 0x80000000

uint8_t get_exp(s21_decimal *self) { return (self->bits[3] & EXP_MASK) >> 16; }

uint8_t get_sign(s21_decimal *self) {
  return (self->bits[3] & SIGN_MASK) >> 31;
}

char set_exp(s21_decimal *self, uint8_t exp) {
  if (exp > 28) return -1;
  self->bits[3] = (exp << 16) | (self->bits[3] & SIGN_MASK);
  return 0;
}

char set_sign(s21_decimal *self, uint8_t sign) {
  if (sign > 1) return -1;
  self->bits[3] = (sign << 31) | (self->bits[3] & EXP_MASK);
  return 0;
}

bool is_negative(s21_decimal *self) { return get_sign(self) > 0; }

bool is_positive(s21_decimal *self) { return get_sign(self) == 0; }
