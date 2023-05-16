
#include "../include/chrono.h"

void save_chrono(world_t *world){
    if (world->joueur->y <= world->ligne_arrivee->y){ // si la partie est fini et que le joueur a depassé la ligne d'arrivée
        FILE *fichier = NULL; // on initialise le fichier
        fichier = fopen("assets/score.txt", "a"); // on ouvre le fichier en mode ajout
        if(fichier != NULL){ // on verifie que le fichier soit bien ouvert
            fprintf(fichier, "%d\n", world->chrono); // on ecrit le score dans le fichier
            fclose(fichier); // on ferme le fichier
        }
        else{ // si le fichier n'est pas ouvert
            printf("Erreur lors de l'ouverture du fichier"); // on affiche une erreur
        }
    }
}

int * get_sort_score(world_t * world){
    FILE *fichier = NULL;
    fichier = fopen("assets/score.txt", "r");
    int len = 0; // on initialise la longueur du tableau
    int * score = malloc(sizeof(int) * 1000); // on initialise le tableau
    if (fichier != NULL){
        while (!feof(fichier) && len < 1000){ // on parcours le fichier
            fscanf(fichier, "%d", &score[len]); // on recupere le score
            len++; // on incremente la longueur du tableau
        }
        fclose(fichier);
    }else{
        printf("Erreur lors de l'ouverture du fichier");
    }
    // trie par ordre croissant
    score = tri_tableau(score, len); // on trie le tableau
    // renvoie que les 3 meilleurs scores
    if (len > 3){ // si il y a plus de 3 scores
        int * score2 = malloc(sizeof(int) * 3); // on initialise un nouveau tableau
        for (int j = 0; j < 3; j++){ // on recupere les 3 meilleurs scores
            score2[j] = score[j];
        }
        free(score); // on libere le tableau
        return score2; // on renvoie le tableau
    }
    return score; // si il y a moins de 3 scores on renvoie le tableau
}

char * get_chrono_str(world_t *world){
    char *chrono = malloc(sizeof(char) * 10);
    if (world->chrono >= 60){ // si le temp fait plus de 60 secondes        
        if (world->chrono % 60 >= 10) // si les secondes sont superieur a 10
            sprintf(chrono, "0%d : %d", world->chrono / 60, world->chrono % 60);
        else 
            sprintf(chrono, "0%d : 0%d", world->chrono / 60, world->chrono % 60);
    }else if (world->chrono >= 10){ // si le temp fait plus de 10 secondes
        sprintf(chrono, "00 : %d", world->chrono);
    }else if (world->chrono < 10){ // si le temp fait moins de 10 secondes
        sprintf(chrono, "00 : 0%d", world->chrono);
    }
    return chrono;
}

int * tri_tableau(int * tab, int len){
    int tmp;
    for (int j = 0; j < len; j++){
        for (int k = j + 1; k < len; k++){
            if (tab[j] > tab[k]){
                tmp = tab[j];
                tab[j] = tab[k];
                tab[k] = tmp;
            }
        }
    }
    return tab;
}

void update_chrono(world_t *world, int time){
    world->chrono = time / 1000;
}

void apply_chrono(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    apply_text_adapted(renderer, SCREEN_WIDTH/2, 15, get_chrono_str(world) , resources->font, 1 );
}