#include <stdio.h>

#include "../test/test.h"

#define TYPE int
#define NAME int
#include "vector_decl.h"
#include "vector_defn.h"
#undef TYPE
#undef NAME

void test_vector_allocation();
void test_vec_add_i_int();
void test_vec_add_i_double();
void test_vec_add();
void test_vec_rm();
void test_vec_add_all();
void test_vec_add_all_i();

int main(void) {
  test_vector_allocation();
  test_vec_add_i_int();
  test_vec_add_i_double();
  test_vec_add();
  test_vec_rm();
  test_vec_add_all();
  test_vec_add_all_i();
}

void test_vector_allocation() {
  int_vec v;
  test(int_vec_alloc(0, &v) == SUCCESS && v.cap == 0 && v.len == 0 &&
           v.dat != NULL,
       "Allocation zero capacity");
  int_vec_free(&v);
  test(int_vec_alloc(12, &v) == SUCCESS && v.cap == 12 && v.len == 0 &&
           v.dat != NULL,
       "Allocation ordinary case");
  int_vec_free(&v);
}

void test_vec_rm() {
  int_vec v;
  int_vec_alloc(4, &v);
  int_vec_add(&v, 4);
  int_vec_add(&v, 3);
  int_vec_add(&v, 2);
  int_vec_add(&v, 1);
  test(int_vec_rm(&v, 0) == SUCCESS && v.len == 3 && v.dat[0] == 3 &&
           v.dat[1] == 2 && v.dat[2] == 1,
       "Remove zero elem");
  test(int_vec_rm(&v, 1) == SUCCESS && v.len == 2 && v.dat[0] == 3 &&
           v.dat[1] == 1,
       "Remove middle elem");
  test(int_vec_rm(&v, 1) == SUCCESS && v.len == 1 && v.dat[0] == 3,
       "Remove last elem");
  test(int_vec_rm(&v, -1) == INDEX_OUT_OF_BOUNDS, "Remove -1st elem");
  test(int_vec_rm(&v, 2) == INDEX_OUT_OF_BOUNDS, "Remove big'th elem");
  int_vec_free(&v);
}

void test_vec_add() {
  int_vec v;
  int_vec_alloc(0, &v);
  test(int_vec_add(&v, 7) == SUCCESS && v.cap >= v.len && v.len == 1 &&
           v.dat[0] == 7,
       "Vector addition to a zero capacity");
  test(int_vec_add(&v, 5) == SUCCESS && v.cap >= v.len && v.len == 2 &&
           v.dat[0] == 7 && v.dat[1] == 5,
       "Vector addition regular case");
  test(int_vec_add(&v, 3) == SUCCESS && v.cap >= v.len && v.len == 3 &&
           v.dat[0] == 7 && v.dat[1] == 5 && v.dat[2] == 3,
       "Vector addition regular case 2");
  int_vec_free(&v);
}

void test_vec_add_i_int() {
  int_vec v;
  int_vec_alloc(0, &v);
  test(int_vec_add_i(&v, 5, 0) == SUCCESS && v.cap >= v.len && v.len == 1 &&
           v.dat[0] == 5,
       "Vector i addition to a zero capacity");
  test(int_vec_add_i(&v, 5, -1) == INDEX_OUT_OF_BOUNDS,
       "Vector i addition insert to a -1 index");
  test(int_vec_add_i(&v, 5, 2) == INDEX_OUT_OF_BOUNDS,
       "Vector i addition insert to a big index");
  int_vec_free(&v);
}

#define TYPE double
#define NAME double
#include "vector_decl.h"
#include "vector_defn.h"
#undef TYPE
#undef NAME

void test_vec_add_i_double() {
  double_vec v;
  double_vec_alloc(12, &v);
  test(double_vec_add_i(&v, 4.7, 0) == SUCCESS && v.cap == 12 && v.len == 1 &&
           v.dat[0] == 4.7,
       "Vector i addition ordinary insertion");
  test(double_vec_add_i(&v, 1.5, 0) == SUCCESS && v.cap == 12 && v.len == 2 &&
           v.dat[0] == 1.5 && v.dat[1] == 4.7,
       "Vector i addition check array shifting");
  test(double_vec_add_i(&v, 7.7, 1) == SUCCESS && v.cap == 12 && v.len == 3 &&
           v.dat[0] == 1.5 && v.dat[1] == 7.7 && v.dat[2] == 4.7,
       "Vector i addition insert in a middle of array");
  test(double_vec_add_i(&v, 0.3, 0) == SUCCESS && v.cap == 12 && v.len == 4 &&
           v.dat[0] == 0.3 && v.dat[1] == 1.5 && v.dat[2] == 7.7 &&
           v.dat[3] == 4.7,
       "Vector i addition shift many values in array");
  test(double_vec_add_i(&v, 0.3, 4) == SUCCESS && v.cap == 12 && v.len == 5 &&
           v.dat[0] == 0.3 && v.dat[1] == 1.5 && v.dat[2] == 7.7 &&
           v.dat[3] == 4.7 && v.dat[4] == 0.3,
       "Vector i addition append to the end");
  double_vec_free(&v);
}

void test_vec_add_all() {
  double_vec v;
  double_vec_alloc(20, &v);
  test(double_vec_add_all(
           &v, (double_arr){.dat = (double[]){1.2, 2.3, 3.4, 4.5, 5.6, 6.7},
                            .len = 6}) == SUCCESS &&
           v.dat[0] == 1.2 && v.dat[1] == 2.3 && v.dat[2] == 3.4 &&
           v.dat[3] == 4.5 && v.dat[4] == 5.6 && v.dat[5] == 6.7,
       "Vector multiple elements addition");
  test(double_vec_add_all(&v, (double_arr){.dat = (double[]){7.8, 8.9},
                                           .len = 2}) == SUCCESS &&
           v.dat[0] == 1.2 && v.dat[1] == 2.3 && v.dat[2] == 3.4 &&
           v.dat[3] == 4.5 && v.dat[4] == 5.6 && v.dat[5] == 6.7 &&
           v.dat[6] == 7.8 && v.dat[7] == 8.9,
       "Vector multiple elements to the end addition");
  double_vec_free(&v);
}

void test_vec_add_all_i() {
  double_vec v;
  double_vec_alloc(20, &v);
  double_vec_add_all(
      &v,
      (double_arr){.dat = (double[]){1.2, 2.3, 3.4, 4.5, 5.6, 6.7}, .len = 6});
  test(double_vec_add_all_i(&v,
                            (double_arr){.dat = (double[]){7.8, 8.9}, .len = 2},
                            3) == SUCCESS &&
           v.dat[0] == 1.2 && v.dat[1] == 2.3 && v.dat[2] == 3.4 &&
           v.dat[3] == 7.8 && v.dat[4] == 8.9 && v.dat[5] == 4.5 &&
           v.dat[6] == 5.6 && v.dat[7] == 6.7,
       "Vector multiple elements to the i'th position addition");
  double_vec_free(&v);
}
