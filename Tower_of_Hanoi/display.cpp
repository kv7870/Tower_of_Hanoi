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

//title screen with 3 options displayed  
void titleScreen(int &numDisc, int &choice, int &move, Peg A, Peg C, Peg B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT ** font) {
	//colours 
	ALLEGRO_COLOR white= al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR grey = al_map_rgb(128, 128, 128);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR cyan = al_map_rgb(0, 255, 255);
	ALLEGRO_COLOR magenta = al_map_rgb(255, 0, 255);

	bool done = false;
	float mx = 0, my = 0; 
	draw(numDisc, move, false, A, C, B, event_queue, font);
	
	al_draw_filled_rounded_rectangle(A.cx - 50, 90, A.cx + 50, 140, 10, 10, cyan);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), A.cx-35, 95, 0, "Lvl 4-");

	al_draw_filled_rounded_rectangle(B.cx - 50, 90, B.cx + 50, 140, 10, 10, magenta);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), B.cx - 35, 95, 0, "Lvl 4");

	al_draw_filled_rounded_rectangle(C.cx - 50, 90, C.cx + 50, 140, 10, 10, yellow);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), C.cx - 35, 95, 0, "Lvl 4+");

	//wait for user to select mode 
	while (!done) {
		al_flip_display();
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
			exit(0);
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mx = ev.mouse.x;
				my = ev.mouse.y;
			}

			//user selects level 4- version 
			if ((mx >= A.cx - 50 && mx <= A.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 1;
				numDisc = 5;
				al_draw_filled_rounded_rectangle(A.cx - 50, 90, A.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), A.cx - 30, 100, 0, "Lvl 4-");
				al_flip_display();
				al_rest(0.1);
			}

			//user selects level 4 version 
			else if ((mx >= B.cx - 50 && mx <= B.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 2;
				numDisc = 5;
				al_draw_filled_rounded_rectangle(B.cx - 50, 90, B.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), B.cx - 30, 100, 0, "Lvl 4");
				al_flip_display();
				al_rest(0.1);
			}

			//user selects level 4+ version 
			else if ((mx >= C.cx - 50 && mx <= C.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 3;
				al_draw_filled_rounded_rectangle(C.cx - 50, 90, C.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), C.cx - 30, 100, 0, "Lvl 4+");
				al_flip_display();
				al_rest(0.1);
			}
		}
	}
}


//show instructions for level 4 requirement 
void walkthrough(int n, Peg s, Peg d, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT** font) {
	bool done = false;
	float mx = 0, my = 0;
	
	//display instructions & next button 
	al_draw_textf(font[REGULAR], al_map_rgb(255,255,255), 150, 75, 0, "Move disk %d from peg %c to peg %C", n, s.pegID, d.pegID);
	al_draw_filled_rounded_rectangle(270, 125, 370, 175, 10, 10, al_map_rgb(255, 255, 255));
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), 285, 130, 0, "Next");

	//wait for user to click next 
	while (!done) {

		al_flip_display();

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mx = ev.mouse.x;
				my = ev.mouse.y;
			}
			//user clicks next
			if (mx >= 270 && mx <= 370)
				if (my >= 125 && my <= 175) {
					done = true;
					al_draw_filled_rounded_rectangle(270, 125, 370, 175, 10, 10, al_map_rgb(128, 128, 128));
					al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), 285, 130, 0, "Next");
				}
		}
	}
}


//draw pegs and all discs in their current position
void draw(int numDisc, int &numMove, bool lvlFour, Peg s, Peg d, Peg i, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT ** font) {
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	//clear screen 
	al_clear_to_color(black);

	//draw pegs
	for (int i = 0, x = 100, y = 425; i < 3; i++, x += 220) {
		al_draw_filled_rectangle(x, y, x + 5, y - 185, white);
		al_draw_filled_rectangle((x + 2.5) - 95, y - 5, (x + 2.5) + 95, y, white);
	}

	//display # of moves
	al_draw_textf(font[BOLD], white, 270, 5, 0, "Moves: %d", numMove);

	//draw discs on source peg
	if (s.getHead() != NULL) {
		int i = 0;
		for (Node* curr = s.getHead(); curr != NULL; curr = curr->next) {
			cout << curr->ID << endl;

			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
		}
		cout << endl; 
	}

	//draw discs on destination peg
	if (d.getHead() != NULL) {
		for (Node* curr = d.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);

	}

	//draw discs on intermediate peg
	if (i.getHead() != NULL) {
		for (Node* curr = i.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
	}

	//show walkthrough instructions if level 4 version is running
	if (lvlFour)
		walkthrough(numDisc, s, d, event_queue, font);

	//al_flip_display();
	//al_rest(0.1);
} 