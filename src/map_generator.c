/**
 * \file map_generator.c
 * \brief fichier qui permet de générer la map grace au bruit de perlin
 */

#define FNL_IMPL 1

#include "../include/FastNoiseLite.h"
#include "../include/const.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float * cree_bruit_perlin(float frequency, float gain ){
    fnl_state noise = fnlCreateState(); // on crée le bruit de perlin
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2; // on utilise le bruit de perlin
    srand(time(NULL)); // on actualise l'aléatoire
    noise.seed = rand(); // on met une seed aléatoire
    noise.frequency = frequency; 
    noise.gain = gain;

    float * noiseData = malloc(MAP_HEIGHT * MAP_WIDTH * sizeof(float)); // tableau qui va contenir les valeurs du bruit de perlin
    int index = 0; // index pour parcourir le tableau

    for (int y = 0; y < MAP_HEIGHT; y++) // on parcours le tableau
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            float noiseValue = fnlGetNoise2D(&noise, x, y); // on récupère la valeur du bruit de perlin
            if (noiseValue > 0.5) { // si la valeur est supérieur à 0.5 on met 1 dans le tableau sinon 0
                noiseData[index++] = 1;
            } else {
                noiseData[index++] = 0;
            }
        }
    }

    return noiseData;
}

void ecrire_carte(float * noiseData){
    FILE *f = fopen("map.txt", "w"); // on ouvre le fichier
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int y = 0; y < MAP_HEIGHT; y++) { // on parcours le tableau
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            fprintf(f, "%d", (int)noiseData[y * MAP_WIDTH + x]); // on écrit la valeur dans le fichier
        }
        fprintf(f, "\n");
    }
    fclose(f); // on ferme le fichier
}

int main(int argc, char *argv[]){
    float * noiseData = cree_bruit_perlin(0.075, 0.3); // on récupère le tableau de bruit de perlin
    ecrire_carte(noiseData); // on écrit le tableau dans un fichier
    return EXIT_SUCCESS;
}
