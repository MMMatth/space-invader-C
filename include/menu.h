/**
 * \file menu.h
 * \brief module qui permet de gerer le menu
 */
#ifndef MENU_H
#define MENU_H

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "const.h"
#include "world.h"
#include "display.h"
#include "sprite.h"
#include "meteors.h"
#include "const.h"
#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * \brief procedure qui permet de rafraichir les ressources du menu
 * 
 * \param renderer : le renderer SDL
 * \param world : les données du monde
 * \param resources : les ressources du jeu
 */
void menu_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief procedure qui permet de gerer les evenements du menu
 * 
 * \param event : l'evenement SDL
 * \param world : les données du monde
 * \param sounds : les sons du jeu
 * \param keys : les touches du clavier
 */
void menu_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds); 



#endif