/**
 * \file chrono.h
 * \brief module qui gere le chrono
 */

#ifndef CHRNO_H
#define CHRNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "world.h"

/**
 * \brief sauvegarder le chrono dans un fichier
 * 
 * \param world : le monde
 */
void save_chrono(world_t *world);

/**
 * \brief permet de recuperer les trois meilleurs scores
 * 
 * \param world : le monde
 * \return int* : tableau de 3 entiers
 */
int * get_sort_score(world_t * world);

/**
 * \brief permet de recuperer le chrono sous la forme 00 : 00
 * 
 * \param world 
 * \return char * : le chrono sous la forme 00 : 00
 */
char * get_chrono_str(world_t *world);

/**
 * \brief permet de trier un tableau d'entiers dans l'ordre croissant
 * 
 * \param tab : le tableau d'entiers
 * \param len : la taille du tableau
 * \return int* : le tableau trié
 */
int * tri_tableau(int * tab, int len);

/**
 * \brief permet de mettre a jour le chrono
 * 
 * \param world : le monde
 * \param time : le temps
 */
void update_chrono(world_t *world, int time);


/**
 * \brief permet d'afficher le chrono
 * 
 * \param renderer : le renderer SDL
 * \param world : les données du monde
 * \param resources : les ressources
 */
void apply_chrono(SDL_Renderer *renderer, world_t *world, resources_t *resources);

#endif