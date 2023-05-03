#ifndef ANIMATE_H
#define ANIMATE_H

#include "const.h"
#include "struct.h"
#include "sdl2-light.h"

void init_animate(SDL_Renderer * renderer ,char * folder_path, int nb_frame, Uint32 frame_duration, animate_t * animate);

void clean_animate(animate_t * animate);

void apply_animate(SDL_Renderer * renderer ,animate_t * animate, int x, int y);

void activate_animate(animate_t * animate, int x, int y);

void update_animate(SDL_Renderer * renderer, world_t * world, animate_t * animate);

#endif