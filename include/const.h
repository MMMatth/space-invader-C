/**
 * \file const.h
 * \brief  fichier qui contient toute les constantes
 * 
 */

/**
 * \brief Largeur de l'écran
*/
#define SCREEN_WIDTH 900

/**
 * \brief Hauteur de l'écran
*/
#define SCREEN_HEIGHT 500

/**
 * \brief Taille du sprite
*/
#define SHIP_SIZE 50

/**
 * \brief taille du projectile
*/
#define PROJECTILE_SIZE 50


/**
 * \brief Pas de déplacement du sprite
*/
#define MOVING_STEP 5

/**
 * \brief Vitesse initiale mouvement des météorites
 */
#define INITIAL_SPEED 1

/**
 * \brief Taille des météorites
 */
#define METEORITE_SIZE 50

/**
 * \brief Nombre de projectile maximum
 */
#define MAX_PROJECTILE 100

/**
 * \brief nombre de meteorite maximum en largeur
 */
#define MAP_WIDTH SCREEN_WIDTH / METEORITE_SIZE

/**
 * \brief nombre de meteorite maximum en hauteur
 */
#define MAP_HEIGHT 500


/**
 * \brief Hauteur de la ligne d'arrivée
 */
#define FINISH_LINE_HEIGHT - (MAP_HEIGHT * METEORITE_SIZE)

