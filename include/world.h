#ifndef WORLD_H
#define WORLD_H

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
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t* joueur; /*!< Sprite représentant le joueur */
    sprite_t* ligne_arrivee; /*!< Sprite représentant la ligne d'arrivée */
    sprite_t* mur_meteorite; /*!< Sprite représentant le mur de météorites */
    float vitesse; /*!< Vitesse de déplacement du fond */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t* world);

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

// --- fonction tests --- //

/**
 * \brief affiche les informations du sprite
 * 
 * \param sprite 
 */
void print_sprite(sprite_t *sprite);

/**
 * \brief affiche les informations du monde
 * 
 * \param world 
 */
void print_data(world_t* world);


#endif