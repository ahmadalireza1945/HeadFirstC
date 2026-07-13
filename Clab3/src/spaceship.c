#include "../include/spaceship.h"

void movement(ALLEGRO_KEYBOARD_STATE *key_state, Spaceship *spaceship) {
    al_get_keyboard_state(key_state);

    if (al_key_down(key_state, ALLEGRO_KEY_LEFT)) {
        spaceship->heading -= 0.05; // Putar berlawanan arah jarum jam
    }
    if (al_key_down(key_state, ALLEGRO_KEY_RIGHT)) {
        spaceship->heading += 0.05; // Putar searah jarum jam
    }

    // 2. Tombol Atas untuk bergerak maju searah moncong pesawat
    if (al_key_down(key_state, ALLEGRO_KEY_UP)) {
        // cosf() menentukan pergerakan horizontal berdasarkan sudut
        // sinf() menentukan pergerakan vertikal berdasarkan sudut
        spaceship->x += cosf(spaceship->heading) * spaceship->speed;
        spaceship->y += sinf(spaceship->heading) * spaceship->speed;
    }

    // (Opsional) Tombol Bawah untuk bergerak mundur
    if (al_key_down(key_state, ALLEGRO_KEY_DOWN)) {
        spaceship->x -= cosf(spaceship->heading) * (spaceship->speed * 0.5);
        spaceship->y -= sinf(spaceship->heading) * (spaceship->speed * 0.5);
    }
}

//logika untuk lopp space
void wall_warp(Spaceship *spaceship, int SCREEN_WIDTH, int SCREEN_HEIGHT, int OBJ_SIZE) {
    if (spaceship->x > SCREEN_WIDTH) {
        spaceship->x = -OBJ_SIZE; // Reappear on the far left
    } else if (spaceship->x < -OBJ_SIZE) {
        spaceship->x = SCREEN_WIDTH; // Reappear on the far right
    }

    if (spaceship->y > SCREEN_HEIGHT) {
        spaceship->y = -OBJ_SIZE;
    } else if (spaceship->y < -OBJ_SIZE) {
        spaceship->y = SCREEN_HEIGHT;
    }
}