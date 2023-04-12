#include "../include/display.h"


void  init_textures(SDL_Renderer *renderer, resources_t *resources){
    resources->background = load_image( "assets/img/space-background.bmp",renderer);
    resources->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    resources->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    resources->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
    resources->laser = load_image( "assets/img/laser.bmp",renderer);
    resources->font = load_font("assets/font/arial.ttf", 30);
}



void handle_events(SDL_Event *event,world_t *world){    
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            world->gameover = 1;
            SDL_Quit();
        }
        if(event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym){
            case SDLK_d:
                world->joueur->x += MOVING_STEP;
                break;
            case SDLK_q:
                world->joueur->x -= MOVING_STEP;
                break;
            case SDLK_z:
                world->vitesse += 1.0;
                break;
            case SDLK_s:
                if (world->vitesse > INITIAL_SPEED)
                    world->vitesse -= 1.0;
                break;
            case SDLK_ESCAPE:
                world->gameover = 1;
                SDL_Quit();
                break;
            case SDLK_SPACE:
                tirer(world);
                break;
            default:
                break;
            }
        }
    }
}

void apply_background(SDL_Renderer *renderer, resources_t *textures){
    if(textures->background != NULL){
        apply_texture_adapted(textures->background, renderer, 0, 0);
    }
}

void clean_textures(resources_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);
    clean_font(textures->font);
}

void apply_chrono(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    char str[20];
    if (world->chrono >= 60){        
        if (world->chrono % 60 >= 10)
            sprintf(str, "0%d : %d", world->chrono / 60, world->chrono % 60);
        else
            sprintf(str, "0%d : 0%d", world->chrono / 60, world->chrono % 60);
    }else if (world->chrono >= 10){
        sprintf(str, "00 : %d", world->chrono);
    }else if (world->chrono < 10){
        sprintf(str, "00 : 0%d", world->chrono);
    }
    apply_text_adapted(renderer, SCREEN_WIDTH/2, 15, str , resources->font );
}

void apply_win_defeat(SDL_Renderer *renderer, world_t *world, resources_t *resources){
    if (is_game_over(world)) {
        hide_sprite(world->joueur);
        if (world->joueur->y <= world->ligne_arrivee->y){
            apply_text_adapted(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "YOU WIN" , resources->font );
        }else //si on perd
            apply_text_adapted(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "GAME OVER" , resources->font );
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources){
    clear_renderer(renderer);
    apply_background(renderer, resources);
    apply_projectile(renderer, world, resources);
    apply_sprite(renderer, resources->vaisseau, world->joueur);
    apply_sprite_adapted(renderer, resources->ligne_arrivee, world->ligne_arrivee);
    apply_meteors(renderer,  world , resources->meteorite);
    apply_chrono(renderer, world, resources);
    apply_win_defeat(renderer, world, resources);
    update_screen(renderer);
}