# ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>
#include <math.h>


typedef struct Spaceship{
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    float heading;
    float speed;
    float turn_speed;
    int gone;
} Spaceship;

void movement(ALLEGRO_KEYBOARD_STATE *key_state, Spaceship *spaceship);
void wall_warp(Spaceship *spaceship, int SCREEN_WIDTH, int SCREEN_HEIGHT, int OBJ_SIZE);


#endif