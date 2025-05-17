#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"

void test_asin_acos(long double (*foo)(double),
                    long double (*expect)(long double)) {
  {
    double xs[] = {
        0.654321987, 0.,          1.,  0.0000005,    0.9999995,
        0.123456789, 0.987654321, -1., -0.123456789,
    };

    for (int i = 0; i < 9; i++) {
      ck_assert_ldouble_eq_tol(foo(xs[i]), expect(xs[i]), 1e-16);
    }
  }
  {
    double xs[] = {S21_NAN, -S21_NAN, S21_INF, -S21_INF};
    for (int i = 0; i < 4; i++) {
      ck_assert_ldouble_nan(foo(xs[i]));
    }
  }
}

START_TEST(test_s21_asin) { test_asin_acos(s21_asin, asinl); }
END_TEST

START_TEST(test_s21_acos) { test_asin_acos(s21_acos, acosl); }
END_TEST

START_TEST(test_s21_atan) {
  double xs[] = {
      0.654321987, 0.,         1.,     0.0000005, 0.9999995,    0.123456789,
      0.987654321, 987654321., 5.5,    -1.,       -0.123456789, -987654321.005,
      -5.5,        1.234,      -1.234, S21_INF,   -S21_INF};

  for (int i = 0; i < 17; i++) {
    ck_assert_ldouble_eq_tol(s21_atan(xs[i]), atanl(xs[i]), 1e-19);
  }
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
  ck_assert_ldouble_nan(s21_atan(-S21_NAN));
}
END_TEST

START_TEST(test_s21_abs) {
  int test_01 = -10909;
  int test_02 = 0;
  int test_03 = 26;

  ck_assert_int_eq(s21_abs(test_01), abs(test_01));
  ck_assert_int_eq(s21_abs(test_02), abs(test_02));
  ck_assert_int_eq(s21_abs(test_03), abs(test_03));
}
END_TEST

START_TEST(test_s21_fabs) {
  double test_01 = -10.9;
  double test_02 = 0;
  double test_03 = 2.6;
  ck_assert_double_eq(s21_fabs(test_01), fabs(test_01));
  ck_assert_double_eq(s21_fabs(test_02), fabs(test_02));
  ck_assert_double_eq(s21_fabs(test_03), fabs(test_03));
}
END_TEST

START_TEST(test_s21_sqrt) {
  const long double eps = 1e-20;

  double test_01 = 25;
  double test_02 = 0;
  double test_03 = -25;
  double test_04 = S21_NAN;
  double test_05 = S21_INF;
  double test_06 = 0.0000000000000000000225;

  ck_assert_ldouble_eq_tol(s21_sqrt(test_01), sqrtl(test_01), eps);
  ck_assert_ldouble_eq_tol(s21_sqrt(test_02), sqrtl(test_02), eps);
  ck_assert_ldouble_eq_tol(s21_sqrt(test_06), sqrtl(test_06), eps);
  ck_assert_ldouble_nan(s21_sqrt(test_03));
  ck_assert_ldouble_nan(s21_sqrt(test_04));
  ck_assert_ldouble_infinite(s21_sqrt(test_05));
}
END_TEST

START_TEST(test_s21_sin) {
  double test_01 = -3.14;
  double test_02 = 0.11;
  double test_03 = 26;
  const long double EPS = 1e-17;
  ck_assert_ldouble_eq_tol(s21_sin(test_01), sinl(test_01), EPS);
  ck_assert_ldouble_eq_tol(s21_sin(test_02), sinl(test_02), EPS);
  ck_assert_ldouble_eq_tol(s21_sin(test_03), sinl(test_03), EPS);
}
END_TEST

START_TEST(test_s21_cos) {
  double test_01 = -10.9;
  double test_02 = 0.1234;
  double test_03 = 2.6;
  const long double EPS = 1e-17;
  ck_assert_ldouble_eq_tol(s21_cos(test_01), cosl(test_01), EPS);
  ck_assert_ldouble_eq_tol(s21_cos(test_02), cosl(test_02), EPS);
  ck_assert_ldouble_eq_tol(s21_cos(test_03), cosl(test_03), EPS);
}
END_TEST

START_TEST(test_s21_tan) {
  double test_01 = 1.33;
  double test_02 = 0.7;
  double test_03 = -25;
  const long double EPS = 1e-17;
  ck_assert_ldouble_eq_tol(s21_tan(test_01), tanl(test_01), EPS);
  ck_assert_ldouble_eq_tol(s21_tan(test_02), tanl(test_02), EPS);
  ck_assert_ldouble_eq_tol(s21_tan(test_03), tanl(test_03), EPS);
}
END_TEST

START_TEST(test_s21_ceil) {
  double t[] = {-5.3456564, 0, 43.45645, 12, 3};

  ck_assert_int_eq(s21_ceil(t[0]), ceil(t[0]));
  ck_assert_int_eq(s21_ceil(t[1]), ceil(t[1]));
  ck_assert_int_eq(s21_ceil(t[2]), ceil(t[2]));
  ck_assert_int_eq(s21_ceil(t[3]), ceil(t[3]));
  ck_assert_int_eq(s21_ceil(t[4]), ceil(t[4]));
}
END_TEST

START_TEST(test_s21_floor) {
  double t[] = {-5.3456564, 0, 43.45645, 12, 3};

  ck_assert_int_eq(s21_floor(t[0]), floor(t[0]));
  ck_assert_int_eq(s21_floor(t[1]), floor(t[1]));
  ck_assert_int_eq(s21_floor(t[2]), floor(t[2]));
  ck_assert_int_eq(s21_floor(t[3]), floor(t[3]));
  ck_assert_int_eq(s21_floor(t[4]), floor(t[4]));
}
END_TEST

START_TEST(test_s21_fmod) {
  double t[] = {-5.3456564, 88.43545345, 43.45645, 2.23454, S21_INF, S21_NAN};

  ck_assert_int_eq(s21_fmod(t[0], t[1]), fmod(t[0], t[1]));
  ck_assert_int_eq(s21_fmod(t[1], t[2]), fmod(t[1], t[2]));
  ck_assert_int_eq(s21_fmod(t[2], t[3]), fmod(t[2], t[3]));
  ck_assert_int_eq(s21_fmod(t[3], t[4]), fmod(t[3], t[4]));
  ck_assert_int_eq(s21_fmod(t[3], t[5]), fmod(t[3], t[5]));
}
END_TEST

START_TEST(test_s21_exp) {
  double x1 = 100;
  double x2 = 21000;
  double x3 = -0.21;
  double x4 = -0.000000021;
  double x5 = 0;

  ck_assert_double_eq(s21_exp(x1), exp(x1));
  ck_assert_double_eq(s21_exp(x2), exp(x2));
  ck_assert_double_eq(s21_exp(x3), exp(x3));
  ck_assert_double_eq(s21_exp(x4), exp(x4));
  ck_assert_double_eq(s21_exp(x5), exp(x5));
}
END_TEST

START_TEST(test_s21_log) {
  double x1 = 100;
  double x2 = 21000;
  double x3 = 0.021;
  double x4 = 0;

  ck_assert_double_eq(s21_log(x1), log(x1));
  ck_assert_double_eq(s21_log(x2), log(x2));
  ck_assert_double_eq(s21_log(x3), log(x3));
  ck_assert_double_eq(s21_log(x4), log(x4));
}
END_TEST

START_TEST(test_s21_pow) {
  double eps = 0.0000001;

  double base1 = 2;
  double exp1 = 8;
  double base2 = 0;
  double exp2 = 0;
  double base3 = 0.21;
  double exp3 = 0.5;
  double base4 = 1;
  double exp4 = 1;
  double base5 = 12345;
  double exp5 = 12345;
  double base6 = -2;
  double exp6 = -8;
  double base7 = -5;
  double exp7 = 2.5;

  ck_assert(fabsl(s21_pow(base1, exp1) - pow(base1, exp1)) <= eps);
  ck_assert(fabsl(s21_pow(base2, exp1) - pow(base2, exp1)) <= eps);
  ck_assert(fabsl(s21_pow(base2, exp2) - pow(base2, exp2)) <= eps);
  ck_assert(fabsl(s21_pow(base1, exp2) - pow(base1, exp2)) <= eps);
  ck_assert(fabsl(s21_pow(base3, exp1) - pow(base3, exp1)) <= eps);
  ck_assert(fabsl(s21_pow(base1, exp3) - pow(base1, exp3)) <= eps);
  ck_assert(fabsl(s21_pow(base4, exp5) - pow(base4, exp5)) <= eps);
  ck_assert(fabsl(s21_pow(base5, exp4) - pow(base5, exp4)) <= eps);
  ck_assert(fabsl(s21_pow(base1, exp6) - pow(base1, exp6)) <= eps);
  ck_assert(fabsl(s21_pow(base6, exp1) - pow(base6, exp1)) <= eps);
  ck_assert_ldouble_nan(s21_pow(base7, exp7));
}
END_TEST

Suite *s21_math_suite(void) {
  Suite *s = suite_create("s21_math");
  TCase *tc_s21_sin, *tc_s21_cos, *tc_s21_tan;

  tc_s21_sin = tcase_create("s21_sin");
  tcase_add_test(tc_s21_sin, test_s21_sin);
  suite_add_tcase(s, tc_s21_sin);

  tc_s21_cos = tcase_create("s21_cos");
  tcase_add_test(tc_s21_cos, test_s21_cos);
  suite_add_tcase(s, tc_s21_cos);

  tc_s21_tan = tcase_create("s21_tan");
  tcase_add_test(tc_s21_tan, test_s21_tan);
  suite_add_tcase(s, tc_s21_tan);

  TCase *tc_s21_asin = tcase_create("s21_asin");
  tcase_add_test(tc_s21_asin, test_s21_asin);
  suite_add_tcase(s, tc_s21_asin);

  TCase *tc_s21_acos = tcase_create("s21_acos");
  tcase_add_test(tc_s21_acos, test_s21_acos);
  suite_add_tcase(s, tc_s21_acos);

  TCase *tc_s21_atan = tcase_create("s21_atan");
  tcase_add_test(tc_s21_atan, test_s21_atan);
  suite_add_tcase(s, tc_s21_atan);
  TCase *tc_s21_ceil, *tc_s21_floor, *tc_s21_fmod;

  tc_s21_ceil = tcase_create("S21_ceil");
  tcase_add_test(tc_s21_ceil, test_s21_ceil);
  suite_add_tcase(s, tc_s21_ceil);

  tc_s21_floor = tcase_create("S21_floor");
  tcase_add_test(tc_s21_floor, test_s21_floor);
  suite_add_tcase(s, tc_s21_floor);

  tc_s21_fmod = tcase_create("S21_fmod");
  tcase_add_test(tc_s21_fmod, test_s21_fmod);
  suite_add_tcase(s, tc_s21_fmod);
  TCase *tc_s21_abs, *tc_s21_fabs, *tc_s21_sqrt;

  tc_s21_abs = tcase_create("S21_abs");
  tcase_add_test(tc_s21_abs, test_s21_abs);
  suite_add_tcase(s, tc_s21_abs);

  tc_s21_fabs = tcase_create("s21_fabs");
  tcase_add_test(tc_s21_fabs, test_s21_fabs);
  suite_add_tcase(s, tc_s21_fabs);

  tc_s21_sqrt = tcase_create("s21_sqrt");
  tcase_add_test(tc_s21_sqrt, test_s21_sqrt);
  suite_add_tcase(s, tc_s21_sqrt);
  TCase *tc_s21_exp, *tc_s21_log, *tc_s21_pow;

  tc_s21_exp = tcase_create("s21_exp");
  tcase_add_test(tc_s21_exp, test_s21_exp);
  suite_add_tcase(s, tc_s21_exp);

  tc_s21_log = tcase_create("s21_log");
  tcase_add_test(tc_s21_log, test_s21_log);
  suite_add_tcase(s, tc_s21_log);

  tc_s21_pow = tcase_create("s21_pow");
  tcase_add_test(tc_s21_pow, test_s21_pow);
  suite_add_tcase(s, tc_s21_pow);

  return s;
}

int main(void) {
  Suite *s = s21_math_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
