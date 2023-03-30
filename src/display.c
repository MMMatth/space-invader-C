#include "../include/display.h"

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture(texture, renderer, sprite->x, sprite->y);
}

void handle_events(SDL_Event *event,world_t *world){    
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            world->gameover = 1;
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
                world->vitesse += 0.2;
                break;
            case SDLK_s:
                if (world->vitesse > INITIAL_SPEED)
                    world->vitesse -= 0.2;
                break;
            case SDLK_ESCAPE:
                world->gameover = 1;
                break;
            default:
                break;
            }
        }
    }
}

void apply_wall(SDL_Renderer *renderer, SDL_Texture *textures, int x, int y){
    if (textures != NULL){
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = METEORITE_SIZE;
        rect.h = METEORITE_SIZE;
        SDL_RenderCopy(renderer, textures, NULL, &rect);
    }
}

void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
        apply_texture(textures->background, renderer, 0, 0);
    }
}

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "assets/img/space-background.bmp",renderer);
    textures->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    textures->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    textures->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
}

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);
}