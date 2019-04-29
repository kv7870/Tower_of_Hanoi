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

	titleScreen(numDisc, choice, move, A, C, B, event_queue, font);

	//initTower(numDisc);

	

	switch (choice) {
	case 1:
		levelFourMinus(numDisc, choice, move, A, C, B, event_queue, font);
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

void levelFourMinus(int& numDisc, int& choice, int& move, Peg& A, Peg& C, Peg& B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, move, false, A, C, B, event_queue, font);

	move = 0;
	choice = 0; 

	al_draw_filled_rounded_rectangle(480, 10, 560, 50, 10, 10, al_map_rgb(255, 255, 255));
	al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), 485, 15, 0, "Menu");
	al_flip_display();
	system("pause");
	C.printStack();
	cout << endl;



	al_clear_to_color(al_map_rgb(0, 0, 0));
	/*for (Node* curr = C.getHead(); curr; curr = curr->next) {
		C.pop(1);
		//cout << "ID: " << A.getHead()->ID << endl;
	}
	A.printStack();

	titleScreen(numDisc, choice, move, A, C, B, event_queue, font);*/
}

void levelFour(int& numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	draw(numDisc, move, false, A, C, B, event_queue, font);
	float mx = 0, my = 0;
	bool done = false;

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 255, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	bool refresh = true;
	bool initial = true; 


	while (!done) {

		if (refresh) {

			draw(numDisc, move, false, A, C, B, event_queue, font);

			al_draw_textf(font[REGULAR], white, 5, 5, 0, "Discs: %d", numDisc);
			al_draw_filled_rectangle(95, 10, 125, 40, white);
			al_draw_filled_rectangle(135, 10, 165, 40, white);

			al_draw_filled_triangle(100, 15, 120, 15, 110, 35, red);
			al_draw_filled_triangle(140, 35, 160, 35, 150, 15, green);

			al_draw_filled_rounded_rectangle(430, 10, 520, 50, 10, 10, white);
			al_draw_text(font[REGULAR], black, 443, 15, 0, "Menu");

			al_draw_filled_rounded_rectangle(540, 10, 630, 50, 10, 10, white);		
			al_draw_text(font[REGULAR], black, 553, 15, 0, "Solve");


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

						A.pop(initial);

						for (Node* curr = A.getHead()->next; curr; curr = curr->next) {
							(curr->ID)--;
						}
						refresh = true;
					}

				}
				else if (mx >= 135 && mx <= 165) {
					if (numDisc < MAX_DISC) {
						numDisc++;
						Node* newnode = new Node;
						newnode->x = A.cx;
						newnode->y = A.topY;
						newnode->radius = A.getHead()->radius - 10;
						newnode->colour = (A.size % 2) ? yellow : blue;
						newnode->ID = 1;

						for (Node* curr = A.getHead()->next; curr; curr=curr->next) {
							(curr->ID)++;
						}

						A.push(newnode);
						refresh = true;
					}
				}
			}

			if ((mx >= 540 && mx <= 630) && (my >= 10 && my <= 50)) {
				done = true;
				al_draw_filled_rounded_rectangle(540, 10, 630, 50, 10, 10, al_map_rgb(128,128,128));
				al_draw_text(font[REGULAR], black, 550, 15, 0, "Solve");
			}
			
		}


	}
	
	hanoi(numDisc, move, true, A, C, B, event_queue, font);
}

void levelFourPlus(int& numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, move, false, A, C, B, event_queue, font);
}

