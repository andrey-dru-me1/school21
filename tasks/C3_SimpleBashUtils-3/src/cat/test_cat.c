#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../common/test/test.h"

#define TYPE char **
#define NAME str_list
#include "../common/arr/arr.h"
#undef NAME
#undef TYPE

static inline void redirect_output(char *filename) {
  int fd = creat(filename, S_IRWXU);
  dup2(fd, STDERR_FILENO);
  dup2(fd, STDOUT_FILENO);
  close(fd);
}

str_list_arr args_list = {
    .dat = (char **[]){(char *[]){"cat", "filename", NULL},
                       (char *[]){"cat", "test_cat.c", NULL},
                       (char *[]){"cat", "cat.c", "test_cat.c", NULL},
                       (char *[]){"cat", "many_spaces.txt", "nonprinting.txt",
                                  NULL}},
    .len = 4};

int test_flags(char *flags) {
  int error_count = 0;
  for (int i = 0; i < args_list.len; i++) {
    char *args[16] = {0};
    int iarg;
    for (iarg = 0; args_list.dat[i][iarg]; iarg++) {
      args[iarg] = args_list.dat[i][iarg];
    }
    args[iarg++] = flags;

    pid_t pid = fork();
    if (pid == 0) {
      redirect_output("cat.txt");
      execvp("cat", args);
    }
    pid = fork();
    if (pid == 0) {
      redirect_output("s21_cat.txt");
      execv("s21_cat", args);
    }
    wait(NULL);
    wait(NULL);
    pid = fork();
    if (pid == 0) {
      redirect_output("diff.txt");
      execlp("diff", "diff", "cat.txt", "s21_cat.txt");
      printf("error");
      return 0;
    }
    wait(NULL);
    FILE *diff = fopen("diff.txt", "rt");
    fseek(diff, 0, SEEK_END);
    if (ftell(diff)) error_count++;
    fclose(diff);
  }
  test(error_count == 0, flags);
  return error_count;
}

static int inner_dfs(const char *flags, char *op_str, int depth) {
  int error_count = test_flags(op_str);
  for (const char *flag = strchr(flags, op_str[depth - 1]) + 1; *flag; flag++) {
    op_str[depth] = *flag;
    error_count += inner_dfs(flags, op_str, depth + 1);
  }
  op_str[depth] = 0;
  return error_count;
}

static int dfs(const char *flags, char *op_str) {
  int error_count = test_flags(NULL);
  op_str[0] = '-';
  for (const char *flag = flags; *flag; flag++) {
    op_str[1] = *flag;
    error_count += inner_dfs(flags, op_str, 2);
  }
  return error_count;
}

int main(void) {
  FILE *nonprinting = fopen("nonprinting.txt", "wb");
  for (char i = 127; i != 32; i++) putc(i, nonprinting);
  fclose(nonprinting);

  FILE *many_spaces = fopen("many_spaces.txt", "wt");
  fprintf(many_spaces,
          "\n\n\tsomething\n\n\n\n\t\n\t\t\t\n\n\t\tstrange\n\n\n\n\n");
  fclose(many_spaces);

  const char flags[] = "benst";
  char op_str[16] = {0};
  int error_count = dfs(flags, op_str);
  printf("FAILS: %d\n", error_count);

  remove("cat.txt");
  remove("s21_cat.txt");
  remove("diff.txt");
  remove("nonprinting.txt");
  remove("many_spaces.txt");
  return 0;
}
