/**
 * \file menu.h
 * \brief fichier d'en tete qui contient toute les fonctions qui concerne le menu
 */
#ifndef OVER_H
#define OVER_H

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
 * \brief La fonction crée une hibox pour le menu
 * \param event l'evenement
 * \param top_left le point en haut à gauche
 * \param top_right le point en haut à droite
 * \param bottom_left le point en bas à gauche
 * \param bottom_right le point en bas à droite
 */
bool hitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);


void over_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources);


void over_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds, const Uint8 *keys);



#endif