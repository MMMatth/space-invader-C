#include "../include/animate.h"

void init_animates(char * folder_path, int nb_frame, Uint32 frame_duration, animate_t ** animate, int loop){
    for (int i = 0; i < MAX_ANIM; i++){
        animate[i] = malloc(sizeof(struct animate_s));
        init_animate(folder_path, nb_frame, frame_duration, animate[i], loop);
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

void active_animates(animate_t ** animate, int x, int y){
    for (int i = 0; i < MAX_ANIM; i++){
        if (animate[i]->active == 0){
            start_animate(animate[i], x, y);
            break;
        }
    }
}

void start_animate(animate_t * animate, int x, int y){
    animate->active = 1;
    animate->current_time = 0;
    animate->x = x;
    animate->y = y;
}

void pause_animate(animate_t * animate){
    animate->active = 0;
}


void apply_animate(SDL_Renderer * renderer ,animate_t * animate, SDL_Texture ** tab_texture, int x, int y, int w, int h){
    Uint32 current_time = SDL_GetTicks(); // on recupere le tick
    if (animate->current_time == animate->nb_frames - 1 && animate->loop != -1) {
        animate->active = 0; // si on est au dernier frame on desactive l'animation
    }

    if(current_time - animate->last_frame_time > animate->frame_duration && animate->active){
        animate->current_time = (animate->current_time + 1) % animate->nb_frames; // on passe au frame suivant
        animate->last_frame_time = current_time; // on met a jour le temps du dernier frame
    }
    if (animate->active) apply_texture( tab_texture[animate->current_time], renderer, x, y, w, h); // on applique le frame courant si l'animation est active
}

void update_animates(world_t * world, animate_t ** animate){
    for (int i = 0; i < MAX_ANIM; i++){
        if (animate[i]->active){
            update_animate(world, animate[i]);
        }
    }
}

void update_animate(world_t * world, animate_t * animate){
    animate->y += world->vitesse;
}

void clean_animates(animate_t ** animate){
    for (int i = 0; i < MAX_ANIM; i++){
        clean_animate(animate[i]);
    }
    free(animate);
}

void clean_animate(animate_t * animate){
    free(animate);
}