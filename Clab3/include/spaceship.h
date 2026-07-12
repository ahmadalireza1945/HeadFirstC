# ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct Spaceship{
    float x;
    float y;
    float vx;
    float vy;
    float heading;
    float speed;
    int gone;

} Spaceship;

void movement(ALLEGRO_KEYBOARD_STATE *key_state, Spaceship *spaceship);


#endif