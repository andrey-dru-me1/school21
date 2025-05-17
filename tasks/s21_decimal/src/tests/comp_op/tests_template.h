#ifdef FOO_NAME

#define TCAT(A, B, C) A##B##C
#define CAT(A, B, C) TCAT(A, B, C)
#define CAT2(A, B) CAT(A, B, )

#define TSTART_TEST(A) START_TEST(A)

#define STR(A) #A

#define SINGLE_TEST(TEST_NAME)                                              \
  TSTART_TEST(CAT(test_s21_is_, FOO_NAME, TEST_NAME)) {                     \
    ck_assert_int_eq(CAT2(s21_is_, FOO_NAME)(as[TEST_NAME], bs[TEST_NAME]), \
                     ress[FOO_NAME][TEST_NAME]);                            \
  }

SINGLE_TEST(pos_neg)
SINGLE_TEST(neg_pos)
SINGLE_TEST(greater_exp)
SINGLE_TEST(less_exp)
SINGLE_TEST(greater_digit)
SINGLE_TEST(less_digit)
SINGLE_TEST(greater_value)
SINGLE_TEST(less_value)
SINGLE_TEST(same_value)
SINGLE_TEST(zeros)
SINGLE_TEST(diff_records_same_vals)
SINGLE_TEST(less_value_neg)

TCase *CAT2(tc_s21_is_, FOO_NAME)() {
  TCase *tc = tcase_create("s21_" STR(FOO_NAME));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, pos_neg));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, neg_pos));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, greater_exp));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, less_exp));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, greater_digit));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, less_digit));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, greater_value));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, less_value));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, same_value));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, zeros));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, diff_records_same_vals));
  tcase_add_test(tc, CAT(test_s21_is_, FOO_NAME, less_value_neg));

  return tc;
}

#undef FOO_NAME

#endif
