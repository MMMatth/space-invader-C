#include "../include/world.h"
#include "../include/wall.h"


void init_data(world_t * world){
    world->joueur = malloc(sizeof(sprite_t));
    init_sprite(world->joueur, SCREEN_WIDTH / 2 - SHIP_SIZE / 2, SCREEN_HEIGHT - SHIP_SIZE - 15, SHIP_SIZE, SHIP_SIZE);
    world->ligne_arrivee = malloc(sizeof(sprite_t));
    init_sprite(world->ligne_arrivee, 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 1);
    world->tab_wall_meteor = malloc(sizeof(sprite_t*) * NB_MUR_METEORITE);
    init_walls(world);
    world->vitesse = INITIAL_SPEED;
    world->chrono = 0;
    world->gameover = 0; // le jeu n'est pas fini
}

void check_pos(world_t *world){ // vérifie que le joueur ne sort pas de l'écran
    if(world->joueur->x < 0){ // si le joueur sort de l'écran à gauche
        world->joueur->x = 0; // on le replace à gauche
    }
    if(world->joueur->x > SCREEN_WIDTH - SHIP_SIZE){ // si le joueur sort de l'écran à droite
        world->joueur->x = SCREEN_WIDTH - SHIP_SIZE; // on le replace à droite
    }
    if(world->joueur->y < 0){ // si le joueur sort de l'écran en haut
        world->joueur->y = 0; // on le replace en haut
    }
    if(world->joueur->y > SCREEN_HEIGHT - SHIP_SIZE){ // si le joueur sort de l'écran en bas
        world->joueur->y = SCREEN_HEIGHT - SHIP_SIZE; // on le replace en bas
    }
}

void est_fini(world_t *world){
    if(sprites_collide(world->joueur, world->ligne_arrivee)){ // si le joueur a atteint la ligne d'arrivée
        printf("Vous avez gagne en %ds!\n", world->chrono);
    }else{
        printf("Vous avez perdu !\n");
    }
}

void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2){
    if(sprites_collide(sp1, sp2)){
        world->gameover = 1;
        // est_fini(world);
    }
}

void clean_data(world_t *world){
    free(world->joueur);
    free(world->ligne_arrivee);
    clean_walls(world);
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    update_wall(world);
    check_pos(world);
    handle_sprites_collision(world, world->joueur, world->ligne_arrivee);
    handle_wall_collision(world);
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
    printf("Vitesse du fond : %f ", world->vitesse);
    printf("Le jeu est fini ? %s \t", world->gameover ? "oui" : "non");
}