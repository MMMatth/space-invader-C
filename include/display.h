/**
 * \file display.h
 * \brief fonctions qui utilise la SDL
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H
#include "const.h"
#include "struct.h"
#include "world.h"
#include "wall.h"
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param resources les ressources du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event,world_t * world);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void init_textures(SDL_Renderer *renderer, resources_t *textures);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(resources_t *textures);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, resources_t *textures);

#endif