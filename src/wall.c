#include "../include/wall.h"

int nb_meteor = 0;


void init_meteor(world_t * world, int indice, int x, int y, int w, int h){
    world->meteors->tab_meteor[indice] = malloc(sizeof(sprite_t));
    init_sprite(world->meteors->tab_meteor[indice], x, y, w, h);
}

void calc_meteor(char * mapfile){
    FILE* fp = fopen(mapfile, "r");
    if(fp == NULL) printf("Erreur d'ouverture du fichier.\n");
    char c;
    int x = 0, y = 0, i = 0;
    while((c = fgetc(fp)) != EOF) {
        if(c == '1') {
            i++;
        }
        x++;
        if(c == '\n') {
            x = 0;
            y++;
        }
    }
    nb_meteor = i;
    fclose(fp);
}

void init_meteors(world_t *world, char * map_file){
    calc_meteor(map_file);
    world->meteors->nb_meteor = nb_meteor; // on defini le nombre de meteorites
    world->meteors->tab_meteor = malloc(world->meteors->nb_meteor * sizeof(sprite_t*)); // on alloue la memoire pour le tableau de sprite de meteorites
    int **map = malloc(world->meteors->nb_meteor * sizeof(int*));
    for (int i = 0; i < world->meteors->nb_meteor; i++) {map[i] = malloc(2 * sizeof(int));}
    FILE* fp = fopen(map_file, "r");
    if(fp == NULL) printf("Erreur d'ouverture du fichier.\n");
    char c;
    int x = 0, y = 0, i = 0;
    while((c = fgetc(fp)) != EOF) {
        if(c == '1') {
            init_meteor(world, i, x * METEORITE_SIZE, - y * METEORITE_SIZE, METEORITE_SIZE, METEORITE_SIZE);
            i++;
        }
        x++;
        if(c == '\n') {
            x = 0;
            y++;
        }
    }
    fclose(fp);

    for (int i = 0; i < world->meteors->nb_meteor; i++) {free(map[i]);}
    free(map);
}

void update_meteors(world_t *world){
    for (int i = 0; i < world->meteors->nb_meteor; i++) {
        if (world->meteors->tab_meteor[i] != NULL) {
            world->meteors->tab_meteor[i]->y += world->vitesse;
        }
    }
}

void clean_meteors(world_t *world){
    for (int i = 0; i < world->meteors->nb_meteor ; i++) {
        if (world->meteors->tab_meteor[i] != NULL) {
            free(world->meteors->tab_meteor[i]);
        }
    }
}

void handle_meteors(world_t *world){
    for (int i = 0; i < world->meteors->nb_meteor; i++) {
        if (world->meteors->tab_meteor[i] != NULL) {
            handle_sprites_collision(world, world->meteors->tab_meteor[i], world->joueur);
        }
    }
}



