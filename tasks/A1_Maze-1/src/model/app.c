#include "model/app.h"

void app_new(app_t *app) {
  *app = (app_t){.infname = NULL,
                 .outfname = NULL,
                 .h = 0,
                 .w = 0,
                 .mt = MTMaze,
                 .generate = false};
}

void app_free(app_t *) {}