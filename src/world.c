#include "../include/world.h"



void init_data(world_t * world){
    world->joueur = malloc(sizeof(sprite_t));
    init_sprite(world->joueur, SCREEN_WIDTH / 2 - SHIP_SIZE / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->ligne_arrivee = malloc(sizeof(sprite_t));
    init_sprite(world->ligne_arrivee, 0, FINISH_LINE_HEIGHT, SCREEN_WIDTH, 1);
    world->mur_meteorite = malloc(sizeof(sprite_t));
    init_sprite(world->mur_meteorite, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    world->vitesse = INITIAL_SPEED;
    world->gameover = 0; // le jeu n'est pas fini
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->joueur);
    free(world->ligne_arrivee);
}

void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    world->mur_meteorite->y += world->vitesse;
}


int is_game_over(world_t *world){
    return world->gameover;
}

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            world->gameover = 1;
        }

        //si une touche est appuyée

        if(event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym){
            case SDLK_d:
                if (world->joueur->x < SCREEN_WIDTH - 3 * SHIP_SIZE / 2){
                        world->joueur->x += MOVING_STEP;
                }
                break;
            case SDLK_q:
                if (world->joueur->x > 0 + SHIP_SIZE / 2 )
                        world->joueur->x -= MOVING_STEP;
                break;
            case SDLK_z:
                if (world->joueur->y > 0 + SHIP_SIZE / 2){
                        world->joueur->y -= MOVING_STEP;
                        world->vitesse += 0.2;
                }
                break;
            case SDLK_s:
                if (world->joueur->y < SCREEN_HEIGHT - 3 * SHIP_SIZE / 2){
                        world->joueur->y += MOVING_STEP;
                        world->vitesse -= 0.2;
                }
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