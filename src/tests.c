#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"

int nb_error = 0;

void error(char * message){
    printf("Erreur : %s\n", message);
    nb_error++;
}

void test_init_sprite_param( int x, int y, int w, int h){
    sprite_t * sprite = malloc(sizeof(sprite_t));
    if (sprite == NULL) error("sprite non alloue");
    init_sprite(sprite, x, y, w, h);
    if (sprite->x != x || sprite->y != y || sprite->w != w || sprite->h != h) error("init_sprite ne fonctionne pas");
    free(sprite);
}

void test_init_sprite(){
    test_init_sprite_param( 0, 0, 10, 10);
    test_init_sprite_param( 50, 31, 12, 10);
    test_init_sprite_param( 0, 0, 0, 0);
}

void test_init_world(){
    world_t * world = malloc(sizeof(world_t));
    if (world == NULL) error("world non alloue");
    init_data(world);
    if (world->joueur == NULL || world->ligne_arrivee == NULL ) error("world->joueur non alloue");
    clean_data(world);
    free(world);
}

void test_check_pos(){
    world_t * world = malloc(sizeof(world_t));
    if (world == NULL) error("world non alloue");
    init_data(world);
    world->joueur->x = -1000000;
    world->joueur->y = -1;
    check_pos(world); 
    if (world->joueur->x != 0 || world->joueur->y != 0) error("check_pos ne fonctionne pas");
    clean_data(world);
    free(world);
}

void test_sprite_collide(){
    sprite_t * sprite1 = malloc(sizeof(sprite_t));
    sprite_t * sprite2 = malloc(sizeof(sprite_t));
    init_sprite(sprite1, 0, 0, 10, 10);
    init_sprite(sprite2, 5, 5, 10, 10);
    if (!sprites_collide(sprite1, sprite2)) error("sprites_collide ne fonctionne pas");
    init_sprite(sprite2, 15, 15, 10, 10);
    if (sprites_collide(sprite1, sprite2)) error("sprites_collide ne fonctionne pas");
    free(sprite1);
    free(sprite2);
}

void test_handle_sprite_collision(){
    sprite_t * sprite1 = malloc(sizeof(sprite_t));
    sprite_t * sprite2 = malloc(sizeof(sprite_t));
    world_t * world = malloc(sizeof(world_t));
    init_sprite(sprite1, 0, 0, 10, 10);
    init_sprite(sprite2, 5, 5, 10, 10);
    init_data(world);
    handle_sprites_collision(world, sprite1, sprite2);
    if (world->gameover != 1) error("handle_sprites_collision ne fonctionne pas");
    free(sprite1);
    free(sprite2);
    clean_data(world);
}


int main(){
    test_init_sprite();
    test_init_world();
    test_check_pos();
    test_sprite_collide();
    test_handle_sprite_collision();
    printf("Il y'a %d erreur \n", nb_error);
    return 0;
}