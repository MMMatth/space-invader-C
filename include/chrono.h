#ifndef CHRNO_H
#define CHRNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"

void save_chrono(world_t *world);

int * get_sort_score(world_t * world);

char * get_chrono_str(world_t *world);

int * tri_tableau(int * tab, int len);

void update_chrono(world_t *world, int time);


#endif