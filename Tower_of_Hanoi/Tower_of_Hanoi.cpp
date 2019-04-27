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
const int numPeg = 3; 
const int pegHeight = 100; 


int main() {
	int numDisc = 5;
	Peg A('A', numDisc);
	Peg B('B');
	Peg C('C');
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	initAllegro(&display, &timer, &event_queue);

	//initTower(numDisc);

	draw(numDisc, A, C, B);
	
	hanoi(numDisc, A, C, B, event_queue);

	A.printStack();
	cout << endl;

	B.printStack();
	cout << endl;

	C.printStack(); 
	cout << endl;



	return 0;
}

void hanoi(int n, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE *event_queue)
{
	if (n > 0) {
		hanoi(n - 1, s, i, d, event_queue);
		Move(n, s, d);
		draw(n, s, d, i); 
		hanoi(n - 1, i, d, s, event_queue);
	}
}



//draw pegs and all discs in current position
void draw(int numDisc, Peg s, Peg d, Peg i) {
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	al_clear_to_color(black); 

	//draw pegs
	for (int i = 0, x = 100, y = 425; i < 3; i++, x += 220) {
		al_draw_filled_rectangle(x, y, x + 5, y - 185, white);
		al_draw_filled_rectangle((x + 2.5) - 95, y - 5, (x + 2.5) + 95, y, white);
	}
	
	al_flip_display();

	//draw discs
	if (s.getHead() != nullptr) {
		for (Node* curr = s.getHead(); curr; curr = curr->next) {
			cout << "HI";
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
			al_flip_display(); 
		}
	}
		
	if (d.getHead() != nullptr) {
		for (Node* curr = d.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
	}

	if (i.getHead() != nullptr) {
		for (Node* curr = i.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
	}

	
	al_flip_display(); 
}



void Move(int n, Peg& s, Peg& d) {
	cout << "Moving disk " << n << " from peg " << s.pegID <<
		" to peg " << d.pegID << endl;

	d.push(s.pop()) ;
}

void initTower(int numDisc) {
	float x1 = 20, y1 = 420, x2 = 120, y2 = 450;
	//al_draw_filled_ellipse(100, 100, 50, 10, al_map_rgb(255, 0, 0));
	//al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
	//y2 = y1;
	//y1 = y1 - (y2 - y1);
	//al_draw_filled_rectangle(x1 + 15, y1, x2 - 15, y2, al_map_rgb(0, 0, 255));
	//al_draw_filled_rectangle(x1+30, y1)
	
	//draw pegs

	for (int i = 0, x = 100, y = 425; i < 3; i++, x += 220) {
		al_draw_filled_rectangle(x, y, x + 5, y-185, al_map_rgb(255, 255, 255));
		al_draw_filled_rectangle((x + 2.5) - 95, y-5, (x + 2.5) + 95, y, al_map_rgb(255, 255, 255));
	}

	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);

	
	for (int i = 0, x = 102.5, y = 400, r = 90; i < numDisc; i++, y -= 20, r -= 10) {
		ALLEGRO_COLOR colour = (i % 2) ? yellow : blue;
		al_draw_filled_rounded_rectangle(x - r, y, x + r, y + 20, 10, 10, colour);
	}

	/*for (int i = 0, x = 102.5, y = 400, r = 90; i < numDisc; i++, y -= 20, r-=10) {
		ALLEGRO_COLOR colour = (i % 2) ?  yellow : blue;
		al_draw_filled_rounded_rectangle(x - r, y, x + r, y + 20, 10, 10, colour);
	}

	//al_draw_filled_rectangle(120 + 2.5 - 65, 420, 120 + 2.5 + 65, 400, al_map_rgb(0, 0, 255));
	/*
	al_draw_filled_rectangle(130, 425, 140, 250, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(310, 425, 320, 250, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(490, 425, 500, 250, al_map_rgb(255, 255, 255));
	*/
	while (1)
		al_flip_display();


}


void initAllegro(ALLEGRO_DISPLAY * *display, ALLEGRO_TIMER * *timer, ALLEGRO_EVENT_QUEUE * *event_queue) {
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
