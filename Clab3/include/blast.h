# ifndef BLAS_H
#define BLAS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "spaceship.h"
#include "globals.h"

struct Spaceship;

typedef struct Blast{
    float x , y;
    float dx, dy;
    float heading;
    float speed;
    int active;
    ALLEGRO_COLOR color;
} Blast;


void fire_blast(struct Spaceship *spaceship, Blast *blast, int maxBlasts);
void update_blast(Blast *blast, int maxBlasts);
void draw_blast(ALLEGRO_DISPLAY *display, Blast *blast, int maxBlasts);

#endif
