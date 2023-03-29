/**
 * \file main.c
 * \brief Programme principal initial du niveau 0
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "../include/sdl2-light.h"
#include "../include/const.h"
#include "../include/world.h"
#include "../include/sprite.h"
#include <stdio.h>

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée à l'image du sprite. */
    SDL_Texture* ligne_arrivee; /*!< Texture liée à l'image de la ligne d'arrivée. */
    SDL_Texture* meteorite; /*!< Texture liée à l'image de la météorite. */
};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct textures_s textures_t;

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->ligne_arrivee);
    clean_texture(textures->meteorite);
}

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "assets/img/space-background.bmp",renderer);
    textures->vaisseau = load_image( "assets/img/spaceship.bmp",renderer);
    textures->ligne_arrivee = load_image( "assets/img/finish_line.bmp",renderer);
    textures->meteorite = load_image( "assets/img/meteorite.bmp",renderer);
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
        apply_texture(textures->background, renderer, 0, 0);
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


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param textures les textures du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    //application du sprite
    apply_sprite(renderer, textures->vaisseau, world->joueur);
    //application de la ligne d'arrivée
    apply_sprite(renderer, textures->ligne_arrivee, world->ligne_arrivee);
    // boucle pour afficher les météorites 3 en largeur et 7 en hauteur
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 7; j++){
            apply_wall(renderer, textures->meteorite , world->mur_meteorite->x + i * METEORITE_SIZE , world->mur_meteorite->y + j * METEORITE_SIZE);
        }
    }

    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main( int argc, char* argv[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
