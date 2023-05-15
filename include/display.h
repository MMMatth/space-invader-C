/**
 * \file display.h
 * \brief module qui permet de gérer l'affichage (SDL)
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H
#include "const.h"
#include "struct.h"
#include "world.h"
#include "sound.h"
#include "animate.h"
#include "chrono.h"
#include "meteors.h"
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

/**
 * \brief procedure qui permet d'initialiser les ressources du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
*/
void init_resources(SDL_Renderer *renderer, resources_t *ressources);

/**
 * \brief procedure qui permet gerer tout les evenements du jeu
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event,world_t * world, sounds_t * sounds, const Uint8 *keys);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, resources_t *textures);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_ressources(resources_t *textures);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param resources les ressources du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources);

/**
 * \brief la fonction permet de savoir si on clique dans une zone
 * 
 * \param event : l'evenement SDL
 * \param x_top_left : la position en x du coin haut gauche de la zone
 * \param x_bottom_left : la position en x du coin bas gauche de la zone
 * \param y_top_left : la position en y du coin haut gauche de la zone
 * \param y_bottom_left : la position en y du coin bas gauche de la zone
 * \return true : si on clique dans la zone
 * \return false : si on clique en dehors de la zone
 */
bool hitbox(SDL_Event event, int x_top_left, int x_bottom_left, int y_top_left, int y_bottom_left);





#endif