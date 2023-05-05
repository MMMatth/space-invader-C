#ifndef STRUCT_H
#define STRUCT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief structure qui représente un sprite
 */
struct sprite_s{
    int x; /*!< Position en x du sprite */
    int y; /*!< Position en y du sprite */
    int w; /*!< Largeur du sprite */
    int h; /*!< Hauteur du sprite */
};
typedef struct sprite_s sprite_t;

/**
 * \brief structure qui représente un projectile
 */
struct  projectile_s{
    float x; /*!< Position en x du projectile */
    float y; /*!< Position en y du projectile */
    float vitesse_x; /*!< Vitesse en x du projectile */
    float vitesse_y; /*!< Vitesse en y du projectile */
    float variation;
    int frequence;
    bool active; /*!< Champ indiquant si le projectile est actif */
    sprite_t * sprite; /*!< Sprite du projectile */
};
typedef struct projectile_s projectile_t;

/**
 * \brief structure qui représente le mur de météorites
 */
struct meteors_s{
    sprite_t ** tab_meteor; /*!< Tableau de sprite représentant les météorites */
    int nb_meteor; /*!< Nombre de météorites */
}; 
typedef struct meteors_s meteors_t;

struct animate_s{
    int nb_frames;
    int current_time;
    Uint32 frame_duration;
    Uint32 last_frame_time;
    int loop;
    int active;
    int x; int y;
};typedef struct animate_s animate_t;



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct resources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du sprite. */
    SDL_Texture* ligne_arrivee; /*!< Texture liée à l'image de la ligne d'arrivée. */
    SDL_Texture* meteorite; /*!< Texture liée à l'image de la météorite. */
    SDL_Texture* laser; /*!< Texture liée à l'image du laser. */
    SDL_Texture* menu; /*!< Texture liée à l'image du menu. */
    SDL_Texture ** explode_img; /*!< Tableau des textures des explosions*/
    SDL_Texture ** speed_img;
    TTF_Font *font; /*!< Font utilisée pour l'affichage du texte. */
};
typedef struct resources_s resources_t;

/**
 * \brief 
 * 
 */
struct sounds_s{
    Mix_Music *music; /*!< Musique du jeu */
    Mix_Chunk *laser; /*!< Son du laser */
    Mix_Chunk *explosion; /*!< Son de l'explosion */
    Mix_Chunk *clic; /*!< Son de clic */
};typedef struct sounds_s sounds_t;




/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t* joueur; /*!< Sprite représentant le joueur */
    sprite_t* ligne_arrivee; /*!< Sprite représentant la ligne d'arrivée */
    sprite_t* mur_meteorite; /*!< Sprite représentant le mur de météorites */
    sprite_t** tab_wall_meteor; /*!< Tableau de sprite représentant les murs de météorites */
    meteors_t * meteors;
    animate_t ** explode_animate; /*!< Texture liée à l'image de l'explosion. */
    animate_t * speed_animate;
    projectile_t ** projectiles;

    int phase; /*!< Champ indiquant la phase du jeu */

    float vitesse; /*!< Vitesse de déplacement du fond */
    int chrono; /*!< Chronomètre du jeu */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};
typedef struct world_s world_t;

#endif