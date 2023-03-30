#ifndef SPRITE_H
#define SPRITE_H

#include "const.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief structure qui représente un sprite
 */
struct sprite_s{
    int x; /*!< Position en x du sprite */
    int y; /*!< Position en y du sprite */
    int w; /*!< Largeur du sprite */
    int h; /*!< Hauteur du sprite */
};
/**
 * \brief Type qui correspond à un sprite
 */
typedef struct sprite_s sprite_t;

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

// --- Fonctions test --- //

/**
 * \brief affiche les informations du sprite
 * 
 * \param sprite 
 */
void print_sprite(sprite_t *sprite);


#endif