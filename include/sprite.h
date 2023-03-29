#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "sdl2-light.h"
#include "const.h"


/**
 * \brief structure qui représente un sprite
 */
struct sprite_s{
    int x; /*!< Position en x du sprite */
    int y; /*!< Position en y du sprite */
    int w; /*!< Largeur du sprite */
    int h; /*!< Hauteur du sprite */
};

typedef struct sprite_s sprite_t;

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
 * \brief affiche les informations du sprite
 * 
 * \param sprite 
 */
void print_sprite(sprite_t *sprite);

/**
 * \brief applique le sprite sur le renderer
 * 
 * \param renderer 
 * \param texture 
 * \param sprite 
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

#endif