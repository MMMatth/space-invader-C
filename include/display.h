/**
 * \file display.h
 * \brief fonctions qui utilise la SDL
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H
#include "const.h"
#include "world.h"
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct resources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du sprite. */
    SDL_Texture* ligne_arrivee; /*!< Texture liée à l'image de la ligne d'arrivée. */
    SDL_Texture* meteorite; /*!< Texture liée à l'image de la météorite. */
    TTF_Font *font; /*!< Font utilisée pour l'affichage du texte. */
};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct resources_s resources_t;

/**
 * \brief applique le sprite sur le renderer
 * 
 * \param renderer 
 * \param texture 
 * \param sprite 
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event,world_t * world);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void init_textures(SDL_Renderer *renderer, resources_t *textures);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(resources_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, resources_t *textures);

/**
 * \brief 
 * 
 * \param renderer 
 * \param textures 
 * \param x 
 * \param y 
 */
void apply_walls(SDL_Renderer *renderer, sprite_t ** tab_mur, SDL_Texture *texture);


#endif