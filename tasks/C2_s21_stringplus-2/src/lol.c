#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *p = strerror(-15);
  char *p1 = strerror(-16);
  printf("%s\n%s", p, p1);
  return 0;
}
