#ifndef CA68955A_5B3D_4596_AB56_0AC5150FF4FD
#define CA68955A_5B3D_4596_AB56_0AC5150FF4FD

#include <stddef.h>

typedef enum { MazeWall, MazePass } maze_wall_t;

typedef struct {
  maze_wall_t down, right;
} maze_cell_t;

typedef struct {
  maze_cell_t *grid;
  size_t h, w;
} maze_t;

void maze_new(maze_t *m, size_t h, size_t w);
maze_cell_t *maze_cell_get(maze_t *m, size_t row, size_t col);
void maze_free(maze_t *m);

#endif /* CA68955A_5B3D_4596_AB56_0AC5150FF4FD */
