#include <stdio.h>
#include "../include/sprite.h"

int main(){
    sprite_t * sprite;
    init_sprite(sprite, 0, 0, 10, 10);
    print_sprite(sprite);
    return 0;
}