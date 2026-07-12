#include "../include/spaceship.h"

void movement(ALLEGRO_KEYBOARD_STATE *key_state, Spaceship *spaceship) {

    al_get_keyboard_state(key_state);
    if (al_key_down(key_state, ALLEGRO_KEY_UP))  spaceship->y -= 5;
    if (al_key_down(key_state, ALLEGRO_KEY_DOWN)) spaceship->y += 5;
    if (al_key_down(key_state, ALLEGRO_KEY_LEFT)) spaceship->x -= 5;
    if (al_key_down(key_state, ALLEGRO_KEY_RIGHT)) spaceship->x += 5;

}