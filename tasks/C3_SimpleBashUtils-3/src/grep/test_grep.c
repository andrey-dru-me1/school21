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
    .dat =
        (char **[]){
            (char *[]){"grep", "pattern", "filename", NULL},
            (char *[]){"grep", "grep", "test_grep.c", NULL},
            (char *[]){"grep", "\nprintf", "grep.c", NULL},
            (char *[]){"grep", "\nprintf", "grep.c", "test_grep.c", NULL},
            (char *[]){"grep", "", "grep.c", "test_grep.c", NULL},
            (char *[]){"grep", "^not found$", "grep.c", "test_grep.c", NULL},
            (char *[]){"grep", "-f", "patterns.txt", "-e", "flag", "grep.c",
                       "test_grep.c", NULL},
            (char *[]){"grep", "-e", "print\ngrep", "-e", "flag", "grep.c",
                       "test_grep.c", NULL},
            (char *[]){"grep", "^.", "grep.c", NULL},
            (char *[]){"grep", ".", "grep.c", NULL}},
    .len = 7};

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
      redirect_output("grep.txt");
      execvp("grep", args);
    }
    pid = fork();
    if (pid == 0) {
      redirect_output("s21_grep.txt");
      execv("s21_grep", args);
    }
    wait(NULL);
    wait(NULL);
    pid = fork();
    if (pid == 0) {
      redirect_output("diff.txt");
      execlp("diff", "diff", "grep.txt", "s21_grep.txt");
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
  FILE *patterns = fopen("patterns.txt", "wt");
  fprintf(patterns, "grep\nprintf\n\n");
  fclose(patterns);

  const char flags[] = "ivclnhso";
  char op_str[16] = {0};
  int error_count = dfs(flags, op_str);
  printf("FAILS: %d\n", error_count);

  remove("grep.txt");
  remove("s21_grep.txt");
  remove("diff.txt");
  remove("patterns.txt");
  return 0;
}
