//hanoi.cpp
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
#include "header.h"
#include "class.h"
using namespace std;

//solve hanoi recursively
void hanoi(int n, int& numMove, bool lvlFour, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font)
{
	if (n > 0) {

		hanoi(n - 1, numMove, lvlFour, s, i, d, event_queue, font);
		Move(n, numMove, s, d);
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		//if (lvlFour)
			//walkthrough(n, s, d, event_queue, font); 
		draw(n, numMove, lvlFour, s, d, i, event_queue, font);
		al_flip_display();
		//slow down animation 
		al_rest(0.1);
		hanoi(n - 1, numMove, lvlFour, i, d, s, event_queue, font);
	}
}

//move disc from source to destination
void Move(int n, int& numMove, Peg& s, Peg& d) {
	cout << "Moving disk " << n << " from peg " << s.pegID <<
		" to peg " << d.pegID << endl;
	Node* dHead = d.getHead();
	Node* sHead = s.getHead();

	//set top disc's x-coord to the x-coord of the destination peg
	sHead->x = d.cx;
	//set top disc's y-coord to the y-coord of the topmost disc in destination 
	sHead->y = d.topY;
	numMove++;
	//pop source's top and push it into destination
	d.push(s.pop(0));
}