/**
 * \file main.c
 * \brief Programme principal initial du niveau 0
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "../include/sdl2-light.h"
#include "../include/sdl2-ttf-light.h"
#include "../include/const.h"
#include "../include/world.h"
#include "../include/display.h"
#include "../include/sprite.h"
#include <stdio.h>
#include <stdlib.h>




/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param resources les resources du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources){
    clear_renderer(renderer);
    apply_background(renderer, resources);
    apply_sprite(renderer, resources->vaisseau, world->joueur);
    apply_sprite(renderer, resources->ligne_arrivee, world->ligne_arrivee);
    apply_walls(renderer, world->tab_wall_meteor , resources->meteorite);

    char str[20];
    sprintf(str, "chrono : %d", world->chrono);
    
    apply_text_adapted(renderer, 0, 0, str , resources->font );

    update_screen(renderer);
}

/**
 * \brief fonction qui met à jour le chrono du jeu
 * 
 * \param world 
 * \param time 
 */
void update_chrono(world_t *world, int time){
        world->chrono = time / 1000;
}

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_textures(*renderer,textures);
}
/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* argv[] )
{
    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        update_chrono(&world, SDL_GetTicks());

        //rafraichissement de l'écran
        refresh_graphics(renderer, &world, &textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
