#include <check.h>

#include "../../s21_decimal.h"
#include "../test.h"

#define TRUE 1
#define FALSE 0

static s21_decimal as[] = {
    {{1, 0, 0, 0}},           {{1, 0, 0, 1u << 31}},
    {{1, 0, 0, 15 << 16}},    {{1, 0, 0, 22 << 16}},
    {{0, 1, 0, 15 << 16}},    {{0, 1, 0, 15 << 16}},
    {{11, 22, 33, 15 << 16}}, {{11, 22, 33, 15 << 16}},
    {{11, 22, 33, 15 << 16}}, {{0, 0, 0, (1 << 31) | (15 << 16)}},
    {{2, 0, 0, 0}},           {{15, 0, 0, 1 << 31}}};

static s21_decimal bs[] = {{{1, 0, 0, 1u << 31}},    {{1, 0, 0, 0}},
                           {{1, 0, 0, 10 << 16}},    {{1, 0, 0, 23 << 16}},
                           {{1, 0, 0, 15 << 16}},    {{0, 0, 1, 15 << 16}},
                           {{10, 22, 33, 15 << 16}}, {{11, 23, 33, 15 << 16}},
                           {{11, 22, 33, 15 << 16}}, {{0, 0, 0, 26 << 16}},
                           {{2000, 0, 0, 3 << 16}},  {{14, 0, 0, 1 << 31}}};

static int ress[][12] = {{FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE,
                          FALSE, FALSE, FALSE, TRUE},
                         {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                          FALSE, TRUE, TRUE, TRUE, FALSE},
                         {FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE,
                          TRUE, TRUE, TRUE, TRUE},
                         {TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE,
                          FALSE, FALSE, FALSE, FALSE},
                         {TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE,
                          TRUE, TRUE, TRUE, FALSE},
                         {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE,
                          FALSE, FALSE, TRUE}};

enum {
  pos_neg,
  neg_pos,
  greater_exp,
  less_exp,
  greater_digit,
  less_digit,
  greater_value,
  less_value,
  same_value,
  zeros,
  diff_records_same_vals,
  less_value_neg
};

enum { less, equal, less_or_equal, greater, greater_or_equal, not_equal };

#define FOO_NAME less
#include "tests_template.h"

#define FOO_NAME equal
#include "tests_template.h"

#define FOO_NAME less_or_equal
#include "tests_template.h"

#define FOO_NAME greater
#include "tests_template.h"

#define FOO_NAME greater_or_equal
#include "tests_template.h"

#define FOO_NAME not_equal
#include "tests_template.h"

Suite *s21_decimal_comp_op_suite() {
  Suite *s = suite_create("s21_decimal_comp_op");

  suite_add_tcase(s, tc_s21_is_less());
  suite_add_tcase(s, tc_s21_is_equal());
  suite_add_tcase(s, tc_s21_is_less_or_equal());
  suite_add_tcase(s, tc_s21_is_greater());
  suite_add_tcase(s, tc_s21_is_greater_or_equal());
  suite_add_tcase(s, tc_s21_is_not_equal());

  return s;
}
