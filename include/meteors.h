/**
 * \file wall.h
 * \brief module qui permet de gerer les météorites
 * 
 */
#ifndef WALLS_H
#define WALLS_H

#include "world.h"
#include "sprite.h"
#include "const.h"
#include "struct.h"
#include "sdl2-light.h"


/**
 * \brief procedure permettant d'initialliser les meteors
 * 
 * \param world : le monde
 * \param map_file : lien de la carte
 */
void init_meteors(world_t *world, char * map_file);

/**
 * \brief procedure qui pertmet d'initialliser un meteor
 * 
 * \param world : le monde
 * \param indice : l'indice du meteor
 * \param x : position x du meteor
 * \param y : position y du meteor
 * \param w : largeur du meteor
 * \param h : hauteur du meteor
 */
void init_meteor(world_t * world, int indice, int x, int y, int w, int h);

/**
 * \brief fonction qui permet de calculer le nombre de meteorites 
 * il conte le nombre de 1 dans le fichier de la map
 * \param mapfile : le fichier de la map
 * \return int le nombre de meteorites
 */
int calc_meteor(char * mapfile);

/**
 * \brief procedure qui permet mettre a jour les meteorites pour prendre en compte la vitesse du jeu
 * 
 * \param world : les données du monde
 */
void update_meteors(world_t *world);

/**
 * \brief procedure qui permet de nettoyer en memoire les meteorites
 * 
 * \param world : les données du monde
 */
void clean_meteors(world_t *world);

/**
 * \brief procedure qui permet de voir si le joueur a perdu
 * 
 * \param world : les données du monde
 */
void est_perdu(world_t *world);

/**
 * \brief permet d'afficher les meteores sur l'écran de jeu
 * 
 * \param renderer 
 * \param world 
 * \param texture 
 */
void apply_meteors(SDL_Renderer *renderer, world_t * world, SDL_Texture *texture);


#endif /* WALLS_H */
