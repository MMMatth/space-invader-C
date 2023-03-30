#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"

void test_init_sprite_param( int x, int y, int w, int h){
    sprite_t * sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, x, y, w, h);
    print_sprite(sprite);
    free(sprite);
}

void test_init_sprite(){
    test_init_sprite_param( 0, 0, 10, 10);
    test_init_sprite_param( 50, 31, 12, 10);
    test_init_sprite_param( 0, 0, 0, 0);
}

void test_init_world(){
    world_t * world = malloc(sizeof(world_t));
    init_data(world);
    print_data(world);
    clean_data(world);
    free(world);
}


int main(){
    test_init_sprite();
    test_init_world();
    return 0;
}