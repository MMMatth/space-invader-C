#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"
#include "../include/sprite.h"
#include "../include/wall.h"

int test_init_sprite_param(int x, int y, int w, int h) {
    sprite_t* sprite = malloc(sizeof(sprite_t));
    if (sprite == NULL) {
        printf("Erreur d'allocation de memoire pour sprite\n");
        return 0;
    }
    init_sprite(sprite, x, y, w, h);
    print_sprite(sprite);
    free(sprite);
    return 1;   
}

int test_init_sprite() {
    test_init_sprite_param(0, 0, 10, 10);
    test_init_sprite_param(50, 31, 12, 10);
    test_init_sprite_param(0, 0, 0, 0);
    return 0;
}

int test_init_world() {
    world_t* world = malloc(sizeof(world_t));
    if (world == NULL) {
        printf("Erreur d'allocation de memoire pour world\n");
        return 0;
    }
    init_data(world);
    print_data(world);
    free(world);
    return 1;
}

int test_check_pos() {
    world_t* world = malloc(sizeof(world_t));
    init_data(world);
    world->joueur->x = -1000000;
    world->joueur->y = -1;
    int temp_x = world->joueur->x;
    int temp_y = world->joueur->y;
    printf("Position du joueur avant check_pos : %d %d \n", world->joueur->x, world->joueur->y);
    check_pos(world); // on actualise la position du joueur
    printf("Position du joueur apres check_pos : %d %d \n", world->joueur->x, world->joueur->y);
    if (world->joueur->x == temp_x || world->joueur->y == temp_y) {
        printf("Erreur dans check_pos : le joueur est encore en dehors de l'écran\n");
        return 0;
    }
    free(world);
    return 1;
}

int test_sprite_collide() {
    sprite_t* sprite1 = malloc(sizeof(sprite_t));
    sprite_t* sprite2 = malloc(sizeof(sprite_t));
    int collision = 0;
    init_sprite(sprite1, 0, 0, 10, 10);
    init_sprite(sprite2, 5, 5, 10, 10);
    printf("Est ce que le sprite 1 (0,0,10,10) touche le sprite 2 (5, 5, 10 , 10) : %d \n", sprites_collide(sprite1, sprite2)); 
    collision += 1;
    init_sprite(sprite2, 15, 15, 10, 10);
    printf("Est ce que le sprite 1 (0,0,10,10) touche le sprite 2 (15, 15, 10 , 10) : %d \n", sprites_collide(sprite1, sprite2)); 
    collision += 1;
    free(sprite1);
    free(sprite2);
    return collision;
}

int test_handle_sprite_collision(){
    sprite_t * sprite1 = malloc(sizeof(sprite_t));
    sprite_t * sprite2 = malloc(sizeof(sprite_t));
    world_t * world = malloc(sizeof(world_t));
    init_sprite(sprite1, 0, 0, 10, 10);
    init_sprite(sprite2, 5, 5, 10, 10);
    init_data(world);
    float vitesse_avant = world->vitesse;
    printf("Vitesse du monde avant collision : %f \n", world->vitesse);
    handle_sprites_collision(world, sprite1, sprite2);
    float vitesse_apres = world->vitesse;
    printf("Vitesse du monde apres collision : %f \n", world->vitesse);
    free(sprite1);
    free(sprite2);
    return (vitesse_avant != vitesse_apres);
}

int main(){
    int tests_reussis = 0;
    printf("Test de test_init_world");
    tests_reussis += test_init_world();
    printf("\nTest de check_pos\n");
    tests_reussis += test_check_pos();
    printf("\nTest de sprites_collide\n");
    tests_reussis += test_sprite_collide();
    printf("\nTest de handle_sprite_collision\n");
    tests_reussis += test_handle_sprite_collision();
    printf("\nNombre de test réussis : %d\n", tests_reussis);
    return 0;
}