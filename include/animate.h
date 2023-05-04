/**
 * \file animate.h
 * \brief fichier d'en-tête du module animate
 */

#ifndef ANIMATE_H
#define ANIMATE_H

#include "const.h"
#include "struct.h"
#include "sdl2-light.h"

/**
 * \brief procedure qui permet d'initialiser plusieurs animations
 * 
 * \param folder_path : le dossier ou se trouve les images (1.bmp, 2.bmp, ...)
 * \param nb_frame : le nombre d'image dans le dossier
 * \param frame_duration : la durée d'une frame en ms
 * \param tab_animate : le tableau d'animation
 */
void init_animates(char * folder_path, int nb_frame, Uint32 frame_duration, animate_t ** tab_animate, int loop);

/**
 * \brief procedure qui permet d'initialiser une animation
 * 
 * \param folder_path ! le dossier ou se trouve les images (1.bmp, 2.bmp, ...)
 * \param nb_frame : le nombre d'image dans le dossier
 * \param frame_duration : la durée d'une frame en ms
 * \param animate : l'animation
 * \param loop : si l'animation doit boucler -1 sinon 0
 */
void init_animate(char * folder_path, int nb_frame, Uint32 frame_duration, animate_t * animate, int loop);

/**
 * \brief procedure qui permet d'afficher une animation
 * 
 * \param renderer : le renderer
 * \param animate : l'animation
 * \param tab_texture : le tableau de texture
 * \param x : la position x
 * \param y : la position y
 * \param w : la largeur
 * \param h : la hauteur
 */
void apply_animate(SDL_Renderer * renderer ,animate_t * animate, SDL_Texture ** tab_texture, int x, int y, int w, int h);

/**
 * \brief procedure qui permet de mettre a jour une animation libre dans un tableau d'animation
 * 
 * \param animate : le tableau d'animation
 * \param x : la position x
 * \param y : la position y
 */
void active_animates(animate_t ** animate, int x, int y);

/**
 * \brief procedure qui permet de mettre a jour une animation
 * 
 * \param animate : l'animation
 * \param x : la position x
 * \param y : la position y
 */
void active_animate(animate_t * animate, int x, int y);

/**
 * \brief procedure qui permet de mettre a jour plusieurs animations ( appliquer la vitesse)
 * 
 * \param world : le monde
 * \param animate : le tableau d'animation
 */
void update_animates(world_t * world, animate_t ** animate);

/**
 * \brief procedure qui permet de mettre a jour une animation ( appliquer la vitesse )
 * 
 * \param world : le monde
 * \param animate : l'animation
 */
void update_animate( world_t * world, animate_t * animate);

/**
 * \brief procedure qui permet de liberer la memoire de plusieurs animations
 * 
 * \param animate : le tableau d'animation
 */
void clean_animates(animate_t ** animate);

/**
 * \brief procedure qui permet de liberer la memoire d'une animation
 * 
 * \param animate : l'animation
 */
void clean_animate(animate_t * animate);

#endif