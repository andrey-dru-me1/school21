#include "test.h"

#include <stdio.h>

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define DFT "\e[0m"

bool test(bool cond, const char *test_name) {
  printf("%s: ", test_name);
  if (cond) {
    printf(GRN "SUCCESS" DFT "\n");
  } else {
    printf(RED "FAIL" DFT "\n");
  }
  return cond;
}
