/**
 * \file projectile.h
 * \brief module qui s'occupe de la gestion des projectiles
 * 
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "const.h"
#include "struct.h"
#include "sprite.h"
#include "animate.h"
#include "display.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * \brief procedure qui permet d'initialiser les projectiles du monde
 * 
 * \param world 
 */
void init_projectiles(world_t *world);

/**
 * \brief procedure qui permet de tirer un projectile
 * 
 * \param world : le monde
 */
void tirer(world_t *world);

/**
 * \brief procedure qui gere la collision entre les projectiles et les meteors
 * 
 * \param world : le monde
 */
void colide_btw_projectile_and_meteor(world_t *world, int index_projectile, int index_meteor);

/**
 * \brief procedure qui permet de désactiver un projectile si il sort de l'écran
 * 
 * \param projectile 
 */
void est_dehors(projectile_t *projectile);

/**
 * \brief procedure qui gere les projectiles
 * 
 * \param world 
 */
void handle_projectile(world_t *world);


/**
 * \brief procedure qui met à jour les projectiles
 * 
 * \param world 
 */
void update_projectile(world_t *world);

/**
 * \brief procedure qui affiche les projectiles sur l'écran
 * 
 * \param renderer 
 * \param world 
 * \param resources 
 */
void apply_projectile(SDL_Renderer *renderer, world_t *world, resources_t *resources);

/**
 * \brief procedure qui permet de nettoyer les projectiles du monde en mémoire
 * 
 * \param world 
 */
void clean_projectile(world_t *world);


#endif /* PROJECTILE_H */