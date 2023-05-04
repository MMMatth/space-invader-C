/**
 * \file menu.h
 * \brief fichier d'en tete qui contient toute les fonctions qui concerne le menu
 */
#ifndef MENU_H
#define MENU_H

#include "const.h"
#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief La fonction crée une hibox pour le menu
 * \param event l'evenement
 * \param top_left le point en haut à gauche
 * \param top_right le point en haut à droite
 * \param bottom_left le point en bas à gauche
 * \param bottom_right le point en bas à droite
 */
bool hitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right);


/**
 * \brief La fonction initialise les données du menu
 * \param world les données du monde
 */
void menu(world_t* world);

/**
 * \brief passage du menu au jeu
 * \param world les données du monde
*/
void event_menu(world_t *world);



#endif