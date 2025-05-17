#include "cmd/cli_processor.h"

#include <stdio.h>
#include <string.h>

#include "cli/parser.h"
#include "model/app.h"

static void open_file(char *fname, void *vars[]) {
  app_t *app = vars[0];
  app->infname = fname;
}

static void choose_maze(char *, void *vars[]) {
  app_t *app = vars[0];
  app->mt = MTMaze;
}
static void choose_cave(char *, void *vars[]) {
  app_t *app = vars[0];
  app->mt = MTCave;
}

static void generate(char *bounds, void *vars[]) {
  app_t *app = vars[0];
  app->generate = true;

  bounds = strtok(bounds, ",");
  sscanf(bounds, "%lu", &app->h);

  bounds = strtok(NULL, ",");
  sscanf(bounds, "%lu", &app->w);
}

static void set_output(char *fname, void *vars[]) {
  app_t *app = vars[0];
  app->outfname = fname;
}

int cli_processor_process(int argc, char *argv[], app_t *app) {
  cli_parser_t cp;
  cli_parser_new(&cp,
                 (option_t[]){{.label = 'f',
                               .llabel = "file",
                               .has_arg = true,
                               .process = open_file},
                              {.llabel = "maze", .process = choose_maze},
                              {.llabel = "cave", .process = choose_cave},
                              {.label = 'g',
                               .llabel = "generate",
                               .has_arg = true,
                               .process = generate},
                              {.label = 'o',
                               .llabel = "output",
                               .has_arg = true,
                               .process = set_output}},
                 5);

  int res = cli_parser_parse(&cp, argc, argv, (void *[]){app});
  cli_parser_free(&cp);
  return res;
}