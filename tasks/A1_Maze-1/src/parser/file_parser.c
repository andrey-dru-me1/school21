#include "parser/file_parser.h"

#include <stdio.h>
#include <string.h>

void file_parser_parse(char *fname, void (*func)(char *token, void *args[]),
                       void *args[]) {
  FILE *f = fopen(fname, "r");
  char buf[256];
  size_t start_point = 0;
  while (!feof(f)) {
    size_t bytes_read =
        fread(buf + start_point, sizeof(*buf),
              (sizeof(buf) - start_point - 1) / sizeof(*buf), f);
    buf[sizeof(buf) - 1] = 0;
    char *saveptr = NULL;
    char *token = strtok_r(buf, " \n", &saveptr);
    size_t tokenlen = strlen(token);
    char *bufendptr = buf + start_point + bytes_read;
    while (token && token + tokenlen < bufendptr) {
      func(token, args);
      token = strtok_r(NULL, " \n", &saveptr);
      if (token) tokenlen = strlen(token);
    }
    if (token) {
      memmove(buf, token, tokenlen);
      start_point = tokenlen;
    } else {
      start_point = 0;
    }
  }
  fclose(f);
}
