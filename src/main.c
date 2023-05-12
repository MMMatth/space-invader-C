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
#include "../include/struct.h"
#include "../include/world.h"
#include "../include/display.h"
#include "../include/sprite.h"
#include "../include/meteors.h"
#include "../include/menu.h"
#include "../include/sound.h"
#include "../include/over.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world, sounds_t *sounds){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_resources(*renderer,textures);
    init_sounds_systeme();
    init_sounds(sounds);
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
    clean_ressources(textures);
    clean_sdl(renderer,window);
    clean_sound();
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* argv[] )
{
    SDL_Event event;
    world_t world;
    sounds_t sounds;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);


    //initialisation du jeu
    init(&window,&renderer,&textures,&world, &sounds);
    
    play_music(sounds.music, -1);

    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        switch (world.phase)
        {
            case 0:
                menu_refresh_graphics(renderer, &world, &textures);
                
                menu_handle_events(&event,&world, &sounds, keys);

                pause(10);

                break;
            
            case 1:

                //gestion des évènements
                handle_events(&event,&world, &sounds, keys);

                //mise à jour des données liée à la physique du monde
                update_data(&world);
                
                update_chrono(&world, SDL_GetTicks());

                //rafraichissement de l'écran
                refresh_graphics(renderer, &world, &textures);
                
                // pause de 10 ms pour controler la vitesse de rafraichissement
                pause(10);

                break;
            
            case 2:

                over_refresh_graphics(renderer, &world, &textures);
                    
                over_handle_events(&event, &world, &sounds, keys);

                pause(10);

                break;

            case 3:
                
                clean(window,renderer,&textures,&world);

                init(&window,&renderer,&textures,&world, &sounds);

                world.phase = 1;
                
                break;

            default:
            
                break;  
        }
    }
    save_chrono(&world);

    refresh_graphics(renderer, &world, &textures); // on rafrachit une dernière fois l'écran pour afficher le message de fin de jeu et faire disparaitre le vaisseau
    
    pause(3000); //pause de 3 secondes à la fin du jeu
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    return 0;
}
