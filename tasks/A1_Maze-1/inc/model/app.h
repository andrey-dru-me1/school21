#ifndef E199ECC8_E2B5_4B89_A96D_6DE4E1D1B68B
#define E199ECC8_E2B5_4B89_A96D_6DE4E1D1B68B

#include <stdbool.h>
#include <stddef.h>

typedef enum { MTMaze, MTCave } maze_type_t;

typedef struct {
  char *infname;
  char *outfname;
  size_t h, w;
  maze_type_t mt;
  bool generate;
} app_t;

void app_new(app_t *app);

void app_free(app_t *);

#endif /* E199ECC8_E2B5_4B89_A96D_6DE4E1D1B68B */
