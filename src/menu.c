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

void menu_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    if(resources->menu != NULL){
        apply_texture(resources->menu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    update_screen(renderer);
}


void menu_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds, const Uint8 *keys){    
    Uint8 *keystates;
    while(SDL_PollEvent(event)) {
        switch (event->type)
        {
        case SDL_QUIT:
            world->gameover = 1;
            SDL_Quit();
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                world->gameover = 1;
                SDL_Quit();
                break;
            default:
                break;
            }
            break; 
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT){
                printf("x = %d, y = %d\n", event->button.x, event->button.y);
                if (hitbox(*event, 0, 185, 305, 330 )){
                    printf("play\n");
                    play_sound(sounds->clic, -1, 0);
                    world->phase = 1;
                }if (hitbox(*event, 0, 185, 360, 390 )){
                    printf("quit\n");
                    play_sound(sounds->clic, -1, 0);
                    world->gameover = 1;
                    SDL_Quit();
                }
            }
            break;
        default:
            break;
        }
        // si on clique
    }
} 