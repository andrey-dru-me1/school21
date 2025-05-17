#include "utils.h"

#include "../../uint_n_arithm/uint_n_arithm.h"
#include "../../utils/utils.h"
#include "../ret_values.h"

int negate(int ret_val, s21_decimal *number) {
  if (ret_val == INF) {
    ret_val = NEG_INF;
  } else if (ret_val == NEG_INF) {
    ret_val = INF;
  } else if (ret_val == OK) {
    s21_negate(*number, number);
  }
  return ret_val;
}

bool bank_ten_div(uint32_t *number, size_t num_len, bool all_zeros,
                  uint32_t *res) {
  uint32_t rem = s21_uint_n_div(number, num_len, 10, res);
  if (rem > 5 || (rem == 5 && (res[0] % 2 == 1 || all_zeros == false))) {
    s21_uint_n_add(res, num_len, (uint32_t[1]){1}, 1, false, res);
  }
  if (rem != 0) all_zeros = false;
  return all_zeros;
}

void equalize_exp(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal *max_exp_num;
  s21_decimal *min_exp_num;
  if (get_exp(value_1) > get_exp(value_2)) {
    max_exp_num = value_1;
    min_exp_num = value_2;
  } else {
    max_exp_num = value_2;
    min_exp_num = value_1;
  }
  uint8_t exp_min = get_exp(min_exp_num);
  int diff = get_exp(max_exp_num) - exp_min;
  s21_decimal prev = *min_exp_num;
  while (diff > 0 && s21_uint_n_mul(min_exp_num->bits, 3, 10, false,
                                    min_exp_num->bits) == 0) {
    prev = *min_exp_num;
    exp_min++;
    diff--;
  }
  if (diff != 0) {
    *min_exp_num = prev;
  }

  bool all_zeros = true;
  while (diff > 0) {
    all_zeros =
        bank_ten_div(max_exp_num->bits, 3, all_zeros, max_exp_num->bits);
    diff--;
  }
  set_exp(value_1, exp_min);
  set_exp(value_2, exp_min);
}

bool is_zero(uint32_t *number, size_t int_count) {
  bool res = true;
  for (size_t i = 0; res && i < int_count; i++) {
    if (number[i] != 0) res = false;
  }
  return res;
}
