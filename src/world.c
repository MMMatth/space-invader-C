#include "../include/world.h"


void init_data(world_t * world){
    world->joueur = malloc(sizeof(sprite_t));
    init_sprite(world->joueur, SCREEN_WIDTH / 2 - SHIP_SIZE / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->ligne_arrivee = malloc(sizeof(sprite_t));
    init_sprite(world->ligne_arrivee, 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 1);
    world->mur_meteorite = malloc(sizeof(sprite_t));
    init_sprite(world->mur_meteorite, SCREEN_WIDTH / 3, 0, 3 * METEORITE_SIZE, 7 * METEORITE_SIZE);
    world->vitesse = INITIAL_SPEED;
    world->gameover = 0; // le jeu n'est pas fini
}

void check_pos(world_t *world){
    if(world->joueur->x < 0){
        world->joueur->x = 0;
    }
    if(world->joueur->x > SCREEN_WIDTH - SHIP_SIZE){
        world->joueur->x = SCREEN_WIDTH - SHIP_SIZE;
    }
    if(world->joueur->y < 0){
        world->joueur->y = 0;
    }
    if(world->joueur->y > SCREEN_HEIGHT - SHIP_SIZE){
        world->joueur->y = SCREEN_HEIGHT - SHIP_SIZE;
    }
}

void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2){
    if(sprites_collide(sp1, sp2)){
        world->vitesse = 0;
    }
}



void clean_data(world_t *world){
    free(world->joueur);
    free(world->ligne_arrivee);
    free(world->mur_meteorite);
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    world->mur_meteorite->y += world->vitesse;
    check_pos(world);
    handle_sprites_collision(world, world->joueur, world->mur_meteorite);
    handle_sprites_collision(world, world->joueur, world->ligne_arrivee);
}

int is_game_over(world_t *world){
    return world->gameover;
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