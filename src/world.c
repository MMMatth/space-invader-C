#include "../include/world.h"
#include "../include/wall.h"

void init_projectile(world_t * world){
    for (int i = 0; i < MAX_PROJECTILE; i++){
        world->projectiles[i] = malloc(sizeof(projectile_t));
        world->projectiles[i]->sprite = malloc(sizeof(sprite_t));
        world->projectiles[i]->active = 0;
        world->projectiles[i]->x = 500;
        world->projectiles[i]->y = 500;
        init_sprite(world->projectiles[i]->sprite, world->projectiles[i]->x, world->projectiles[i]->y, PROJECTILE_SIZE/2, PROJECTILE_SIZE);
    }
}

void clean_projectile(world_t * world){
    for (int i = 0; i < MAX_PROJECTILE; i++){
        free(world->projectiles[i]->sprite);
        free(world->projectiles[i]);
    }
    free(world->projectiles);
}

void handle_projectile(world_t *world){
    for (int i = 0; i < MAX_PROJECTILE; i++){
        if (world->projectiles[i]->active){
            if (world->projectiles[i]->y < 0){
                world->projectiles[i]->active = 0;
            }
            for (int j = 0; j < world->meteors->nb_meteor; j++){
                if (world->meteors->tab_meteor[j] != NULL){
                    if (sprites_collide(world->projectiles[i]->sprite, world->meteors->tab_meteor[j])){
                        printf("x = %d y = %d\n", world->projectiles[i]->sprite->x, world->projectiles[i]->sprite->y);

                        world->meteors->tab_meteor[j] = NULL;
                        world->projectiles[i]->active = 0;
                        world->projectiles[i]->x = 500;
                        world->projectiles[i]->y = 500;
                    }
                }
            }
        }
    }
}


void init_data(world_t * world){
    world->joueur = malloc(sizeof(sprite_t));
    init_sprite(world->joueur, SCREEN_WIDTH / 2 - SHIP_SIZE / 2, SCREEN_HEIGHT - SHIP_SIZE - 15, SHIP_SIZE, SHIP_SIZE);
    world->ligne_arrivee = malloc(sizeof(sprite_t));
    init_sprite(world->ligne_arrivee, 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 1);
    world->meteors = malloc(sizeof(meteors_t));
    init_meteors(world, "map.txt");
    world->projectiles = malloc(sizeof(projectile_t*) * (MAX_PROJECTILE+1) );
    init_projectile(world);
    printf("init_data");
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


void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2){
    if(sprites_collide(sp1, sp2)){
        world->gameover = 1;
    }
}

void tirer(world_t *world){
    int i = 0;
    while(i < MAX_PROJECTILE && world->projectiles[i]->active){
        i++;
    }
    world->projectiles[i]->active = 1;
    world->projectiles[i]->x = world->joueur->x + SHIP_SIZE / 2 - PROJECTILE_SIZE / 4;
    world->projectiles[i]->y = world->joueur->y ;
    world->projectiles[i]->vitesse_y = 10;
    world->projectiles[i]->vitesse_x = 0;
}

void clean_data(world_t *world){
    free(world->joueur);
    free(world->ligne_arrivee);
    clean_meteors(world);
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    update_meteors(world);
    check_pos(world);
    handle_sprites_collision(world, world->joueur, world->ligne_arrivee);
    handle_meteors(world);
    handle_projectile(world);
    for (int i = 0; i < MAX_PROJECTILE; i++){
        if (world->projectiles[i]->active){
            world->projectiles[i]->y -= world->projectiles[i]->vitesse_y;
            world->projectiles[i]->x -= world->projectiles[i]->vitesse_x;
        }
    }
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