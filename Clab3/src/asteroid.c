#include "../include/asteroid.h"

#include <math.h>

#include "../include/blast.h"

void spawn_asteroids(Asteroid *asteroid, int count) {
    for (int i = 0; i < count; i++) {

        asteroid[i].active = true;
        asteroid[i].speed = rand() % 3;
        asteroid[i].x = rand() % SCREEN_WIDTH;
        asteroid[i].y = rand() % SCREEN_HEIGHT;
        asteroid[i].scale = (float) (rand() % 101 + 150) / 100.0f;
        asteroid[i].heading = rand() % 4;
        asteroid[i].dx = cos(asteroid[i].heading) * asteroid[i].speed;
        asteroid[i].dy = sin(asteroid[i].heading) * asteroid[i].speed;
    }
}

void update_asteroids(Asteroid *asteroid, int count){
    for (int i = 0; i < count; i++) {
        asteroid[i].x += asteroid[i].dx;
        asteroid[i].y += asteroid[i].dy;

            if (asteroid[i].x > SCREEN_WIDTH) {
                asteroid[i].x = -OBJ_SIZE; // Reappear on the far left
            } else if (asteroid[i].x < -OBJ_SIZE) {
                asteroid[i].x = SCREEN_WIDTH; // Reappear on the far right
            }

            if (asteroid[i].y > SCREEN_HEIGHT) {
                asteroid[i].y = -OBJ_SIZE;
            } else if (asteroid[i].y < -OBJ_SIZE) {
                asteroid[i].y = SCREEN_HEIGHT;
            }

    }
}

void draw_asteroids(Asteroid *asteroid, int count, ALLEGRO_BITMAP *image) {
    ALLEGRO_TRANSFORM trans;
    for (int i = 0; i < count; i++) {
        if (asteroid[i].active) {
            al_identity_transform(&trans);

            al_rotate_transform(&trans, asteroid[i].heading);
            al_scale_transform(&trans, asteroid[i].scale, asteroid[i].scale);
            al_translate_transform(&trans, asteroid[i].x, asteroid[i].y);

            al_use_transform(&trans);

            al_draw_bitmap(image, -al_get_bitmap_width(image) / 2.0, -al_get_bitmap_height(image) / 2.0,0);
        }

        al_identity_transform(&trans);
        al_use_transform(&trans);
    }
}