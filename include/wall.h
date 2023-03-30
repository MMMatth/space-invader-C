#ifndef WALLS_H
#define WALLS_H

#include "world.h"
#include "sprite.h"
#include "const.h"

void init_wall(world_t * world, int indice, int x, int y, int w, int h);


void init_walls(world_t* world);


void handle_wall_collision(world_t *world);


void update_wall(world_t *world);


void clean_walls(world_t *world);


#endif /* WALLS_H */
