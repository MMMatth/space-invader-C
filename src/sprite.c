#include "../include/sprite.h"

void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x = x; // on initialise les valeurs du sprite
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}

void hide_sprite(sprite_t *sprite){
    sprite->w = 0; // on cache le sprite
    sprite->h = 0;
}

int sprites_collide(sprite_t * sp1, sprite_t * sp2){
    return (sp1->x < sp2->x + sp2->w && // si les sprites se chevauchent
            sp1->x + sp1->w > sp2->x &&
            sp1->y < sp2->y + sp2->h &&
            sp1->y + sp1->h > sp2->y);
}

void apply_sprite_adapted(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture_adapted(texture, renderer, sprite->x, sprite->y); // on applique la texture
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture(texture, renderer, sprite->x, sprite->y, sprite->w, sprite->h); // on applique la texture
}