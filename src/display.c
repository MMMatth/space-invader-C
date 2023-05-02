#include "../include/display.h"
#include "../include/sound.h"


void  init_textures(SDL_Renderer *renderer, resources_t *resources){
    resources->background = load_image( "assets/img/space-background.bmp",renderer);
    resources->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    resources->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    resources->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
    resources->laser = load_image( "assets/img/laser.bmp",renderer);
    resources->font = load_font("assets/font/arial.ttf", 30);
}



void handle_events(SDL_Event *event,world_t *world, sounds_t * sounds, const Uint8 *keys){    
    static Uint32 last_tire_time = 0; 
    
    Uint32 current_time = SDL_GetTicks(); 

    while (SDL_PollEvent(event)) {
        //Si l'utilisateur a cliqué sur le x de la fenêtre
        if( event->type == SDL_QUIT ) {
            world->gameover = 1;
            SDL_Quit();
        }
        if (event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym){
                case SDLK_ESCAPE:
                    world->gameover = 1;
                    SDL_Quit();
                    break;
                case SDLK_z:
                    world->vitesse += 1;
                    break;
                case SDLK_s:
                    if (world->vitesse > INITIAL_SPEED)
                        world->vitesse -= 1.0;
                    break;
                default:
                    break;
            }
        }
    }
    // on gère les déplacements du joueur avec keys pour pouvoir appuyer sur plusieurs touches en même temps
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]){
        // on fait rien
    }
    else if (keys[SDL_SCANCODE_A]){ // Touche A enfoncée (correspond à Q sur un clavier AZERTY)
        world->joueur->x -= MOVING_STEP;
    }
    else if (keys[SDL_SCANCODE_D]){ // Touche D enfoncée
        world->joueur->x += MOVING_STEP;
    }
    if (keys[SDL_SCANCODE_SPACE]){ // Touche Espace enfoncée

        if (current_time - last_tire_time >= 100){ // on vérifie que le temps écoulé depuis le dernier tir est supérieur à 100ms (pour éviter de tirer trop vite)
            play_sound(sounds->laser, -1, 0);
            last_tire_time = current_time; // on met à jour le temps du dernier tir
            tirer(world);
        }
    }
}


void apply_background(SDL_Renderer *renderer, resources_t *textures){
    if(textures->background != NULL){
        apply_texture_adapted(textures->background, renderer, 0, 0);
    }
}

void clean_ressources(resources_t *textures){
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