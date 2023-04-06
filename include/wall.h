/**
 * \file wall.h
 * \brief fichier d'entete du module wall
 * 
 */
#ifndef WALLS_H
#define WALLS_H

#include "world.h"
#include "sprite.h"
#include "const.h"



void init_meteors(world_t *world, char * map_file);

void init_meteor(world_t * world, int indice, int x, int y, int w, int h);

void update_meteors(world_t *world);

void clean_meteors(world_t *world);

void handle_meteors(world_t *world);


#endif /* WALLS_H */
