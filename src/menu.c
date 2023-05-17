#include "../include/menu.h"




void menu_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    if(resources->menu != NULL){
        apply_texture(resources->menu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    update_screen(renderer);
}


void menu_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds){    
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
                if (hitbox(*event, 0, 185, 305, 330 )){
                    play_sound(sounds->clic, -1, 0);
                    world->phase = 1;
                }if (hitbox(*event, 0, 185, 360, 390 )){
                    play_sound(sounds->clic, -1, 0);
                    fade_out_music(500); // On fait un fondu de 500ms
                    world->gameover = 1;
                    pause(500); // On attend 500ms pour que le son puisse se jouer
                    SDL_Quit();
                }
            }
            break;
        default:
            break;
        }
    }
} 