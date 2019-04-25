// Tower_of_Hanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "header.h"
#include "class.h"
using namespace std;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int FPS = 60;



int main() {
	int numDisc = 3;
	Peg A('A', numDisc);
	Peg B('B');
	Peg C('C');
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_TIMER * timer = NULL;
	ALLEGRO_EVENT_QUEUE * event_queue = NULL;

	initAllegro(&display, &timer, &event_queue);

	//initTower(numDisc);

	A.printStack(); 
	hanoi(numDisc, A, C, B); 

	return 0; 
}

void hanoi(int n, Peg s, Peg d, Peg i)
{
	if (n > 0) {
		hanoi(n - 1, s, i, d);
		move(n, s, d);
		hanoi(n - 1, i, d, s);
	}
}

void move(int n, Peg s, Peg d) {
	cout << "Move disk " << n << " from rod " << s.ID <<
		" to rod " << d.ID << endl;
	cout << "n: " << n << endl;
	int temp = (s.getHead())->data; 
	s.pop();
	d.push(temp);
}

void initTower(int numDisc) {
	float x1 = 20, y1 = 420, x2 = 120, y2 = 450;
	//al_draw_filled_ellipse(100, 100, 50, 10, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
	y2 = y1;
	y1 = y1 - (y2 - y1);
	al_draw_filled_rectangle(x1 + 15, y1, x2 - 15, y2, al_map_rgb(0, 0, 255));
	//al_draw_filled_rectangle(x1+30, y1)
	while (1)
		al_flip_display();


}


void initAllegro(ALLEGRO_DISPLAY ** display, ALLEGRO_TIMER ** timer, ALLEGRO_EVENT_QUEUE ** event_queue) {
	al_init();

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1000);
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	*display = al_create_display(SCREEN_W, SCREEN_H);
	*timer = al_create_timer(1.0 / FPS);
	*event_queue = al_create_event_queue();
}


