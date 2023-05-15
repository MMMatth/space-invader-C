#include "../include/display.h"


void  init_resources(SDL_Renderer *renderer, resources_t *resources){
    // on charge les images
    resources->background = load_image( "assets/img/space-background.bmp",renderer);
    resources->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    resources->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    resources->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
    resources->laser = load_image( "assets/img/laser.bmp",renderer);
    resources->menu = load_image("assets/img/menu.png", renderer);
    resources->over = load_image("assets/img/over.png", renderer);
    // on charge la police
    resources->font = load_font("assets/font/space_age.ttf", 30);
    // on charge les aniamations
    resources->explode_img = malloc(sizeof(SDL_Texture*) * MAX_ANIM);
    resources->speed_img = malloc(sizeof(SDL_Texture*) * MAX_ANIM);

    char path[100];
    // on charge les images des explosions
    for (int i = 0; i < 6; i++){
        sprintf(path, "assets/img/explode_animate/%d.png", i + 1);
        resources->explode_img[i] = load_image(path, renderer);
    }
    // on charge les images de la vitesse
    for (int i = 0; i < 9; i++){
        sprintf(path, "assets/img/speed_animate/%d.png", i + 1); 
        resources->speed_img[i] = load_image(path, renderer);
    }

}



void handle_events(SDL_Event *event,world_t *world, sounds_t * sounds, const Uint8 *keys){    
    static Uint32 last_tire_time = 0; 
    
    Uint32 current_time = SDL_GetTicks(); 

    while (SDL_PollEvent(event)){
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
            break;

        default:
            break;
        }
    }
    // on gère les déplacements du joueur avec keys pour pouvoir appuyer sur plusieurs touches en même temps
    if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_D]){ // Si les touches A et D sont enfoncées en même temps
        // on fait rien
    }
    else if (keys[SDL_SCANCODE_A]){ // Touche A enfoncée (correspond à Q sur un clavier AZERTY)
        world->joueur->x -= MOVING_STEP;
    }
    else if (keys[SDL_SCANCODE_D]){ // Touche D enfoncée
        world->joueur->x += MOVING_STEP;
    }
    if (keys[SDL_SCANCODE_SPACE]){ // Touche Espace enfoncée
        if (current_time - last_tire_time >= 250){ // on vérifie que le temps écoulé depuis le dernier tir est supérieur à 250ms (pour éviter de tirer trop vite)
            play_sound(sounds->laser, -1, 0); // on joue le son du tir
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
    // on libère les images
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);
    clean_texture(textures->laser);
    clean_texture(textures->menu);
    clean_texture(textures->over);
    // on libère la police
    clean_font(textures->font);
    // on libère les animations
    for (int i = 0; i < 6; i++){
        clean_texture(textures->explode_img[i]);
    }free(textures->explode_img);
    for (int i = 0; i < 9; i++){
        clean_texture(textures->speed_img[i]);
    }free(textures->speed_img);
}



void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources){
    clear_renderer(renderer);
    apply_background(renderer, resources);
    apply_projectile(renderer, world, resources);
    apply_sprite(renderer, resources->vaisseau, world->joueur);
    apply_sprite_adapted(renderer, resources->ligne_arrivee, world->ligne_arrivee);
    apply_meteors(renderer,  world , resources->meteorite);
    apply_chrono(renderer, world, resources);
    // on applique les animations des explosions
    for (int i = 0; i < MAX_ANIM; i++){
        apply_animate(renderer, world->explode_animate[i], resources->explode_img, world->explode_animate[i]->x, world->explode_animate[i]->y, METEORITE_SIZE, METEORITE_SIZE);
    }
    // on applique l'animation de la vitesse
    apply_animate(renderer, world->speed_animate, resources->speed_img, world->speed_animate->x, world->speed_animate->y, SCREEN_WIDTH, SCREEN_HEIGHT);
    update_screen(renderer);
}

bool hitbox(SDL_Event event, int x_top_left, int x_bottom_left, int y_top_left, int y_bottom_left){
    if (event.button.x >= x_top_left // Si la souris est dans la hitbox
        && event.button.x <= x_bottom_left 
        && event.button.y >= y_top_left 
        && event.button.y <= y_bottom_left)
        return true; // On retourne true
    else
        return false; // On retourne false
}