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


void hanoi(int n, int &move, bool lvlFour, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT ** font)
{
	if (n > 0) {
		
		hanoi(n - 1, move, lvlFour, s, i, d, event_queue, font);
		Move(n, move, s, d);
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		draw(n, move, lvlFour, s, d, i, event_queue, font);
		al_flip_display(); 
		al_rest(0.1);
		hanoi(n - 1, move, lvlFour, i, d, s, event_queue, font);
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
	d.push(s.pop(0)) ; 	
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
