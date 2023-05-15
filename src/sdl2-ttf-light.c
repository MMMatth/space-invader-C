#include "../include/sdl2-ttf-light.h"

void init_ttf(){
    if(TTF_Init()==-1) { // On initialise le moteur TTF
        printf("TTF_Init: %s\n", TTF_GetError()); // En cas d'erreur, on affiche un message et on quitte
    }
}

TTF_Font * load_font(const char *path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size); // On ouvre la police
    if(font == NULL){ // Si l'ouverture a échoué, on affiche un message d'erreur et on quitte
        fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
    }
    return font;
}

void apply_text(SDL_Renderer *renderer,int x, int y, int w, int h, const char *text, TTF_Font *font){
    SDL_Color color = { 255, 255, 255 }; // blanc
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color); // On crée une surface contenant le texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // On crée la texture correspondante
    SDL_Rect dstrect2 = {x, y, w, h}; // On crée un rectangle qui va contenir la texture
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2); // On copie la texture dans le renderer (affichage)
}

void apply_text_adapted(SDL_Renderer *renderer,int x, int y, const char *text, TTF_Font *font, int size){
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect2 = {x - surface->w / 2 , y - surface->h /2, surface->w * size , surface->h * size}; // On crée un rectangle qui va contenir la texture
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font); // On ferme la police
}
