/**
 * \file over.h
 * \brief module qui gere l'écran de fin du jeu
 */
#ifndef OVER_H
#define OVER_H

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "const.h"
#include "world.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief permet de rafraichir les graphiques de l'écran de fin du jeu
 * 
 * \param renderer : le rendu SDL
 * \param world : le monde
 * \param resources : les ressources
 */
void over_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief permet de gerer les evenements de l'écran de fin du jeu
 * 
 * \param event : l'evenement SDL
 * \param world : le monde
 * \param sounds : les sons
 * \param keys : les touches du clavier
 */
void over_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds);



#endif