#include "../include/world.h"


void init_data(world_t * world){
    world->joueur = malloc(sizeof(sprite_t));
    init_sprite(world->joueur, SCREEN_WIDTH / 2 - SHIP_SIZE / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->ligne_arrivee = malloc(sizeof(sprite_t));
    init_sprite(world->ligne_arrivee, 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 1);
    world->mur_meteorite = malloc(sizeof(sprite_t));
    init_sprite(world->mur_meteorite, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    world->vitesse = INITIAL_SPEED;
    world->gameover = 0; // le jeu n'est pas fini
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}


void clean_data(world_t *world){
    free(world->joueur);
    free(world->ligne_arrivee);
    free(world->mur_meteorite);
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    world->mur_meteorite->y += world->vitesse;
}

int is_game_over(world_t *world){
    return world->gameover;
}

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d \n", sprite->x, sprite->y, sprite->w, sprite->h);
}

void print_data(world_t* world){
    printf("Position et taille du joueur : ");
    print_sprite(world->joueur);
    printf("Position et taille de la ligne d'arrivee : ");
    print_sprite(world->ligne_arrivee);
    printf("Position et taille du mur de meteorites : ");
    print_sprite(world->mur_meteorite);
    printf("Vistesse du fond : %f ", world->vitesse);
    printf("Le jeu est fini ? %s \t", world->gameover ? "oui" : "non");
}