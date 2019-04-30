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
	int numMove = 0;

	Peg A('A', 102.5, numDisc);
	Peg B('B', 322.5);
	Peg C('C', 542.5);

	titleScreen(numDisc, choice, numMove, A, C, B, event_queue, font);

	//initTower(numDisc);

	

	switch (choice) {
	case 1:
		levelFourMinus(numDisc, choice, numMove, A, C, B, event_queue, font);
		break;
	case 2:
		levelFour(numDisc, numMove, A, C, B, event_queue, font);
		break;
	case 3:
		levelFourPlus(numDisc, numMove, A, C, B, event_queue, font);
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

void reset(int &numDisc, int &choice, int &numMove, Peg& A, Peg& C) {
	numDisc = 5;
	choice = 0;
	numMove = 0; 

	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 255, 255);

	for (Node* curr = C.getHead(); curr; curr = curr->next)
		C.pop(0);

	float x = 102.5, y = 400, r = 90;
	for (int i = 0; i < numDisc; i++) {
		Node* temp = new Node;
		ALLEGRO_COLOR colour = (i % 2) ? yellow : blue;
		temp->ID = numDisc - i;
		temp->x = x;
		temp->y = y;
		temp->radius = r;
		temp->colour = colour;

		A.push(temp);

		y -= 20;
		r -= 10;
	}
}

void levelFourMinus(int& numDisc, int& choice, int& numMove, Peg& A, Peg& C, Peg& B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, numMove, false, A, C, B, event_queue, font);

	

	al_draw_filled_rounded_rectangle(480, 10, 560, 50, 10, 10, al_map_rgb(255, 255, 255));
	al_draw_text(font[REGULAR], al_map_rgb(0, 0, 0), 485, 15, 0, "Menu");
	al_flip_display();
	system("pause");
	
	reset(numDisc, choice, numMove, A, C);
	C.printStack();
	cout << endl;



	al_clear_to_color(al_map_rgb(0, 0, 0));

	titleScreen(numDisc, choice, numMove, A, C, B, event_queue, font);
}

void levelFour(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	draw(numDisc, numMove, false, A, C, B, event_queue, font);
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

			draw(numDisc, numMove, false, A, C, B, event_queue, font);

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
	
	hanoi(numDisc, numMove, true, A, C, B, event_queue, font);
}

void levelFourPlus(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	bool done = false;
	bool refresh = true; 
	float mx = 0, my = 0;
	bool selected = false; 
	Peg* s = NULL, * d = NULL; 

	while (!done) {
		draw(numDisc, numMove, false, A, C, B, event_queue, font); draw(numDisc, numMove, false, A, C, B, event_queue, font);

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
				cout << "HI";
			}

			getSelectedDisc(mx, my, s, A, C, B);

			if (s != NULL) {
				al_draw_filled_rounded_rectangle(s->getHead()->x - s->getHead()->radius, s->getHead()->y, s->getHead()->x + s->getHead()->radius,
					s->getHead()->y + 20, 10, 10, al_map_rgb(0, 255, 0));
				refresh = true;
				selected = true;
			}
			else {
				mx = 0;
				my = 0;
			}
		}

		if (selected) { 
			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				if (ev.mouse.button & 1) {  
					mx = ev.mouse.x;
					my = ev.mouse.y;

					if (chkValidMove(mx, my, A, C, B, s, d)) {
						Move(numDisc, numMove, *s, *d);
						//cout << "HI";
					}
				}
		}

		if (refresh) { 
			al_flip_display(); 
			refresh = false; 
			s = NULL; 
			d = NULL; 
		}
	}
}

void getSelectedDisc(float mx, float my, Peg *s, Peg A, Peg C, Peg B) {
	if (mx >= A.cx - A.getHead()->radius && mx <= A.cx + A.getHead()->radius) {
		if (my <= A.getHead()->y + 20 && my >= A.getHead()->y)
			s = &A; 
	}

	else if (mx >= B.cx - B.getHead()->radius && mx <= B.cx + B.getHead()->radius) {
		if (my <= B.getHead()->y + 20 && my >= B.getHead()->y)
			s = &B;
	}

	else if (mx >= C.cx - C.getHead()->radius && mx <= C.cx + C.getHead()->radius) {
		if (my <= C.getHead()->y + 20 && my >= C.getHead()->y)
			s = &C;
	}
}


bool chkValidMove(float mx, float my, Peg A, Peg C, Peg B, Peg *s, Peg *d) {
	/*for (int i = 0, x = 100, y = 425; i < 3; i++, x += 220) {
		al_draw_filled_rectangle(x, y, x + 5, y - 185, white);
		al_draw_filled_rectangle((x + 2.5) - 95, y - 5, (x + 2.5) + 95, y, white);*/

		if (my <= 425 && my >= 240) {                    
			//not same peg                   
			if (mx<s->cx - 2.5 || mx>s->cx + 2.5) {  

				if (mx >= 100 && mx <= 105) {
					if (A.getHead()->ID > s->getHead()->ID) {  
						d = &A;    
						return true; 
					}
				}

				else if (mx >= 320 && mx <= 325) { 
					if (B.getHead()->ID > s->getHead()->ID) { 
						d = &B;     
						return true;  
					}
				}

				else if (mx >= 540 && mx <= 545) {   
					if (C.getHead()->ID > s->getHead()->ID) {  
						d = &C;                
						return true;     
					}
				}
			}

		}

		return false; 
}

