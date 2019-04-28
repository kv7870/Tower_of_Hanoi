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
const int MAX_DISC = 8; 


int main() {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_FONT* font[2] = { NULL };
	initAllegro(&display, &timer, &event_queue, font);

	int numDisc = 5;
	int choice; 
	int move = 0; 

	Peg A('A', 102.5, numDisc);
	Peg B('B', 322.5);
	Peg C('C', 542.5);



	//initTower(numDisc);

	titleScreen(numDisc, choice, move, A, C, B, font, event_queue); 

	switch (choice) {
		case 1:
			levelFourMinus(numDisc, move, A, C, B, event_queue, font);
			break;
		case 2:
			levelFour(numDisc, move, A, C, B, event_queue, font);
			break;
		case 3:
			levelFourPlus(numDisc, move, A, C, B, event_queue, font);
			break; 
		default:
			cout << "Invalid choice";
	}

	//hanoi(numDisc, A, C, B, event_queue);

#if 0
	A.printStack();
	cout << endl;

	B.printStack();
	cout << endl;

	C.printStack(); 
	cout << endl;
#endif

	return 0;
}

void levelFourMinus(int numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, move, A, C, B, event_queue, font);
}

void levelFour(int &numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	draw(numDisc, move, A, C, B, font);
	float mx = 0, my = 0;
	bool done = false;

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	bool refresh = true; 


	while (!done) {

		if (refresh) {
			al_draw_textf(font[REGULAR], white, 5, 5, 0, "Discs: %d", numDisc);
			al_draw_filled_rectangle(95, 10, 125, 40, white);
			al_draw_filled_rectangle(135, 10, 165, 40, white);

			al_draw_filled_triangle(100, 15, 120, 15, 110, 35, red);
			al_draw_filled_triangle(140, 35, 160, 35, 150, 15, green);

			draw(numDisc, move, A, C, B, font);
			al_flip_display(); 
		

	
			refresh = false;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mx = ev.mouse.x;
				my = ev.mouse.y;
			}

			if (my >= 10 && my <= 40) {
				if (mx >= 95 && mx <= 125) {
					if (numDisc > 1) {
						numDisc--;
						refresh = true;
					}

				}
				else if (mx >= 135 && mx <= 165) {
					if (numDisc < MAX_DISC) {
						numDisc++;
						refresh = true;
					}
				}
			}
		}

		
	}
		
	hanoi(numDisc, move, A, C, B, event_queue, font);
}

void levelFourPlus(int &numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, move, A, C, B, event_queue, font);
}



void hanoi(int n, int &move, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT ** font)
{
	if (n > 0) {
		hanoi(n - 1, move, s, i, d, event_queue, font);
		Move(n, move, s, d);
		draw(n, move, s, d, i, font); 
		hanoi(n - 1, move, i, d, s, event_queue, font);
	}
}


void Move(int n, int &move, Peg& s, Peg& d) {
	cout << "Moving disk " << n << " from peg " << s.pegID <<
		" to peg " << d.pegID << endl;
	Node* dHead = d.getHead();
	Node* sHead = s.getHead(); 

	sHead->x = d.cx; 
	sHead->y = d.topY; 
	move++; 
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
	ALLEGRO_COLOR blue = al_map_rgb(0, 255, 255);

	
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
