#include "../../s21_decimal.h"
#include "../uint_n_arithm/uint_n_arithm.h"
#include "../utils/utils.h"
#include "ret_values.h"
#include "utils/utils.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret_val = OK;
  if (is_negative(&value_1) && is_negative(&value_2)) {
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    ret_val = s21_sub(value_2, value_1, result);
  } else if (is_negative(&value_1) && is_positive(&value_2)) {
    set_sign(&value_1, 0);
    ret_val = negate(s21_add(value_1, value_2, result), result);
  } else if (is_positive(&value_1) && is_negative(&value_2)) {
    set_sign(&value_2, 0);
    ret_val = s21_add(value_2, value_1, result);
  } else if (s21_is_less(value_1, value_2) == 1) {
    ret_val = negate(s21_sub(value_2, value_1, result), result);
  } else {
    equalize_exp(&value_1, &value_2);
    s21_uint_n_sub(value_1.bits, 3, value_2.bits, 3, result->bits);
    set_sign(result, 0);
    set_exp(result, get_exp(&value_1));
  }
  return ret_val;
}
