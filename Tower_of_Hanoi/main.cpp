//main.cpp
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
	initAllegro(&display, &event_queue, font);

	int numDisc = 5;
	//level 4-, 4, 4+ options 
	int choice;
	//track number of moves
	int numMove = 0;

	Peg A('A', 102.5, numDisc);
	Peg B('B', 322.5);
	Peg C('C', 542.5);

	//display options 
	titleScreen(numDisc, choice, numMove, A, C, B, event_queue, font);

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
	return 0;
}


//level 4 minus requirement: computer solves in fewest moves using recursion 
void levelFourMinus(int& numDisc, int& choice, int& numMove, Peg& A, Peg& C, Peg& B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {
	hanoi(numDisc, numMove, false, A, C, B, event_queue, font);

	//wait for user to close window
	finishScreen(event_queue, font);
}

//level 4 requirement: clickable walkthrough using recursion 
void levelFour(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue,
	ALLEGRO_FONT** font) {

	float mx = 0, my = 0;
	bool done = false;

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR cyan = al_map_rgb(0, 255, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	bool refresh = true;
	bool initial = true;

	cout << "NUMDISC: " << numDisc << endl;

	changeNumDisc(numDisc, numMove, A, C, B, event_queue, font);
	
	//solve recursively but one step at a time 
	hanoi(numDisc, numMove, true, A, C, B, event_queue, font);

	draw(numDisc, numMove, false, A, C, B, event_queue, font);

	//wait for user to close window
	finishScreen(event_queue, font);
}


void changeNumDisc(int& numDisc, int numMove, Peg& A, Peg& C, Peg& B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font) {

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR cyan = al_map_rgb(0, 255, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	bool done = false;
	bool refresh = true;
	bool initial = true;
	float mx = 0, my = 0;

	while (!done) {

		//update display if user adjusts the # of disks 
		if (refresh) {
			draw(numDisc, numMove, false, A, C, B, event_queue, font);

			//draw buttons to adjust # of disks 
			al_draw_textf(font[REGULAR], white, 5, 5, 0, "Discs: %d", numDisc);
			al_draw_filled_rectangle(95, 10, 125, 40, white);
			al_draw_filled_rectangle(135, 10, 165, 40, white);
			al_draw_filled_triangle(100, 15, 120, 15, 110, 35, red);
			al_draw_filled_triangle(140, 35, 160, 35, 150, 15, green);

			//draw begin button 
			al_draw_filled_rounded_rectangle(480, 10, 580, 65, 10, 10, red);
			al_draw_text(font[BOLD], white, 490, 15, 0, "Begin");

			al_flip_display();
			refresh = false;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//user presses mouse 1 
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mx = ev.mouse.x;
				my = ev.mouse.y;
			}

			if (my >= 10 && my <= 40) {
				//user clicks button to decrease # of discs 
				if (mx >= 95 && mx <= 125) {
					if (numDisc > 1) {
						numDisc--;

						//shift ID of other discs 
						for (Node* curr = A.getHead()->next; curr; curr = curr->next) {
							(curr->ID)--;
						}

						A.pop(initial);
						refresh = true; 
					}

				}
				//user clicks button to increase # of discs 
				else if (mx >= 135 && mx <= 165) {
					if (numDisc < MAX_DISC) {
						numDisc++;

						//create new disc
						Node* newnode = new Node;
						newnode->x = A.cx;
						newnode->y = A.topY;
						newnode->radius = A.getHead()->radius - 10;
						newnode->colour = (A.size % 2) ? yellow : cyan;
						newnode->ID = 1;

						//shift ID of other discs
						for (Node* curr = A.getHead(); curr; curr = curr->next) {
							(curr->ID)++;
						}
						Node* curr = A.getHead();
						curr = curr->next; 
						A.push(newnode);
						refresh = true;
					}
				}
			}


			//begin hanoi if user clicks begin
			if ((mx >= 480 && mx <= 580) && (my >= 10 && my <= 50)) {
				done = true;
				al_draw_filled_rounded_rectangle(540, 10, 630, 50, 10, 10, al_map_rgb(128, 128, 128));
				al_draw_text(font[REGULAR], black, 550, 15, 0, "Begin");
			}
		}
	}
}
