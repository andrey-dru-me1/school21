#include <string.h>

#include "../../s21_decimal.h"
#include "../uint_n_arithm/uint_n_arithm.h"
#include "../utils/utils.h"
#include "ret_values.h"
#include "utils/utils.h"

static int sum_positives(s21_decimal v1, s21_decimal v2, s21_decimal *r) {
  int ret_val = OK;
  s21_decimal res = {};

  equalize_exp(&v1, &v2);
  uint8_t res_exp = get_exp(&v1);

  uint32_t add_res = s21_uint_n_add(v1.bits, 3, v2.bits, 3, false, res.bits);
  if (add_res > 0 && res_exp == 0) {
    ret_val = INF;
  } else if (add_res > 0) {
    uint32_t int_res[4] = {0, 0, 0, 1};
    res_exp--;
    memcpy(int_res, res.bits, 3 * sizeof(uint32_t));
    bank_ten_div(int_res, 4, true, int_res);
    memcpy(res.bits, int_res, 3 * sizeof(uint32_t));
  }
  if (ret_val == OK) {
    set_exp(&res, res_exp);
    set_sign(&res, 0);
    memcpy(r, &res, sizeof(res));
  }
  return ret_val;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret_val = OK;
  if (is_negative(&value_1) && is_positive(&value_2)) {
    s21_negate(value_1, &value_1);
    ret_val = s21_sub(value_2, value_1, result);
  } else if (is_positive(&value_1) && is_negative(&value_2)) {
    s21_negate(value_2, &value_2);
    ret_val = s21_sub(value_1, value_2, result);
  } else if (is_negative(&value_1) && is_negative(&value_2)) {
    s21_negate(value_1, &value_1);
    s21_negate(value_2, &value_2);
    ret_val = negate(s21_add(value_1, value_2, result), result);
  } else
    ret_val = sum_positives(value_1, value_2, result);
  return ret_val;
}
