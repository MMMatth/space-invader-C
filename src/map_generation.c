#include <stdio.h>
#include <SDL2\SDL.h>
 

int main(int argc, char *argv[]) {
    SDL_Surface *surface = SDL_LoadBMP("assets/img/noise.bmp");
    FILE *fp = fopen("map.txt", "w");

    if(surface == NULL || fp == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }

    Uint8 *pixels = (Uint8*)surface->pixels;
    int width = surface->w;
    int height = surface->h;

    const int threshold = 128;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int index = y * surface->pitch + x;
            int value = pixels[index];
            if(value < threshold) {
                fprintf(fp, "1");
            } else {
                fprintf(fp, "0");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    SDL_FreeSurface(surface);

    return 0;
}