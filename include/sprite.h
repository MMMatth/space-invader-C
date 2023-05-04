/**
 * \file sprite.h
 * \brief fichier d'en tete des fonctions qui gère les sprites
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include "sdl2-light.h"
#include "struct.h"


/**
 * \brief fonction qui verifie si deux sprites se chevauchent
 * 
 * \param sp1 : le premier sprite
 * \param sp2 : le deuxieme sprite
 * \return int 
 */
int sprites_collide(sprite_t * sp1, sprite_t * sp2);


/**
 * \brief initialise un sprite
 * 
 * \param sprite : le sprite à initialiser
 * \param x : la position en x du sprite
 * \param y : la position en y du sprite
 * \param w : la largeur du sprite
 * \param h : la hauteur du sprite
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h);

/**
 * \brief cache le sprite
 * 
 * \param sprite 
 */
void hide_sprite(sprite_t *sprite);

/**
 * \brief applique le sprite sur le renderer en l'adaptant à la taille de l'image
 * 
 * \param renderer : le renderer
 * \param texture : la texture
 * \param sprite : le sprite
 */
void apply_sprite_adapted(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * \brief applique le sprite sur le renderer
 * 
 * \param renderer : le renderer
 * \param texture : la texture
 * \param sprite : le sprite
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

// --- Fonctions test --- //

/**
 * \brief affiche les informations du sprite
 * 
 * \param sprite 
 */
void print_sprite(sprite_t *sprite);


#endif