
#include "../include/chrono.h"

void save_chrono(world_t *world){
    if (world->gameover = 1 && world->joueur->y <= world->ligne_arrivee->y){
        FILE *fichier = NULL;
        fichier = fopen("score.txt", "a");
        if(fichier != NULL){
            fprintf(fichier, "%d\n", world->chrono);
            fclose(fichier);
        }
        else{
            printf("Erreur lors de l'ouverture du fichier");
        }
    }
}

int * get_sort_score(world_t * world){
    FILE *fichier = NULL;
    fichier = fopen("score.txt", "r");
    int len = 0;
    int *score = malloc(sizeof(int) * 1000);
    while (!feof(fichier) && len < 1000){
        fscanf(fichier, "%d", &score[len]);
        len++;
    }
    fclose(fichier);
    
    // trie par ordre croissant
    score = tri_tableau(score, len);
    // renvoie que les 3 meilleurs scores
    if (len > 3){
        int * score2 = malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++){
            score2[j] = score[j];
        }
        return score2;
    }
    return score;
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