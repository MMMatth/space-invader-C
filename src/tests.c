/**
 * \file tests.c
 * \brief fichier comportant les testes de chaque module
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/animate.h"
#include "../include/world.h"
#include "../include/struct.h"
#include "../include/const.h"

int nb_error = 0;

/**
 * \brief fonction qui sert pour les erreurs
 * 
 * \param message 
 */
void error(char * message){
    printf("Erreur : %s\n", message);
    nb_error++;
}

/**************************************************/
/*                    ANIMATE                     */
/**************************************************/

void test_init_aniamtes(){
    animate_t ** animate = malloc(sizeof(struct animate_s) * MAX_ANIM);
    init_animates("test", 10, 100, animate, 1);
    for (int i = 0; i < MAX_ANIM; i++){
        if (animate[i]->nb_frames != 10) error("init_animates : nb_frames");
        if (animate[i]->frame_duration != 100) error("init_animates : frame_duration");
        if (animate[i]->loop != 1) error("init_animates : loop");
        if (animate[i]->active != 0) error("init_animates : active");
        if (animate[i]->x != 0) error("init_animates : x");
        if (animate[i]->y != 0) error("init_animates : y");
    }
    clean_animates(animate);
}

void test_start_aniamtes(){
    animate_t ** animate = malloc(sizeof(struct animate_s) * MAX_ANIM);
    init_animates("test", 10, 100, animate, 1);
    start_animates(animate, 0, 0);
    int j = 0;
    for (int i = 0; i < MAX_ANIM; i++){
        if (animate[i]->active == 1) j++;
    }
    if (j != 1) error("start_animates : active");
    clean_animates(animate);
}

void test_pause_animate(){
    animate_t * animate = malloc(sizeof(struct animate_s));
    init_animate("test", 10, 100, animate, 1);
    start_animate(animate, 0, 0);
    pause_animate(animate);
    if (animate->active != 0) error("pause_animate : active");
    clean_animate(animate);
}

void test_update_animate(){
    animate_t * animate = malloc(sizeof(struct animate_s));
    init_animate("test", 10, 100, animate, 1);
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    start_animate(animate, 0, 0);
    update_animate(world, animate);
    if (animate->y != INITIAL_SPEED) error("update_animate : update");
    clean_animate(animate);
    clean_data(world);
}


void test_animate(){
    test_init_aniamtes();
    test_start_aniamtes();
    test_pause_animate();
    test_update_animate();
}

/**************************************************/
/*                 CHRONO                         */
/**************************************************/

void test_get_chrono_str(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    world->chrono = 60;
    char * str = get_chrono_str(world);
    if (str[0] != '0' && str[1] != '1') error("get_chrono_str : str");
    clean_data(world);
}

void test_tri_tableau(){
    int tab[5] = {5, 4, 3, 2, 1};
    tri_tableau(tab, 5);
    for (int i = 0; i < 5; i++){
        if (tab[i] != i + 1) error("tri_tableau : tri");
    }
}

void test_update_chrono(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    update_chrono(world, 1200); // 1200 ms sont passé
    if (world->chrono != 1) error("update_chrono : chrono");
    clean_data(world);
}

void test_chrono(){
    test_get_chrono_str();
    test_tri_tableau();
    test_update_chrono();
}

/**************************************************/
/*                    DISPLAY                     */
/**************************************************/

// aucun test possible car c'est que du graphique

/**************************************************/
/*                    METEORS                     */
/**************************************************/

void test_init_meteors(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    for (int i = 0; i < world->meteors->nb_meteor; i++){
        if (world->meteors->tab_meteor[i] == NULL) error("init_meteors : active");
    }
    clean_data(world);
    free(world);
}

void test_update_meteors(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world); // on initialise les données
    world->meteors->tab_meteor[0]->y = 0; // on le place en haut de l'écran
    update_meteors(world); // on met à jour les météores
    if (world->meteors->tab_meteor[0]->y != INITIAL_SPEED) error("update_meteors : update");
    clean_data(world);
    free(world);
}

void test_meteors(){
    test_update_meteors();
    test_init_meteors();
}

/**************************************************/
/*                  PROJECTILE                    */
/**************************************************/

void test_init_projectiles(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    init_projectiles(world);
    for (int i = 0; i < MAX_PROJECTILE; i++){
        if (world->projectiles[i]->active != 0) error("init_projectiles : active");
        if (world->projectiles[i]->x != -1) error("init_projectiles : x");
        if (world->projectiles[i]->y != -1) error("init_projectiles : y");
        if (world->projectiles[i]->variation != 0) error("init_projectiles : variation");
    }
    clean_data(world);
}

void test_tirer(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    tirer(world);
    for (int i = 0; i < MAX_PROJECTILE; i++){
        if (world->projectiles[i]->active == 1){
            if (world->projectiles[i]->x != world->joueur->x + SHIP_SIZE / 2 - PROJECTILE_SIZE / 4) error("tirer : x");
            if (world->projectiles[i]->y != world->joueur->y) error("tirer : y");
            if (world->projectiles[i]->variation != 0) error("tirer : variation");
        }
    }
    clean_data(world);
}

void test_est_dehors(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    tirer(world);
    for (int i = 0; i < MAX_PROJECTILE; i++){
        if (world->projectiles[i]->active == 1){
            est_dehors(world->projectiles[i]); // il est dans l'écran
            if (world->projectiles[i]->active != 1) error("est_dehors : active");
            world->projectiles[i]->y = -200;
            est_dehors(world->projectiles[i]); // il est en dehors de l'écran
            if (world->projectiles[i]->active != 0) error("est_dehors : active");
        }
    }
    clean_data(world);
}

void test_update_projectile(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    tirer(world);
    float y = world->projectiles[0]->y;
    update_projectile(world);
    if (world->projectiles[0]->y == y) error("update_projectile : y");
    clean_data(world);
}

void test_projectile(){
    test_init_projectiles();
    test_tirer();
    test_est_dehors();
    test_update_projectile();
}

/**************************************************/
/*                    SOUND                       */
/**************************************************/

// compliqué à tester car c'est du son

/**************************************************/
/*                    SPRITE                      */
/**************************************************/

void test_init_sprite(){
    sprite_t * sprite = malloc(sizeof(struct sprite_s));
    init_sprite(sprite, 10, 10, 10, 10);
    if (sprite->x != 10) error("init_sprite : x");
    if (sprite->y != 10) error("init_sprite : y");
    if (sprite->w != 10) error("init_sprite : w");
    if (sprite->h != 10) error("init_sprite : h");
    free(sprite);
}

void test_hide_sprite(){
    sprite_t * sprite = malloc(sizeof(struct sprite_s));
    init_sprite(sprite, 10, 10, 10, 10);
    hide_sprite(sprite);
    if (sprite->w != 0) error("hide_sprite : w");
    if (sprite->h != 0) error("hide_sprite : h");
    free(sprite);
}

void test_sprites_collide(){
    sprite_t * sprite1 = malloc(sizeof(struct sprite_s));
    sprite_t * sprite2 = malloc(sizeof(struct sprite_s));
    init_sprite(sprite1, 10, 10, 10, 10);
    init_sprite(sprite2, 10, 10, 10, 10);
    if (sprites_collide(sprite1, sprite2) != 1) error("sprites_collide : collision");
    sprite2->x = 100;
    if (sprites_collide(sprite1, sprite2) != 0) error("sprites_collide : pas de collision");
    free(sprite1);
    free(sprite2);
}

void test_sprite(){
    test_init_sprite();
    test_hide_sprite();
    test_sprites_collide();
}

/**************************************************/
/*                    WORLD                       */
/**************************************************/

void test_init_data(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    if (world->vitesse != INITIAL_SPEED) error("init_data : vitesse");
    if (world->gameover != 0) error("init_data : score");
    if (world->chrono != 0) error("init_data : chrono");
    if (world->phase != 0) error("init_data : score");
    clean_data(world);
}

void test_check_pos(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    world->joueur->x = -1;
    check_pos(world); // on reposionne le joueur si il est en dehors de l'écran
    if (world->joueur->x != 0) error("check_pos : x");
    clean_data(world);
}

void test_handle_sprites_collision(){
    world_t * world = malloc(sizeof(struct world_s));
    init_data(world);
    world->joueur->x = 0;
    world->joueur->y = 0;
    world->ligne_arrivee->x = 0;
    world->ligne_arrivee->y = 0;
    est_fini(world);
    if (world->phase != 2) error("est_fini : gameover");
    world->phase = 0;
    world->ligne_arrivee->x = 20000;
    world->ligne_arrivee->y = 20000;
    est_fini(world); // on reverifie si le joueur est arrivé
    if (world->phase != 0) error("est_fini : pas fini");
    clean_data(world);
}

void test_world(){
    test_init_data();
    test_check_pos();
    test_handle_sprites_collision();
}

/**************************************************/
/*                    LE MAIN                     */
/**************************************************/

int main(int argc, char *argv[]){
    test_animate();
    test_chrono();
    test_projectile();
    test_sprite();
    test_world();
    test_meteors();
    printf("Il y'a %d erreur \n", nb_error);
    return 0;
}