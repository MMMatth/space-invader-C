/**
 * \file sound.h
 * \brief fichier d'en tete des fonctions qui gère les sons
 */

#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "struct.h"

/**
 * \brief La fonction initialise le système de son
 * 
 */
void init_sounds_systeme();

/**
 * \brief La fonction initialise les sons
 * 
 * \param sounds : structure qui contient les sons
 */
void init_sounds(sounds_t * sounds);

/**
 * \brief La fonction nettoie les sons
 * 
 */
void clean_sound();

/**
 * \brief fonction pour jouer un son
 * 
 * \param sound : le son (Mix_Chunk)
 * \param channel : le canal sur lequel on joue le son (-1 pour le premier canal disponible)
 * \param loop : le nombre de fois que l'on joue le son (-1 pour une boucle infinie)
 */
void play_sound(Mix_Chunk *sound, int channel, int loop);

/**
 * \brief fonction pour jouer une musique
 * 
 * \param music : la musique (Mix_Music)
 * \param loop : le nombre de fois que l'on joue la musique (-1 pour une boucle infinie)
 */
void play_music(Mix_Music *music, int loop);

/**
 * \brief fonction pour mettre en pause la musique
 * 
 */
void pause_music();

/**
 * \brief fonction pour reprendre la musique
 * 
 */
void resume_music();

/**
 * \brief fonction pour arrêter la musique
 * 
 */
void stop_music();

/**
 * \brief fonction pour arrêter un son
 * 
 * \param channel : le canal sur lequel on arrête le son (-1 pour tous les canaux)
 */
void stop_channel(int channel);

/**
 * \brief fonction pour régler le volume d'un canal 
 * 
 * \param channel : le canal sur lequel on règle le volume (-1 pour tous les canaux)
 * \param volume : le volume (entre 0 et 128)
 */
void set_volume(int channel, int volume);

/**
 * \brief fonction pour faire un fondu sur la musique
 * 
 * \param ms : le temps en millisecondes
 */
void fade_out_music(int ms);

#endif
