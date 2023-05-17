#include "../include/animate.h"

void init_animates(char * folder_path, int nb_frame, Uint32 frame_duration, animate_t ** animate, int loop){
    for (int i = 0; i < MAX_ANIM; i++){ // on parcours le tableau d'animation
        animate[i] = malloc(sizeof(struct animate_s)); // on alloue la memoire pour l'animation
        init_animate(folder_path, nb_frame, frame_duration, animate[i], loop); // on initialise l'animation
    }
}

void init_animate(char * folder_path, int nb_frame, Uint32 frame_duration, animate_t * animate, int loop){
    animate->nb_frames = nb_frame; 
    animate->current_time = 0;
    animate->frame_duration = frame_duration;
    animate->last_frame_time = 0;
    animate->loop = loop;
    animate->active = 0;
    animate->x = 0;
    animate->y = 0;
}

void apply_animate(SDL_Renderer * renderer ,animate_t * animate, SDL_Texture ** tab_texture, int x, int y, int w, int h){
    Uint32 current_time = SDL_GetTicks(); // on recupere le tick
    if (animate->current_time == animate->nb_frames - 1 && animate->loop != -1) { // on verifie que l'on est au dernier frame et que l'animation ne soit pas en boucle infinie
        animate->active = 0; // on desactive l'animation
    }

    if(current_time - animate->last_frame_time > animate->frame_duration && animate->active){ // on verifie que le temps entre le dernier frame et le frame courant soit superieur au temps de frame et que l'animation soit active
        animate->current_time = (animate->current_time + 1) % animate->nb_frames; // on passe au frame suivant
        animate->last_frame_time = current_time; // on met a jour le temps du dernier frame
    }
    if (animate->active) apply_texture( tab_texture[animate->current_time], renderer, x, y, w, h); // on applique le frame courant si l'animation est active
}

void start_animates(animate_t ** animate, int x, int y){
    for (int i = 0; i < MAX_ANIM; i++){ // on parcours le tableau d'animation
        if (animate[i]->active == 0){ // on verifie que l'aniation soit active
            start_animate(animate[i], x, y); // on demarre l'animation
            break; // on sort de la boucle
        }
    }
}

void start_animate(animate_t * animate, int x, int y){
    animate->active = 1; // on active l'animation
    animate->current_time = 0; // on met le frame courant a 0
    animate->x = x; // on met a jour la position
    animate->y = y; // on met a jour la position
}

void pause_animate(animate_t * animate){
    animate->active = 0; // on desactive l'animation
}

void update_animates(world_t * world, animate_t ** animate){
    for (int i = 0; i < MAX_ANIM; i++){ // on parcours le tableau d'animation
        if (animate[i]->active){ // on verifie que l'animation soit active
            update_animate(world, animate[i]); // on met a jour l'animation
        }
    }
}

void update_animate(world_t * world, animate_t * animate){
    animate->y += world->vitesse; // on met a jour la position
}

void clean_animates(animate_t ** animate){
    for (int i = 0; i < MAX_ANIM; i++){ // on parcours le tableau d'animation
        clean_animate(animate[i]); // on libere la memoire de l'animation
    }
    free(animate); // on libere la memoire du tableau d'animation
}

void clean_animate(animate_t * animate){
    free(animate); // on libere la memoire de l'animation
}