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

void test_check_pos(){
    world_t * world = malloc(sizeof(world_t));
    init_data(world);
    world->joueur->x = -1000000;
    world->joueur->y = -1;
    printf("Position du joueur avant check_pos : %d %d \n", world->joueur->x, world->joueur->y);
    check_pos(world); // on actualise la position du joueur
    printf("Position du joueur apres check_pos : %d %d \n", world->joueur->x, world->joueur->y);
    clean_data(world);
    free(world);
}

void test_sprite_collide(){
    sprite_t * sprite1 = malloc(sizeof(sprite_t));
    sprite_t * sprite2 = malloc(sizeof(sprite_t));
    init_sprite(sprite1, 0, 0, 10, 10);
    init_sprite(sprite2, 5, 5, 10, 10);
    printf("Est ce que le sprite 1 (0,0,10,10) touche le sprite 2 (5, 5, 10 , 10) : %d \n", sprites_collide(sprite1, sprite2));
    init_sprite(sprite2, 15, 15, 10, 10);
    printf("Est ce que le sprite 1 (0,0,10,10) touche le sprite 2 (15, 15, 10 , 10) : %d \n", sprites_collide(sprite1, sprite2));
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
    printf("Vitesse du monde avant collision : %f \n", world->vitesse);
    handle_sprites_collision(world, sprite1, sprite2);
    printf("Vitesse du monde apres collision : %f \n", world->vitesse);
    free(sprite1);
    free(sprite2);
    clean_data(world);
}


int main(){
    printf("Test de init_sprite\n");
    test_init_sprite();
    printf("\nTest de init_world de base\n");
    test_init_world();
    printf("\nTest de check_pos\n");
    test_check_pos();
    printf("\nTest de sprite_collide\n");
    test_sprite_collide();
    printf("\nTest de handle_sprite_collision\n");
    test_handle_sprite_collision();
    return 0;
}