#include "../include/world.h"


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
        // on initialise les animations des explosions

    world->explode_animate = malloc(sizeof(animate_t*) * MAX_ANIM);
    init_animates("assets/img/explode_animate", 6, 50, world->explode_animate, 0);

    world->speed_animate = malloc(sizeof(animate_t*) * MAX_ANIM);
    init_animate("assets/img/speed_animate", 9, 100, world->speed_animate, -1);

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

char * get_chrono_str(world_t *world){
    char *chrono = malloc(sizeof(char) * 10);
    if (world->chrono >= 60){        
        if (world->chrono % 60 >= 10)
            sprintf(chrono, "0%d : %d", world->chrono / 60, world->chrono % 60);
        else
            sprintf(chrono, "0%d : 0%d", world->chrono / 60, world->chrono % 60);
    }else if (world->chrono >= 10){
        sprintf(chrono, "00 : %d", world->chrono);
    }else if (world->chrono < 10){
        sprintf(chrono, "00 : 0%d", world->chrono);
    }
    return chrono;
}

void save_chrono(world_t *world){
    FILE *fichier = NULL;
    fichier = fopen("score.txt", "a");
    if(fichier != NULL){
        fprintf(fichier, "%s\n", get_chrono_str(world));
        fclose(fichier);
    }
    else{
        printf("Erreur lors de l'ouverture du fichier");
    }
}

void update_chrono(world_t *world, int time){
    world->chrono = time / 1000;
}


void handle_sprites_collision(world_t *world, sprite_t *sp1, sprite_t *sp2){
    if(sprites_collide(sp1, sp2)){
        world->gameover = 1;
    }
}

void clean_data(world_t *world){
    free(world->joueur);
    free(world->ligne_arrivee);
    clean_projectile(world);
    clean_meteors(world);
    clean_animates(world->explode_animate);
    clean_animate(world->speed_animate);
}

int speed_animate = 0;

void activate_speed_animate(world_t *world){
    if (world->vitesse > 3){
        if (speed_animate == 0){
            start_animate(world->speed_animate, 0, 0);
            speed_animate = 1;
        }
    }else{
        pause_animate(world->speed_animate);
        speed_animate = 0;
    }
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    update_meteors(world);
    update_projectile(world);
    check_pos(world);
    handle_sprites_collision(world, world->joueur, world->ligne_arrivee);
    est_perdu(world);
    handle_projectile(world);
    update_animates(world, world->explode_animate);
    activate_speed_animate(world);
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