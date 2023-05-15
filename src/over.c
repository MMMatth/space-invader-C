#include "../include/over.h"


void over_refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    // on affiche le fond
    if (resources->over != NULL){
        apply_texture(resources->over, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // on applique la texture de fond
    }
    // on affiche si il a gagné ou perdu
    if (world->joueur->y <= world->ligne_arrivee->y){ // si le joueur a gagné
        apply_text_adapted(renderer, 200, 120 , "YOU WIN" , resources->font , 2);
    }else{
        apply_text_adapted(renderer, 200, 120, "GAME OVER" , resources->font , 2);
    }
    // on affiche les trois meilleurs scores enregistrés
    int * best_score = get_sort_score(world);
    char * score = malloc(sizeof(char) * 10);
    apply_text_adapted(renderer, 750, SCREEN_HEIGHT / 2 - 50, "BEST SCORES" , resources->font , 1);
    int i = 0; int j = 0;
    while (i < 3){
        if (best_score[i] == 0){
            i ++;
        }else{
            sprintf(score, "%d sec", best_score[i]);
            apply_text_adapted(renderer, 750, SCREEN_HEIGHT / 2 + j*50, score , resources->font , 1);
            j++;
            i++;
        }
    }
    // on actualise l'écran
    update_screen(renderer);
}


void over_handle_events(SDL_Event *event,world_t *world, sounds_t * sounds){
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
                if (hitbox(*event, 30, 290, 300, 330 )){
                    printf("replay\n");
                    play_sound(sounds->clic, -1, 0);
                    world->phase = 3;
                }
                if (hitbox(*event, 0, 185, 360, 390 )){
                    printf("quit\n");
                    play_sound(sounds->clic, -1, 0);
                    world->gameover = 1;
                    pause(500);
                    SDL_Quit();
                }
            }
            break;
        default:
            break;
        }
    }
} 