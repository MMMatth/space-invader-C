#include "../include/meteors.h"

void init_meteors(world_t *world, char * map_file){
    world->meteors->nb_meteor = calc_meteor(map_file); // on defini le nombre de meteorites
    world->meteors->tab_meteor = malloc(world->meteors->nb_meteor * sizeof(sprite_t*)); // on alloue la memoire pour le tableau de sprite de meteorites
    FILE* fp = fopen(map_file, "r"); // on ouvre le fichier map afin de le lire
    if(fp == NULL) printf("Erreur d'ouverture du fichier.\n"); // on gère le cas ou il y'a une erreur dans l'ouverture
    char c;
    int x = 0, y = 0, nb_meteor = 0;

    while((c = fgetc(fp)) != EOF) {
        if (c == '1') { // si le caractere est un 1 alors c'est un asteroide
            init_meteor(world, nb_meteor // nombre du meteore
            , x * METEORITE_SIZE // position du meteore en x
            , - y * METEORITE_SIZE // position du meteore en y
            , METEORITE_SIZE, METEORITE_SIZE);
            nb_meteor++;
        }
        x++;
        if(c == '\n') { // si on est arrive au bout d'une ligne
            x = 0; // on reinitialise la largeur
            y++; // on passe sur la deuxieme ligne
        }
    }
    fclose(fp);
}

void init_meteor(world_t * world, int indice, int x, int y, int w, int h){
    world->meteors->tab_meteor[indice] = malloc(sizeof(sprite_t)); // on alloue la memoire pour un asteroide
    init_sprite(world->meteors->tab_meteor[indice], x, y, w, h); // on initialise l'asteroide
}

int calc_meteor(char * mapfile){
    FILE* fp = fopen(mapfile, "r"); // on ouvre le fichier map afin de le lire
    if(fp == NULL) printf("Erreur d'ouverture du fichier.\n"); // on gère le cas ou il y'a une erreur dans l'ouverture
    char c;
    int nb_meteor = 0;
    while((c = fgetc(fp)) != EOF) { // on parcours le fichier
        if(c == '1') { // si le caractère est un 1 alors on ajoute 1 
            nb_meteor++;
        }
    }
    fclose(fp); // on ferme le fichier
    return nb_meteor;
}



void update_meteors(world_t *world){
    for (int i = 0; i < world->meteors->nb_meteor; i++) {
        if (world->meteors->tab_meteor[i] != NULL) { // on verfie que le meteors est bien definie
            world->meteors->tab_meteor[i]->y += world->vitesse; // on le deplace avec la vitesse du jeu
        }
    }
}

void clean_meteors(world_t *world){
    for (int i = 0; i < world->meteors->nb_meteor ; i++) {
        if (world->meteors->tab_meteor[i] != NULL) {
            free(world->meteors->tab_meteor[i]); // on libère la memoire pour chaque asteroide
        }
    }
    free(world->meteors->tab_meteor); // on libere l'adresse du tableau
}

void apply_meteors(SDL_Renderer *renderer, world_t * world, SDL_Texture *texture){
    for (int k = 0; k < world->meteors->nb_meteor ; k++){ // on parcourt le tableau de mur
        if (world->meteors->tab_meteor[k] != NULL)
            apply_texture(texture, renderer, world->meteors->tab_meteor[k]->x, world->meteors->tab_meteor[k]->y, world->meteors->tab_meteor[k]->w, world->meteors->tab_meteor[k]->h);
    }
}

