//initialization.cpp
#include "stdafx.h"
#include "header.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
const int SCREEN_W = 640;
const int SCREEN_H = 480;

//initialize Allegro 
void initAllegro(ALLEGRO_DISPLAY** display, ALLEGRO_EVENT_QUEUE** event_queue,
	ALLEGRO_FONT** font) {

	//initialization 
	if (!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not initialize Allegro", NULL, NULL);


	//install
	al_install_keyboard();
	al_install_mouse();

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//create 
	*display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create display", NULL, NULL);

	*event_queue = al_create_event_queue();

	font[BOLD] = al_load_ttf_font("OpenSans-Bold.ttf", 28, 0);
	font[REGULAR] = al_load_ttf_font("OpenSans-Regular.ttf", 24, 0);

	//register
	al_register_event_source(*event_queue, al_get_display_event_source(*display));
	al_register_event_source(*event_queue, al_get_keyboard_event_source());
	al_register_event_source(*event_queue, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
}

