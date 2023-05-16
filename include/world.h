/**
 * \file world.h
 * \brief module qui s'occupe de la gestion du monde
 */
#ifndef WORLD_H
#define WORLD_H

#include "const.h"
#include "struct.h"
#include "sprite.h"
#include "projectile.h"
#include "meteors.h"
#include "animate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t* world);

/**
 * \brief fonction qui verifie si le joueur depasse les bords de l'écran et le deplace en conséquence
 * 
 * \param world : les données du monde ou se trouve le joueur
 */
void check_pos(world_t *world);

/**
 * \brief fonction pour verifier si la collision entre deux sprites, change de phase si c'est le cas
 * 
 * \param world : les données du monde ou se trouve les sprites
 * \param sp1 : le premier sprite
 * \param sp2 : le deuxieme sprite
 */
void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t* world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t* world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t* world);

/**
 * \brief fonction qui permet d'activer l'animation de vitesse
 * 
 * \param world : les données du monde
 */
void speed_animate(world_t *world);

#endif