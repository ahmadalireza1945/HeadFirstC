#include "../include/blast.h"


void fire_blast(Spaceship *spaceship, Blast *blast, int maxBlasts) {
        for (int i = 0 ; i < maxBlasts; i++) {
            if (!blast[i].active) {
                blast[i].speed = 8.0;


                blast[i].x = spaceship->x + cos(spaceship->heading) * (spaceship->radius + 5);
                blast[i].y = spaceship->y + sin(spaceship->heading) * (spaceship->radius + 5);


                blast[i].dx = cos(spaceship->heading) * blast[i].speed;
                blast[i].dy = sin(spaceship->heading) * blast[i].speed;

                // blast
                blast[i].active = 1;
                break;
            }
        }
}

void update_blast(Blast *blast, int maxBlasts) {
    for (int i = 0 ; i < maxBlasts ; i++) {
        if (blast[i].active) {
            blast[i].x += blast[i].dx;
            blast[i].y += blast[i].dy;

            if (blast[i].x < 0 || blast[i].x > SCREEN_WIDTH || blast[i].y < 0 || blast[i].y > SCREEN_HEIGHT) {
                blast[i].active = false;
            }
        }
    }
}


void draw_blast(ALLEGRO_DISPLAY *display, Blast *blast, int maxBlasts) {
    for (int i = 0 ; i < maxBlasts ; i++) {
        if (blast[i].active) {
            al_draw_filled_circle(blast[i].x, blast[i].y, 3, blast[i].color);
        }
    }
}