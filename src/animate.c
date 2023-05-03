#include "../include/animate.h"

void init_animate(SDL_Renderer * renderer ,char * folder_path, int nb_frame, Uint32 frame_duration, animate_t * animate){
    animate->frames = malloc(sizeof(SDL_Texture*) * nb_frame);
    animate->nb_frames = nb_frame;
    animate->current_time = 0;
    animate->frame_duration = frame_duration;
    animate->last_frame_time = 0;
    animate->active = 0;
    animate->x = 0;
    animate->y = 0;
    char path[100];
    for(int i = 1; i <= nb_frame; i++){
        sprintf(path, "%s/%d.bmp", folder_path, i);
        animate->frames[i - 1] = load_image(path, renderer);
    }
}

void clean_animate(animate_t * animate){
    for(int i = 0; i < animate->nb_frames; i++){
        clean_texture(animate->frames[i]);
    }
    free(animate->frames);
}

void activate_animate(animate_t * animate, int x, int y){
    animate->active = 1;
    animate->current_time = 0;
    animate->x = x;
    animate->y = y;
}


void apply_animate(SDL_Renderer * renderer ,animate_t * animate, int x, int y){
    Uint32 current_time = SDL_GetTicks();
    if (animate->current_time == animate->nb_frames - 1)
        animate->active = 0;
    if(current_time - animate->last_frame_time > animate->frame_duration && animate->active){
        animate->current_time = (animate->current_time + 1) % animate->nb_frames;
        animate->last_frame_time = current_time;
    }
    if (animate->active)
        apply_texture(animate->frames[animate->current_time], renderer, x, y, METEORITE_SIZE, METEORITE_SIZE);
}

void update_animate(SDL_Renderer * renderer, world_t * world, animate_t * animate){
    animate->y += world->vitesse;
}