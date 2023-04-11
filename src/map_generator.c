#define FNL_IMPL 1
#define WIDTH 18
#define HEIGHT 100

#include "../include/FastNoiseLite.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    // Create and configure noise state
    fnl_state noise = fnlCreateState();
    // noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    srand(time(NULL));
    noise.seed = rand();
    noise.frequency = 0.075;
    noise.gain = 0.3;

    // Gather noise data
    float* noiseData = malloc(HEIGHT * WIDTH * sizeof(float));
    int index = 0;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            float noiseValue = fnlGetNoise2D(&noise, x, y);
            if (noiseValue > 0.5) {
                noiseData[index++] = 1;
            } else {
                noiseData[index++] = 0;
            }
        }
    }


    // on ecrit dans un fichier les données
    FILE *f = fopen("map.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(f, "%d", (int)noiseData[y * WIDTH + x]);
        }
        fprintf(f, "\n");
    }
    fclose(f);


    // Free data later
    free(noiseData);
    return 0;
}
