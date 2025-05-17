#include <string.h>

#include "../../s21_decimal.h"
#include "../uint_n_arithm/uint_n_arithm.h"
#include "../utils/utils.h"
#include "ret_values.h"
#include "utils/utils.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_exp = get_exp(&value_1) + get_exp(&value_2);
  char res_sign = get_sign(&value_1) ^ get_sign(&value_2);

  uint32_t add_res[6] = {};
  for (int i = 0; i < 3; i++) {
    uint32_t mul_res[4] = {};
    s21_uint_n_mul(value_1.bits, 3, value_2.bits[i], true, mul_res);
    s21_uint_n_add(add_res + i, 6 - i, mul_res, 4, false, add_res + i);
  }

  bool all_zeros = true;
  while ((!is_zero(add_res + 3, 3) || res_exp > 28) && res_exp >= 0) {
    all_zeros = bank_ten_div(add_res, 6, all_zeros, add_res);
    res_exp--;
  }

  int ret_val = OK;
  if (res_exp < 0)
    ret_val = (res_sign == 1) ? NEG_INF : INF;
  else {
    memset(result, 0, sizeof(*result));
    memcpy(result->bits, add_res, 3 * sizeof(uint32_t));

    set_sign(result, res_sign);
    set_exp(result, res_exp);
  }
  return ret_val;
}
