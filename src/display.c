#include "../include/display.h"


void  init_textures(SDL_Renderer *renderer, resources_t *resources){
    resources->background = load_image( "assets/img/space-background.bmp",renderer);
    resources->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    resources->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    resources->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
    resources->laser = load_image( "assets/img/laser.bmp",renderer);
    resources->font = load_font("assets/font/arial.ttf", 30);
}

void apply_sprite_adapted(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture_adapted(texture, renderer, sprite->x, sprite->y);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture(texture, renderer, sprite->x, sprite->y, sprite->w, sprite->h);
}

void apply_meteors(SDL_Renderer *renderer, world_t * world, SDL_Texture *texture){
    for (int k = 0; k < world->meteors->nb_meteor ; k++){ // on parcourt le tableau de mur
        if (world->meteors->tab_meteor[k] != NULL)
            apply_texture(texture, renderer, world->meteors->tab_meteor[k]->x, world->meteors->tab_meteor[k]->y, world->meteors->tab_meteor[k]->w, world->meteors->tab_meteor[k]->h);
    }
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
                SDL_Delay(100);
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