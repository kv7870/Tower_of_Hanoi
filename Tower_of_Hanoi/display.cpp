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

void titleScreen(int &numDisc, int &choice, int &move, Peg A, Peg C, Peg B, ALLEGRO_FONT ** font,
	ALLEGRO_EVENT_QUEUE * event_queue) {
	ALLEGRO_COLOR bblue = al_map_rgb(137, 207, 240);
	ALLEGRO_COLOR cyan = al_map_rgb(0, 255, 255);
	ALLEGRO_COLOR white= al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR grey = al_map_rgb(128, 128, 128);
	bool done = false;
	float mx = 0, my = 0; 
	draw(numDisc, move, A, C, B, font);
	
	al_draw_filled_rounded_rectangle(A.cx - 50, 90, A.cx + 50, 140, 10, 10, white);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), A.cx-30, 100, 0, "Level 4-");

	al_draw_filled_rounded_rectangle(B.cx - 50, 90, B.cx + 50, 140, 10, 10, white);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), B.cx - 30, 100, 0, "Level 4");

	al_draw_filled_rounded_rectangle(C.cx - 50, 90, C.cx + 50, 140, 10, 10, white);
	al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), C.cx - 30, 100, 0, "Level 4+");


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

			if ((mx >= A.cx - 50 && mx <= A.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 1;
				numDisc = 5;
				al_draw_filled_rounded_rectangle(A.cx - 50, 90, A.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), A.cx - 30, 100, 0, "Level 4-");
				al_flip_display();
				al_rest(0.2);
			}

			else if ((mx >= B.cx - 50 && mx <= B.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 2;
				numDisc = 5;
				al_draw_filled_rounded_rectangle(B.cx - 50, 90, B.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), B.cx - 30, 100, 0, "Level 4");
				al_flip_display();
				al_rest(0.2);
			}

			else if ((mx >= C.cx - 50 && mx <= C.cx + 50) && (my >= 90 && my <= 140)) {
				done = true;
				choice = 3;
				al_draw_filled_rounded_rectangle(C.cx - 50, 90, C.cx + 50, 140, 10, 10, grey);
				al_draw_text(font[BOLD], al_map_rgb(0, 0, 0), C.cx - 30, 100, 0, "Level 4+");
				al_flip_display();
				al_rest(0.2);
			}

		}


		
	}

}



//draw pegs and all discs in current position
void draw(int numDisc, int &move, Peg s, Peg d, Peg i, ALLEGRO_FONT ** font) {
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	al_clear_to_color(black);

	//draw pegs
	for (int i = 0, x = 100, y = 425; i < 3; i++, x += 220) {
		al_draw_filled_rectangle(x, y, x + 5, y - 185, white);
		al_draw_filled_rectangle((x + 2.5) - 95, y - 5, (x + 2.5) + 95, y, white);
	}



	if (move > 0)
		al_draw_textf(font[BOLD], white, 310, 10, 0, "Moves: %d", move);


	//draw discs
	if (s.getHead() != NULL) {
		int i = 0;
		for (Node* curr = s.getHead(); curr != NULL; curr = curr->next) {
			cout << curr->ID << endl;

			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
		}
		cout << endl; 
	}

	if (d.getHead() != NULL) {
		for (Node* curr = d.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);

	}

	if (i.getHead() != NULL) {
		for (Node* curr = i.getHead(); curr; curr = curr->next)
			al_draw_filled_rounded_rectangle(curr->x - curr->radius, curr->y, curr->x + curr->radius,
				curr->y + 20, 10, 10, curr->colour);
	}

	//al_flip_display();
	//al_rest(0.1);

} 