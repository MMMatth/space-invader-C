#define FNL_IMPL 1

#include "../include/FastNoiseLite.h"
#include "../include/const.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    srand(time(NULL));
    noise.seed = rand();
    noise.frequency = 0.075;
    noise.gain = 0.3;

    float* noiseData = malloc(MAP_HEIGHT * MAP_WIDTH * sizeof(float));
    int index = 0;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            float noiseValue = fnlGetNoise2D(&noise, x, y);
            if (noiseValue > 0.5) {
                noiseData[index++] = 1;
            } else {
                noiseData[index++] = 0;
            }
        }
    }

    FILE *f = fopen("map.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            fprintf(f, "%d", (int)noiseData[y * MAP_WIDTH + x]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    free(noiseData);
    return 0;
}
