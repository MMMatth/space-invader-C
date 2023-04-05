/**
 * \file wall.h
 * \brief fichier d'entete du module wall
 * 
 */
#ifndef WALLS_H
#define WALLS_H

#include "world.h"
#include "sprite.h"
#include "const.h"

/**
 * \brief initialise les murs du jeu
 * 
 * \param world 
 * \param indice 
 * \param x : la position en x du mur
 * \param y : la position en y du mur
 * \param w : la largeur du mur
 * \param h : la hauteur du mur
 */
void init_wall(world_t * world, int indice, int x, int y, int w, int h);


/**
 * \brief fonction qui gere les collisions avec tout les murs
 * 
 * \param world : les données du monde ou se trouve le tableau de mur
 */
void handle_wall_collision(world_t *world);

/**
 * \brief fonction qui permet d'actualiser la position des murs
 * 
 * \param world : les données du monde ou se trouve le tableau de mur
 */
void update_wall(world_t *world);

/**
 * \brief fonction qui permet des liberer la memoir des murs
 * 
 * \param world : les données du monde ou se trouve le tableau de mur
 */
void clean_walls(world_t *world);


#endif /* WALLS_H */
