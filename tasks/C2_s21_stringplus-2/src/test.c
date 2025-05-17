#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_s21_strlen) {
  char *t1 = "";
  char *t2 = "!";
  char *t3 = "how R U?";
  ck_assert_int_eq(s21_strlen(t1), strlen(t1));
  ck_assert_int_eq(s21_strlen(t2), strlen(t2));
  ck_assert_int_eq(s21_strlen(t3), strlen(t3));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char *t1 = " hello!";
  char *t2 = "gun?";
  char *t3 = " ";
  char *t4 = "mmm!";
  char *t5 = "lol";
  char *t6 = "leaks";
  char *t7 = "";
  ck_assert_int_eq(s21_strcspn(t1, t2), strcspn(t1, t2));
  ck_assert_int_eq(s21_strcspn(t1, t3), strcspn(t1, t3));
  ck_assert_int_eq(s21_strcspn(t1, t4), strcspn(t1, t4));
  ck_assert_int_eq(s21_strcspn(t1, t5), strcspn(t1, t5));
  ck_assert_int_eq(s21_strcspn(t1, t6), strcspn(t1, t6));
  ck_assert_int_eq(s21_strcspn(t1, t7), strcspn(t1, t7));
  ck_assert_int_eq(s21_strcspn(t7, t1), strcspn(t7, t1));
}
END_TEST

START_TEST(s21_strrchr_test) {
  const char *stroc[] = {"programm inginClanguage", "rt333", "2we\tt", "eww",
                         "lolkek"};
  int c[] = {'m', '3', 'r', 'w', 0};

  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_eq(s21_strrchr(stroc[i], c[i]), strrchr(stroc[i], c[i]));
  }
}
END_TEST

START_TEST(s21_strchr_test) {
  const char *stroc[] = {"programm inginClanguage",
                         "rt333",
                         "2we\tt",
                         "eww",
                         "",
                         "r",
                         "l\0;",
                         "lolkek"};
  int c[] = {'m', '3', 'r', 'w', 'l', 'r', '\t', 0};

  for (int i = 0; i < 8; i++) {
    ck_assert_ptr_eq(s21_strchr(stroc[i], c[i]), strchr(stroc[i], c[i]));
  }
}
END_TEST

START_TEST(s21_strstr_test) {
  const char *restr_1[] = {"programming in C language",
                           "apple r",
                           "100492334",
                           "eww",
                           "helloy world",
                           "wewe",
                           ""};
  const char *restr_2[] = {"C", "r", "9", "uu", "rld2^12", "", "e"};

  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(s21_strstr(restr_1[i], restr_2[i]),
                     strstr(restr_1[i], restr_2[i]));
  }
}
END_TEST

START_TEST(s21_strpbrk_test) {
  const char *restr_1[] = {"programming in C language",
                           "apple r",
                           "100492334",
                           "eww",
                           "helloy world",
                           "wewe",
                           ""};
  const char *restr_2[] = {"Cpr", "p", "9", "uu", "rld2^12", "", "e"};

  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(s21_strpbrk(restr_1[i], restr_2[i]),
                     strpbrk(restr_1[i], restr_2[i]));
  }
}
END_TEST

START_TEST(s21_memchr_test) {
  const char *restr_1[] = {"programming in C language",
                           "apple r",
                           "100492334",
                           "eww",
                           "helloy world",
                           "wewe",
                           ""};
  char restr_2[] = {'i', 'r', '9', 'w', 'o', 'p', '1'};
  size_t ns[] = {15, 3, 7, 2, 3, 2, 1, 4};

  for (int i = 0; i < 7; i++) {
    ck_assert_ptr_eq(s21_memchr(restr_1[i], restr_2[i], ns[i]),
                     memchr(restr_1[i], restr_2[i], ns[i]));
  }
}
END_TEST

START_TEST(test_s21_strncmp) {
  char *t1 = "";
  char *t2 = " scare?";
  char *t3 = " scream!";
  char *t4 = "Run";
  size_t k1 = 1;
  size_t k2 = 4;
  size_t k3 = 15;
  size_t k4 = 0;

  ck_assert_uint_eq(s21_strncmp(t1, t2, k1) < 0, strncmp(t1, t2, k1) < 0);
  ck_assert_uint_eq(s21_strncmp(t1, t2, k2) < 0, strncmp(t1, t2, k2) < 0);
  ck_assert_uint_eq(s21_strncmp(t2, t3, k1) == 0, strncmp(t2, t3, k1) == 0);
  ck_assert_uint_eq(s21_strncmp(t2, t3, k3) < 0, strncmp(t2, t3, k3) < 0);
  ck_assert_uint_eq(s21_strncmp(t3, t2, k3) > 0, strncmp(t3, t2, k3) > 0);
  ck_assert_uint_eq(s21_strncmp(t2, t4, k2) < 0, strncmp(t2, t4, k2) < 0);
  ck_assert_uint_eq(s21_strncmp(t2, t4, k3) < 0, strncmp(t2, t4, k3) < 0);
  ck_assert_uint_eq(s21_strncmp(t4, t3, k4) > 0, strncmp(t4, t3, k4) > 0);
}
END_TEST

START_TEST(test_s21_strncat) {
  char test1_1[100] = "Hello";
  char test1_2[100] = "Hello";
  const char test2_1[] = "World";
  const char test2_2[] = "World";
  char test3_1[100] = "@#&^!";
  char test3_2[100] = "@#&^!";
  const char test4_1[] = " ";
  const char test4_2[] = " ";
  char test5_1[100] = "";
  char test5_2[100] = "";
  const char test6_1[] = "123";
  const char test6_2[] = "123";
  char test7_1[100] = "T=m.Yg?jbgVE^Cf!>sXf#";
  char test7_2[100] = "T=m.Yg?jbgVE^Cf!>sXf#";
  const char test8_1[] = "AP.gfG,z@G^GKJ@R.*+R#HsLH";
  const char test8_2[] = "AP.gfG,z@G^GKJ@R.*+R#HsLH";
  s21_size_t n1 = 6;
  s21_size_t n2 = 1;
  s21_size_t n3 = 0;
  s21_size_t n4 = 10;

  ck_assert_str_eq(s21_strncat(test1_1, test2_1, n1),
                   strncat(test1_2, test2_2, n1));
  ck_assert_str_eq(s21_strncat(test3_1, test4_1, n2),
                   strncat(test3_2, test4_2, n2));
  ck_assert_str_eq(s21_strncat(test5_1, test6_1, n3),
                   strncat(test5_2, test6_2, n3));
  ck_assert_str_eq(s21_strncat(test7_1, test8_1, n4),
                   strncat(test7_2, test8_2, n4));
}
END_TEST

START_TEST(test_s21_strerror) {
  int test1 = 1;
  int test2 = -1;
  int test3 = 0;
  int test4 = 100;
  int test5 = 123456;

  ck_assert_str_eq(s21_strerror(test1), strerror(test1));
  ck_assert_str_eq(s21_strerror(test2), strerror(test2));
  ck_assert_str_eq(s21_strerror(test3), strerror(test3));
  ck_assert_str_eq(s21_strerror(test4), strerror(test4));
  ck_assert_str_eq(s21_strerror(test5), strerror(test5));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char t1[] = "";
  char t2[] = " scare?";
  char t3[] = " scream!";
  char t4[] = "Run";
  size_t k1 = 0;
  size_t k2 = 1;
  size_t k3 = 4;

  ck_assert_uint_eq(s21_memcmp(t1, t2, k1) == 0, memcmp(t1, t2, k1) == 0);
  ck_assert_uint_eq(s21_memcmp(t2, t3, k1) == 0, memcmp(t2, t3, k1) == 0);
  ck_assert_uint_eq(s21_memcmp(t2, t3, k2) == 0, memcmp(t2, t3, k2) == 0);
  ck_assert_uint_eq(s21_memcmp(t2, t4, k2) < 0, memcmp(t2, t4, k2) < 0);
  ck_assert_uint_eq(s21_memcmp(t4, t2, k3) > 0, memcmp(t4, t2, k3) > 0);
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1[] = "1,2.3/4!5";
  const char delim1[] = "!,./";
  char str2[] = "!&*V)C xZ@tAN.P ! YCy),R";
  const char delim2[] = " ";
  char str3[] = "Hello, world!";
  const char delim3[] = "\0";
  char str4[] = "///////helloworld";
  const char delim4[] = "/";
  char str5[] = " ";
  const char delim5[] = "";
  char str6[] = "s&wENHrU&LU##ynsg,Z*lSXMMrAi^vO#*dJt*P!upK@!ClO(EW";
  const char delim6[] = "f/Xb.Ad,XkeDyqXLhxAqI*w&Fd^#t)xjgmw#XM#dGdt!Hl.VG";

  ck_assert_str_eq(s21_strtok(str1, delim1), strtok(str1, delim1));
  ck_assert_str_eq(s21_strtok(str2, delim2), strtok(str2, delim2));
  ck_assert_str_eq(s21_strtok(str3, delim3), strtok(str3, delim3));
  ck_assert_str_eq(s21_strtok(str4, delim4), strtok(str4, delim4));
  ck_assert_str_eq(s21_strtok(str5, delim5), strtok(str5, delim5));
  ck_assert_str_eq(s21_strtok(str6, delim6), strtok(str6, delim6));
}
END_TEST

START_TEST(test_s21_to_upper) {
  char str1[] = "hello";
  char str2[] = "HeLLllLLo";
  char str3[] = "";

  char *upped1 = s21_to_upper(str1);
  char *upped2 = s21_to_upper(str2);
  char *upped3 = s21_to_upper(str3);

  ck_assert_str_eq(upped1, "HELLO");
  ck_assert_str_eq(upped2, "HELLLLLLO");
  ck_assert_str_eq(upped3, "");

  free(upped1);
  free(upped2);
  free(upped3);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char str1[] = "HELLO";
  char str2[] = "HeLLllLLo";
  char str3[] = "";

  char *lower1 = s21_to_lower(str1);
  char *lower2 = s21_to_lower(str2);
  char *lower3 = s21_to_lower(str3);

  ck_assert_str_eq(lower1, "hello");
  ck_assert_str_eq(lower2, "hellllllo");
  ck_assert_str_eq(lower3, "");

  free(lower1);
  free(lower2);
  free(lower3);
}
END_TEST

START_TEST(test_s21_trim) {
  char str[] = " QWERTY ";
  char trim1[] = "";
  char trim2[] = "1";
  char trim3[] = "TY Q";

  char *res = s21_trim(str, trim1);
  ck_assert_str_eq(res, "QWERTY");
  free(res);

  res = s21_trim(str, trim2);
  ck_assert_str_eq(res, " QWERTY ");
  free(res);

  res = s21_trim(str, trim3);
  ck_assert_str_eq(res, "WER");
  free(res);

  res = s21_trim("    Geeks00000", "0");
  ck_assert_str_eq(res, "    Geeks");
  free(res);

  res = s21_trim("*123xyz********c******c", "*1c");
  ck_assert_str_eq(res, "23xyz");
  free(res);

  res = s21_trim("", "*1c");
  ck_assert_str_eq(res, "");
  free(res);

  res = s21_trim(s21_NULL, "*1c");
  ck_assert_ptr_null(res);
  free(res);

  res = s21_trim("", s21_NULL);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_sprintf_ordinary_case) {
  char lib_res[256] = {0};
  char imp_res[256] = {0};

#define TEST_SPRINTF(...)                                \
  {                                                      \
    ck_assert_int_eq(sprintf(lib_res, __VA_ARGS__),      \
                     s21_sprintf(imp_res, __VA_ARGS__)); \
    ck_assert_str_eq(lib_res, imp_res);                  \
  }

  TEST_SPRINTF("Ordinary string");
  TEST_SPRINTF("Format%dstring%cwith%%digits%xwith%idifferent%oradix%u%X", -563,
               'j', 123789, INT_MAX, 123456, UINT_MAX, 987654);
  TEST_SPRINTF("Check for floating numbers: %f, %f, %f", -123.456, 5.5555555,
               5.);
  TEST_SPRINTF("Check for scientific notation: %e, %e, %e, %e", 123.456,
               5.5555555, 5., -0.000658);
  TEST_SPRINTF("Check for upper scientific notation: %E, %E, %E, %E", 123.456,
               5.5555555, 5., -0.000658);
  TEST_SPRINTF("Check for printing plus: %+e, %e, %+f, %f, %i, %+i", 15.3, 15.3,
               55.6, 55.6, 24, 24);
  TEST_SPRINTF("Check for printing width: %15i, %15u, %15f, %15e", -789, 789,
               -123.456, -123.456);
  TEST_SPRINTF("Check strings: %s, %s, %15s", "lol kek chebureck",
               "What\ndoes\n\tthe fox say?", "short");
  TEST_SPRINTF("Check leading zeros: %0d %015d", 156, 156);
  TEST_SPRINTF("Check left alignment: %-15s %-15d", "lol", -156);
  TEST_SPRINTF("Check place for sign: % d % d", 156, -156);
  TEST_SPRINTF("Check precision: %.15d %.15d %.3f %.0f %.5e", 156, -156,
               -1.666666, -1.132, -7.456);
  TEST_SPRINTF("Check length specifier: %lld %llu %hu %Lf %Le",
               (long long int)INT64_MAX, (long long unsigned)UINT64_MAX,
               (short unsigned)UINT32_MAX, (long double)123.123123123,
               (long double)123.123123123);
  TEST_SPRINTF("Check char alignment: %15c %15c %-15c", '\n', 's', 's');
  TEST_SPRINTF("Check double round: %.0f %.0f %.0f %.0f %.0f", 15.5, 15.49,
               -15.5, -15.49, -15.51);
  TEST_SPRINTF("Check scientific notation alignment: %15e %-15e %15e", 5.5,
               -5.5, 2.12e123);
}
END_TEST

START_TEST(test_s21_memcpy) {
  char t1[100] = "908hack agent";
  char t2[100] = "007_James";
  char t3[100] = " // // ";
  ck_assert_str_eq(s21_memcpy(t1, t2, 2), memcpy(t1, t2, 2));
  ck_assert_str_eq(s21_memcpy(t2, t3, 3), memcpy(t2, t3, 3));
  ck_assert_str_eq(s21_memcpy(t1, t3, 5), memcpy(t1, t3, 5));
}
END_TEST

START_TEST(test_s21_memset) {
  char str1[100] = "908hack agent";
  char test_1 = 'u';
  char test_2 = '/';
  char test_3 = ' ';
  char test_4 = '\n';
  size_t n1 = 7;
  size_t n2 = 6;
  size_t n3 = 5;
  size_t n4 = 4;
  ck_assert_str_eq(s21_memset(str1, test_1, n1), memset(str1, test_1, n1));
  ck_assert_str_eq(s21_memset(str1, test_2, n2), memset(str1, test_2, n2));
  ck_assert_str_eq(s21_memset(str1, test_3, n3), memset(str1, test_3, n3));
  ck_assert_str_eq(s21_memset(str1, test_4, n4), memset(str1, test_4, n4));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char str_1[] = "908hack agent";
  char str_2[] = "908hack agent";
  char str_3[] = "908hack agent";
  char str_4[] = "908hack agent";
  char str_5[20] = "908hack agent";
  char substr_1[] = "0123";
  char substr_2[] = "012";
  char substr_3[] = "01234";
  char substr_4[] = "0123567";
  char substr_5[] = "0123567";
  size_t n1 = 4;
  size_t n2 = 4;
  size_t n3 = 3;
  size_t n4 = 0;
  size_t n5 = 19;
  ck_assert_str_eq(s21_strncpy(str_1, substr_1, n1),
                   strncpy(str_1, substr_1, n1));
  ck_assert_str_eq(s21_strncpy(str_2, substr_2, n2),
                   strncpy(str_2, substr_2, n2));
  ck_assert_str_eq(s21_strncpy(str_3, substr_3, n3),
                   strncpy(str_3, substr_3, n3));
  ck_assert_str_eq(s21_strncpy(str_4, substr_4, n4),
                   strncpy(str_4, substr_4, n4));
  ck_assert_str_eq(s21_strncpy(str_5, substr_5, n5),
                   strncpy(str_5, substr_5, n5));
}
END_TEST

START_TEST(test_s21_insert) {
  char test_1_1[] = "908hack agent";
  // char test_1_2[] = "\0";
  char test_2[] = " // // /";
  char test_3[] = " ";
  char test_4[] = "u";
  char test_5[] = "!";
  char test_6[] = "/n";

  s21_size_t ind_2 = 3;
  s21_size_t ind_3 = 0;
  s21_size_t ind_4 = 2;
  s21_size_t ind_5 = 13;
  s21_size_t ind_6 = 14;

  char *result_2 = s21_insert(test_1_1, test_2, ind_2);
  char *result_3 = s21_insert(test_1_1, test_3, ind_3);
  char *result_4 = s21_insert(test_1_1, test_4, ind_4);
  char *result_5 = s21_insert(test_1_1, test_5, ind_5);
  // char *result_7 = s21_insert(test_1_2, test_2, ind_3);

  ck_assert_str_eq(result_2, "908 // // /hack agent");
  ck_assert_str_eq(result_3, " 908hack agent");
  ck_assert_str_eq(result_4, "90u8hack agent");
  ck_assert_str_eq(result_5, "908hack agent!");
  ck_assert_pstr_eq(s21_insert(test_1_1, test_6, ind_6), s21_NULL);
  // ck_assert_str_eq(result_7, " // // /");

  free(result_2);
  free(result_3);
  free(result_4);
  free(result_5);
  // free(result_6);
  // free(result_7);
}
END_TEST

// ================== End of test definitions ===================

Suite *s21_math_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);

  TCase *tc_s21_strlen, *tc_s21_strcspn, *tc_s21_strncmp, *tc_s21_memcmp,
      *tc_s21_strncat, *tc_s21_strerror, *tc_s21_strtok, *tc_s21_trim,
      *tc_s21_strrchr, *tc_s21_strstr, *tc_s21_strchr, *tc_s21_strpbrk,
      *tc_s21_memchr, *tc_s21_to_upper, *tc_s21_to_lower, *tc_s21_memcpy,
      *tc_s21_memset, *tc_s21_strncpy, *tc_s21_insert;

  tc_s21_strrchr = tcase_create("s21_strrchr");
  tcase_add_test(tc_s21_strrchr, s21_strrchr_test);
  suite_add_tcase(s, tc_s21_strrchr);

  tc_s21_strstr = tcase_create("s21_strstr");
  tcase_add_test(tc_s21_strstr, s21_strstr_test);
  suite_add_tcase(s, tc_s21_strstr);

  tc_s21_strchr = tcase_create("s21_strchr");
  tcase_add_test(tc_s21_strchr, s21_strchr_test);
  suite_add_tcase(s, tc_s21_strchr);

  tc_s21_strpbrk = tcase_create("s21_strpbrk");
  tcase_add_test(tc_s21_strpbrk, s21_strpbrk_test);
  suite_add_tcase(s, tc_s21_strpbrk);

  tc_s21_memchr = tcase_create("s21_memchr");
  tcase_add_test(tc_s21_memchr, s21_memchr_test);
  suite_add_tcase(s, tc_s21_memchr);

  tc_s21_strlen = tcase_create("S21_strlen");
  tcase_add_test(tc_s21_strlen, test_s21_strlen);
  suite_add_tcase(s, tc_s21_strlen);

  tc_s21_strcspn = tcase_create("S21_strcspn");
  tcase_add_test(tc_s21_strcspn, test_s21_strcspn);
  suite_add_tcase(s, tc_s21_strcspn);

  tc_s21_strncmp = tcase_create("S21_strncmp");
  tcase_add_test(tc_s21_strncmp, test_s21_strncmp);
  suite_add_tcase(s, tc_s21_strncmp);

  tc_s21_memcmp = tcase_create("S21_memcmp");
  tcase_add_test(tc_s21_memcmp, test_s21_memcmp);
  suite_add_tcase(s, tc_s21_memcmp);

  tc_s21_strncat = tcase_create("s21_strncat");
  tcase_add_test(tc_s21_strncat, test_s21_strncat);
  suite_add_tcase(s, tc_s21_strncat);

  tc_s21_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_s21_strerror, test_s21_strerror);
  suite_add_tcase(s, tc_s21_strerror);

  tc_s21_strtok = tcase_create("s21_strtok");
  tcase_add_test(tc_s21_strtok, test_s21_strtok);
  suite_add_tcase(s, tc_s21_strtok);

  tc_s21_to_upper = tcase_create("s21_to_upper");
  tcase_add_test(tc_s21_to_upper, test_s21_to_upper);
  suite_add_tcase(s, tc_s21_to_upper);

  tc_s21_to_lower = tcase_create("s21_to_lower");
  tcase_add_test(tc_s21_to_lower, test_s21_to_lower);
  suite_add_tcase(s, tc_s21_to_lower);

  tc_s21_trim = tcase_create("s21_trim");
  tcase_add_test(tc_s21_trim, test_s21_trim);
  suite_add_tcase(s, tc_s21_trim);

  tc_s21_memcpy = tcase_create("s21_memcpy");
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy);
  suite_add_tcase(s, tc_s21_memcpy);

  tc_s21_memset = tcase_create("s21_memset");
  tcase_add_test(tc_s21_memset, test_s21_memset);
  suite_add_tcase(s, tc_s21_memset);

  tc_s21_strncpy = tcase_create("s21_strncpy");
  tcase_add_test(tc_s21_strncpy, test_s21_strncpy);
  suite_add_tcase(s, tc_s21_strncpy);

  tc_s21_insert = tcase_create("s21_insert");
  tcase_add_test(tc_s21_insert, test_s21_insert);
  suite_add_tcase(s, tc_s21_insert);

  tcase_add_test(tc_core, test_sprintf_ordinary_case);

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
