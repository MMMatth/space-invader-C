#include "../include/sprite.h"

void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d \n", sprite->x, sprite->y, sprite->w, sprite->h);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture(texture, renderer, sprite->x, sprite->y);
}