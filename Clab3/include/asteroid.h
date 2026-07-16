#ifndef ASTEROID_H
#define ASTEROID_H
#include <allegro5/allegro.h>
struct Spaceship;
struct Blast;


typedef enum LabelPosisi {
    KIRI,
    TENGAH,
    KANAN,
} LabelPosisi;

typedef struct Asteroid {
    float x, y;
    float dx,dy;
    float heading;
    float twist;
    float speed;
    float rot_velocity;;
    float scale;
    float shoot_timer;
    float shoot_cooldown;
    LabelPosisi label;
    int active;
} Asteroid;

void spawn_asteroids(Asteroid *asteroid, int count);
void update_asteroids(Asteroid *asteroid, int count);
void draw_asteroids(Asteroid *asteroid, int count, ALLEGRO_BITMAP *image);


#endif
