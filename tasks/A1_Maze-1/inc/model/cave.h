#ifndef E34E9972_B6DD_4275_9EC0_7067C0C58332
#define E34E9972_B6DD_4275_9EC0_7067C0C58332

#include <stddef.h>

typedef enum { CaveBlock, CavePass } cave_cell_t;

typedef struct {
  cave_cell_t *grid;
  size_t h, w;
} cave_t;

void cave_new(cave_t *c, size_t h, size_t w);
cave_cell_t *cave_cell_get(cave_t *c, size_t row, size_t col);
void cave_free(cave_t *c);

#endif /* E34E9972_B6DD_4275_9EC0_7067C0C58332 */
