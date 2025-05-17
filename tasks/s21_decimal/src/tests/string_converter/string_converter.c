#include "string_converter.h"

#include "../../main/uint_n_arithm/uint_n_arithm.h"
#include "../../main/utils/utils.h"

void decimal_to_string(s21_decimal v, char *str) {
  int i = 0;
  char exp = get_exp(&v);
  str[i++] = is_negative(&v) ? '-' : '+';
  while (i < 31) {
    if (i - 1 == exp)
      str[i++] = '.';
    else
      str[i++] = '0' + s21_uint_n_div(v.bits, 3, 10, v.bits);
  }
  for (int j = 1; j <= 15; j++) {
    char c = str[31 - j];
    str[31 - j] = str[j];
    str[j] = c;
  }
  str[i++] = 0;
}
