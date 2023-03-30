#include "../include/wall.h"


void init_wall(world_t * world, int indice, int x, int y, int w, int h){
    world->tab_wall_meteor[indice] = malloc(sizeof(sprite_t));
    init_sprite(world->tab_wall_meteor[indice], x, y, w, h);
}

void init_walls(world_t* world){
    init_wall(world, 0, 48, 0, 96, 192);
    init_wall(world, 1, 252, 0, 96, 192);
    init_wall(world, 2, 48, -320, 96, 192);
    init_wall(world, 3, 188, -352, 224, 160);
    init_wall(world, 4, 48, -672, 96, 192);
    init_wall(world, 5, 252, -672, 96, 192);
}

void handle_wall_collision(world_t *world){
    for (int i = 0; i < NB_MUR_METEORITE; i++){
        handle_sprites_collision(world, world->joueur, world->tab_wall_meteor[i]);
    }
}

void update_wall(world_t *world){
    for (int i = 0; i < NB_MUR_METEORITE; i++){
        world->tab_wall_meteor[i]->y += world->vitesse;
    }
}

void clean_walls(world_t *world){
    for (int i = 0; i < NB_MUR_METEORITE; i++){
        free(world->tab_wall_meteor[i]);
    }free(world->tab_wall_meteor);
}