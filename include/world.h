#ifndef WORLD_H
#define WORLD_H

#include "const.h"
#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t* joueur; /*!< Sprite représentant le joueur */
    sprite_t* ligne_arrivee; /*!< Sprite représentant la ligne d'arrivée */
    sprite_t* mur_meteorite; /*!< Sprite représentant le mur de météorites */
    sprite_t** tab_wall_meteor; /*!< Tableau de sprite représentant les murs de météorites */
    float vitesse; /*!< Vitesse de déplacement du fond */
    int chrono; /*!< Chronomètre du jeu */
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


void init_walls(world_t *world);

/**
 * \brief fonction qui verifie si le joueur depasse les bords de l'écran et le deplace en conséquence
 * 
 * \param world 
 */
void check_pos(world_t *world);


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
 * \brief fonction qui permet de modifier le world en fonction de la collision entre deux sprites
 * 
 * \param world 
 * \param sp1 
 * \param sp2 
 */
void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);


// --- fonction tests --- //


/**
 * \brief affiche les informations du monde
 * 
 * \param world 
 */
void print_data(world_t* world);


#endif