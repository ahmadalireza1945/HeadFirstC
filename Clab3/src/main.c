#include <stdio.h>
#include "../include/spaceship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


int main(int argc, char *argv[]) {
    if (!al_init()) {
        fprintf (stderr, "allegro couldn't initialize\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf (stderr, "allegro couldn't initialize\n");
        return -1;
    }


    if (!al_init_image_addon()) {
        fprintf(stderr, "allegro couldn't initialize image addon\n");
        return -1;
    }
    //variable for display
    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;
    const int OBJ_SIZE = 32;

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display) {
        fprintf (stderr, "allegro couldn't initialize\n");
        return -1;
    }

    ALLEGRO_BITMAP *spaceship_image = al_load_bitmap("/home/learn/LearnC/HeadFirstC/Clab3/asset/images/spaceship.png");
    ALLEGRO_BITMAP *background_image = al_load_bitmap("/home/learn/LearnC/HeadFirstC/Clab3/asset/images/jokowi.png");

    if (!spaceship_image) {
        fprintf (stderr, "allegro couldn't load spaceship\n");
        al_destroy_display(display);
        return -1;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    al_set_window_title(display, "Space Ship");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    struct Spaceship spaceship;
    spaceship.x = (float)SCREEN_WIDTH / 2;
    spaceship.y = (float)SCREEN_HEIGHT / 2;

    bool running = true;
    bool redraw = true;

    al_start_timer(timer);

    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;

            ALLEGRO_KEYBOARD_STATE key_state;
            movement(&key_state, &spaceship);

        }else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }


        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0)); // Background hitam


            al_draw_bitmap(background_image, 0 ,0, 0);

            // tempat space ship
            al_draw_bitmap(spaceship_image, spaceship.x, spaceship.y, 0);

            al_flip_display();
        }
    }
    al_destroy_bitmap(spaceship_image);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}
