#include "../include/over.h"
#include "../include/display.h"

void over_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    if(resources->menu != NULL){
        apply_texture(resources->over, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    if (world->joueur->y <= world->ligne_arrivee->y){
            apply_text_adapted(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "YOU WIN" , resources->font );
    }else //si on perd
        apply_text_adapted(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "GAME OVER" , resources->font );
    update_screen(renderer);
}


void over_handle_events(SDL_Event *event, SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world, sounds_t *sounds,const Uint8 *keys){
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
                if (hitbox(*event, 30, 290, 300, 330 )){
                    printf("replay\n");
                    play_sound(sounds->clic, -1, 0);
                    //init(world, textures, sounds, window, renderer); 
                    world->phase = 0;
                }
                if (hitbox(*event, 0, 185, 360, 390 )){
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
    }
} 