#include "../include/menu.h"


bool hitbox(SDL_Event event, int top_left, int top_right, int bottom_left, int bottom_right){   
    if (event.button.x >= top_left // Si la souris est dans la hitbox
        && event.button.x <= top_right 
        && event.button.y >= bottom_left 
        && event.button.y <= bottom_right)
        return true; // On retourne true
    else
        return false; // On retourne false
}

void menu(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    if(resources->menu != NULL){
        apply_texture_adapted(resources->menu, renderer, 0, 0);
    }
    update_screen(renderer);
}

void event_menu(SDL_Event *event,world_t *world, sounds_t * sounds, const Uint8 *keys){    
    Uint8 *keystates;
    while(SDL_PollEvent(event)) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            world->gameover = 1;
            SDL_Quit();
        }
        // si on clique
        if (event->type == SDL_MOUSEBUTTONDOWN){
            if (event->button.button == SDL_BUTTON_LEFT){
                if (hitbox(*event, 0, 240, 270, 310  )){
                    world->phase = 1;
                }
                if (hitbox(*event, 0, 240, 315, 350  )){
                    printf("option\n");
                }
                if (hitbox(*event, 0, 240, 365, 400  )){
                    printf("credits\n");
                }
                if (hitbox(*event, 3, 240, 405, 440  )){
                    printf("exit\n");
                    world->gameover = 1;
                    SDL_Quit();
                }
            }
        if(event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym){
            case SDLK_SPACE:
                world->phase = 1;
                world->tps = SDL_GetTicks();
                printf("tps = %d\n", world->tps);
                break;
            case SDLK_ESCAPE:
                world->gameover = 1;
                SDL_Quit();
                break;
            default:
                break;
            }
        }
    }
} }