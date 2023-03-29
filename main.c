/**
 * \file main.c
 * \brief Programme principal initial du niveau 0
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */
#include "sdl2-light.h"
#include <stdio.h>


/**
 * \brief Largeur de l'écran
*/
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran
*/
#define SCREEN_HEIGHT 480

/**
 * \brief Taille du sprite
*/
#define SHIP_SIZE 32

/**
 * \brief Pas de déplacement du sprite
*/
#define MOVING_STEP 20

#define FINISH_LINE_HEIGHT -1000

#define INITIAL_SPEED 1

#define METEORITE_SIZE 32

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
 * \brief structure qui représente un sprite
 */
struct sprite_s{
    int x; /*!< Position en x du sprite */
    int y; /*!< Position en y du sprite */
    int w; /*!< Largeur du sprite */
    int h; /*!< Hauteur du sprite */
};

typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t* joueur; /*!< Sprite représentant le joueur */
    sprite_t* ligne_arrivee; /*!< Sprite représentant la ligne d'arrivée */
    sprite_t* mur_meteorite; /*!< Sprite représentant le mur de météorites */
    int vitesse; /*!< Vitesse de déplacement du fond */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;



void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
}

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d \n", sprite->x, sprite->y, sprite->w, sprite->h);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    apply_texture(texture, renderer, sprite->x, sprite->y);
}


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
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


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->joueur);
    free(world->ligne_arrivee);
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world){
    world->ligne_arrivee->y += world->vitesse;
    world->mur_meteorite->y += world->vitesse;

}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            if (event->key.keysym.sym == SDLK_d){
                if (world->joueur->x < SCREEN_WIDTH - 3 * SHIP_SIZE / 2){
                    world->joueur->x += MOVING_STEP;
                }
            }else if (event->key.keysym.sym == SDLK_q){
                if (world->joueur->x > 0 + SHIP_SIZE / 2 )
                    world->joueur->x -= MOVING_STEP;
            }else if (event->key.keysym.sym == SDLK_z){
                if (world->joueur->y > 0 + SHIP_SIZE / 2){
                    world->joueur->y -= MOVING_STEP;
                    world->vitesse += 1;
                }
            }else if (event->key.keysym.sym == SDLK_s){
                if (world->joueur->y < SCREEN_HEIGHT - 3 * SHIP_SIZE / 2){
                    world->joueur->y += MOVING_STEP;
                    world->vitesse -= 1;
                }
            }else if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }else if(event->key.keysym.sym == SDLK_SPACE){
                print_sprite(world->joueur);
            }
        }
    }
}


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
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->vaisseau = load_image( "ressources/spaceship.bmp",renderer);
    textures->ligne_arrivee = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
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
int main( int argc, char* args[] )
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
