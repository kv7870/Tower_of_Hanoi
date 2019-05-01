#include "stdafx.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
#include "class.h"
using namespace std;

//level 4+ requirement: user plays game 
void levelFourPlus(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	bool done = false;
	bool refresh = true;
	float mx = 0, my = 0;
	bool selected = false;
	Peg* s = NULL, * d = NULL;

	//let user adjust the # of discs 
	changeNumDisc(numDisc, numMove, A, C, B, event_queue, font);

	while (!done) {
		if (refresh) {
			draw(numDisc, numMove, false, A, C, B, event_queue, font);
			al_draw_text(font[BOLD], al_map_rgb(255, 255, 255), 105, 100, 0, "Click the disk you wish to move");
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mx = ev.mouse.x;
				my = ev.mouse.y;

				if (selected) {
					if (chkValidMove(mx, my, A, C, B, s, &d)) {
						//cout << "Source: " << s->pegID << endl << "Destination: " << d->pegID << endl; 
						//system("pause"); 
						Move(numDisc, numMove, *s, *d);
						d->printStack(); 
						refresh = true; 
						selected = false;
						s = NULL;
						d = NULL;
						continue;
					}
				}

				if (selectDisc(mx, my, &s, A, C, B)) {
					draw(numDisc, numMove, false, A, C, B, event_queue, font);

					al_draw_filled_rounded_rectangle(s->getHead()->x - s->getHead()->radius, s->getHead()->y,
						s->getHead()->x + s->getHead()->radius, s->getHead()->y + 20, 10, 10, al_map_rgb(0, 255, 0));

					drawOptions(s, A, C, B, font);
					refresh = true;
					selected = true;
				}
				else {
					mx = 0;
					my = 0;
				}
			}
		}

		if (refresh) {
			al_flip_display();
			refresh = false;
		}
		
		if (chkSolved(numDisc, C))
			done = true; 
	}

	//wait for user to close window
	finishScreen(event_queue, font);
}

bool chkSolved(int numDisc, Peg& C) {
	if (C.getHead()) {
		if (C.getHead()->ID == numDisc)
			return true;
	}
	return false; 
}

void drawOptions(Peg* s, Peg &A, Peg &C, Peg &B, ALLEGRO_FONT** font) {
	if (s->pegID != A.pegID) {
		if (!(A.getHead()) || A.getHead()->radius > s->getHead()->radius) {
			al_draw_filled_rounded_rectangle(A.cx - 50, 100, A.cx + 50, 150, 10, 10, al_map_rgb(0, 255, 0));
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), A.cx - 30, 95, 0, "Move");
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), A.cx - 25, 120, 0, "here");
		}
	}

	if (s->pegID != B.pegID) {
		if (!(B.getHead()) || B.getHead()->radius > s->getHead()->radius) {
			al_draw_filled_rounded_rectangle(B.cx - 50, 100, B.cx + 50, 150, 10, 10, al_map_rgb(0, 255, 0));
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), B.cx - 30, 95, 0, "Move");
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), B.cx - 25, 120, 0, "here");
		}
	}

	if (s->pegID != C.pegID) {
		if (!(C.getHead()) || C.getHead()->radius > s->getHead()->radius) {
			al_draw_filled_rounded_rectangle(C.cx - 50, 100, C.cx + 50, 150, 10, 10, al_map_rgb(0, 255, 0));
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), C.cx - 30, 95, 0, "Move");
			al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), C.cx - 25, 120, 0, "here");
		}
	}
}

bool selectDisc(float mx, float my, Peg** s, Peg& A, Peg& C, Peg& B) {
	if (A.getHead())
		if (mx >= A.cx - A.getHead()->radius && mx <= A.cx + A.getHead()->radius) {
			if (my <= A.getHead()->y + 20 && my >= A.getHead()->y) {
				*s = &A;
				return true;
			}
		}

	if (B.getHead()) {
		if (mx >= B.cx - B.getHead()->radius && mx <= B.cx + B.getHead()->radius) {
			if (my <= B.getHead()->y + 20 && my >= B.getHead()->y)
				if (B.getHead()) {
					*s = &B;
					return true;
				}
		}
	}

	if (C.getHead()) {
		if (mx >= C.cx - C.getHead()->radius && mx <= C.cx + C.getHead()->radius) {
			if (my <= C.getHead()->y + 20 && my >= C.getHead()->y)
				if (C.getHead()) {
					*s = &C;
					return true;
				}
		}
	}

	return false;
}


bool chkValidMove(float mx, float my, Peg &A, Peg &C, Peg &B, Peg* s, Peg** d) {

	if (my <= 150 && my >= 100) {
		if (mx >= A.cx - 50 && mx <= A.cx + 50) {
			//verify that destination != source   
			if (s->pegID != A.pegID) {
				if (A.getHead() == NULL || A.getHead()->ID > s->getHead()->ID) {
					*d = &A;
					return true;
				}
			}
		}

		else if (mx >= B.cx - 50 && mx <= B.cx + 50) {
			if (s->pegID != B.pegID) {
				if (B.getHead() == NULL || B.getHead()->ID > s->getHead()->ID) {
					*d = &B;
					return true;
				}
			}
		}

		else if (mx >= C.cx - 50 && mx <= C.cx + 50) {
			if (s->pegID != C.pegID) {
				if (C.getHead() == NULL || C.getHead()->ID > s->getHead()->ID) {
					*d = &C;
					return true;
				}
			}

		}
	}

	return false;
}



