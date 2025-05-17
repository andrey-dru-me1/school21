#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "../test/test.h"
#include "command_line_parser.h"

typedef struct test_struct_s {
  char a, b, c, d;
} test_struct;

int a_handler(test_struct *obj, char **args);
int b_handler(test_struct *obj, char **args);
int c_handler(test_struct *obj, char **args);
int d_handler(test_struct *obj, char **args);

void test_command_line_parser_ordinary();
void test_clparser_long_ops();
void test_clparser_dash_without_op();
void test_clparser_wrong_op();
void test_clparser_wrong_args();
void test_clparser_non_existent_op();
void test_clparser_non_existent_long_op();
void test_clparser_multi_ops_arity_last();
void test_clparser_multi_ops_arity_outside();
void test_clparser_multi_ops_arity_inside();
void test_clparser_inline_op_param();
void test_clparser_inline_op_eq_param();
void test_clparser_wrong_inline_op_param();
void test_clparser_invalid_inline_op_param();
void test_clparser_invalid_eq();

option ops[] = {
    (option){.label = 'a',
             .long_label = "aaaa",
             .arity = 0,
             .apply = (int (*)(void *obj, char **args))a_handler},
    (option){.label = 'b',
             .long_label = "bar",
             .arity = 1,
             .apply = (int (*)(void *obj, char **args))b_handler},
    (option){.label = 'c',
             .arity = 0,
             .apply = (int (*)(void *obj, char **args))c_handler},
    (option){.label = 'd',
             .arity = 2,
             .apply = (int (*)(void *obj, char **args))d_handler},
};

op_arr available_options = {.dat = (void *)ops, .len = 4};

int main(void) {
  freopen("/dev/zero", "a", stderr);
  test_command_line_parser_ordinary();
  test_clparser_long_ops();
  test_clparser_dash_without_op();
  test_clparser_wrong_op();
  test_clparser_wrong_args();
  test_clparser_non_existent_op();
  test_clparser_non_existent_long_op();
  test_clparser_multi_ops_arity_last();
  test_clparser_multi_ops_arity_outside();
  test_clparser_multi_ops_arity_inside();
  test_clparser_inline_op_param();
  test_clparser_inline_op_eq_param();
  test_clparser_wrong_inline_op_param();
  test_clparser_invalid_inline_op_param();
  test_clparser_invalid_eq();
  return 0;
}

int a_handler(test_struct *obj, char **args) {
  (void)args;
  obj->a = 1;
  return 0;
}

int b_handler(test_struct *obj, char **args) {
  int exit = -1;
  if (args[0] && strcmp(args[0], "watermelon") == 0) {
    obj->b = 1;
    exit = 0;
  }
  return exit;
}

int c_handler(test_struct *obj, char **args) {
  (void)args;
  obj->c = 1;
  return 0;
}

int d_handler(test_struct *obj, char **args) {
  int exit = -1;
  if (args[0] && args[1] && strcmp(args[0], "juice") == 0 &&
      strcmp(args[1], "coffee") == 0) {
    obj->d = 1;
    exit = 0;
  }
  return exit;
}

void test_command_line_parser_ordinary() {
  str_arr input = {.dat = (char *[]){"-a", "-b", "watermelon", "melon", "grape",
                                     "-c", "-d", "juice", "coffee", "lemon"},
                   .len = 10};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line ordinary test return value");
  test(shared_obj.a == 1 && shared_obj.b == 1 && shared_obj.c == 1 &&
           shared_obj.d == 1,
       "Parse line ordinary test shared obj");
  test(strcmp((params.dat)[0], "melon") == 0 &&
           strcmp((params.dat)[1], "grape") == 0 &&
           strcmp((params.dat)[2], "lemon") == 0 && params.len == 3,
       "Parse line ordinary test params");

  free(params.dat);
}

void test_clparser_long_ops() {
  str_arr input = {
      .dat = (char *[]){"--aaaa", "--bar", "watermelon", "melon", "grape", "-c",
                        "-d", "juice", "coffee", "lemon"},
      .len = 10};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line long options test return value");
  test(shared_obj.a == 1 && shared_obj.b == 1 && shared_obj.c == 1 &&
           shared_obj.d == 1,
       "Parse line long options test shared obj");
  test(strcmp((params.dat)[0], "melon") == 0 &&
           strcmp((params.dat)[1], "grape") == 0 &&
           strcmp((params.dat)[2], "lemon") == 0 && params.len == 3,
       "Parse line long options test params");

  free(params.dat);
}

void test_clparser_dash_without_op() {
  str_arr input = {.dat = (char *[]){"-"}, .len = 1};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line dash without any op option test return value");
  test(strcmp((params.dat)[0], "-") == 0,
       "Parse line dash without any op option test params");
  free(params.dat);
}

void test_clparser_non_existent_op() {
  str_arr input = {.dat = (char *[]){"-a", "-r"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line non-existent option test return value");
  test(shared_obj.a == 1 && shared_obj.b == 0 && shared_obj.c == 0 &&
           shared_obj.d == 0,
       "Parse line non-existent option test shared obj");
}

void test_clparser_non_existent_long_op() {
  str_arr input = {.dat = (char *[]){"-c", "--aaa"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line non-existent long option test return value");
  test(shared_obj.a == 0 && shared_obj.b == 0 && shared_obj.c == 1 &&
           shared_obj.d == 0,
       "Parse line non-existent long option test shared obj");
}

void test_clparser_wrong_args() {
  str_arr input = {.dat = (char *[]){"-d", "lol"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line wrong option's argument count test return value");
  test(shared_obj.a == 0 && shared_obj.b == 0 && shared_obj.c == 0 &&
           shared_obj.d == 0,
       "Parse line wrong option's argument count test shared obj");
}

void test_clparser_wrong_op() {
  str_arr input = {.dat = (char *[]){"-a", "-push"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line wrong option test return value");
  test(shared_obj.a == 1 && shared_obj.b == 0 && shared_obj.c == 0 &&
           shared_obj.d == 0,
       "Parse line wrong option test shared obj");
}

void test_clparser_multi_ops_arity_last() {
  str_arr input = {.dat = (char *[]){"-aaccad", "juice", "coffee"}, .len = 3};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line multiple options (non-zero arity option is last) test "
       "return value");
  test(shared_obj.a == 1 && shared_obj.b == 0 && shared_obj.c == 1 &&
           shared_obj.d == 1,
       "Parse line multiple options (non-zero arity option is last) test "
       "shared obj");

  free(params.dat);
}

void test_clparser_multi_ops_arity_outside() {
  str_arr input = {.dat = (char *[]){"-b", "watermelon", "-ac"}, .len = 3};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line multiple options (non-zero arity option outside) test "
       "return value");
  test(shared_obj.a == 1 && shared_obj.b == 1 && shared_obj.c == 1 &&
           shared_obj.d == 0,
       "Parse line multiple options (non-zero arity option outside) test "
       "shared obj");

  free(params.dat);
}

void test_clparser_multi_ops_arity_inside() {
  str_arr input = {.dat = (char *[]){"-adc", "juice", "coffee"}, .len = 3};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line multiple options (non-zero arity option inside) test return "
       "value");
}

void test_clparser_inline_op_param() {
  str_arr input = {.dat = (char *[]){"-acbwatermelon", "juice"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line inline option parameter test "
       "return value");
  test(shared_obj.a == 1 && shared_obj.b == 1 && shared_obj.c == 1 &&
           shared_obj.d == 0 && params.dat && params.dat[0] &&
           strcmp(params.dat[0], "juice") == 0,
       "Parse line inline option parameter test "
       "shared obj");

  free(params.dat);
}

void test_clparser_inline_op_eq_param() {
  str_arr input = {.dat = (char *[]){"-acb=watermelon"}, .len = 1};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == 0,
       "Parse line inline option parameter test "
       "return value");
  test(shared_obj.a == 1 && shared_obj.b == 1 && shared_obj.c == 1 &&
           shared_obj.d == 0,
       "Parse line inline option parameter test "
       "shared obj");

  free(params.dat);
}

void test_clparser_wrong_inline_op_param() {
  str_arr input = {.dat = (char *[]){"-acdjuice", "coffee"}, .len = 2};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line wrong inline option parameter test "
       "return value");
}

void test_clparser_invalid_inline_op_param() {
  str_arr input = {.dat = (char *[]){"-acb="}, .len = 1};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line wrong inline option parameter test "
       "return value");
}

void test_clparser_invalid_eq() {
  str_arr input = {.dat = (char *[]){"-ac="}, .len = 1};

  test_struct shared_obj = {0, 0, 0, 0};

  str_arr params;

  test(parse_line(input, &shared_obj, available_options, &params) == -1,
       "Parse line wrong inline option parameter test "
       "return value");
}
