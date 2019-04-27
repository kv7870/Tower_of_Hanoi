#include "stdafx.h"
#include "header.h"
#include "class.h"
#include <iostream>
using namespace std;

Peg::Peg(char c) {
	head = NULL;
	pegID = c;
}

//constructor 
Peg::Peg(char c, int numDiscs) {
	head = NULL;
	pegID = c;
	//disc width 
	int width = 50; 
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	Node* temp = new Node; 

	for (int i = 0, x = 102.5, y = 400, r = 90; i < numDiscs; i++, y -= 20, r -= 10) {
		ALLEGRO_COLOR colour = (i % 2) ? yellow : blue;
		temp->ID = numDiscs - i;
		temp->x = x;
		temp->y = y;
		temp->radius = r;
		temp->colour = colour; 
		push(temp);
	}
}

void Peg::push(Node *newnode) {

	/*newnode->ID = source->ID;
	newnode->x = source->x;
	newnode->y = source->y;
	newnode->radius = source->radius;
	newnode->colour = source->colour;
	newnode->next = head;
	head = newnode;*/

	newnode->next = head;
	head = newnode; 
}

Node * Peg::pop() {
	Node* temp = head;
	if (head != nullptr) {
		head = head->next;

		//cout << "TOP DISC: " << topDisc << endl;
		return temp; 
	}
	else
		cout << "ERROR" << endl;
}

Node* Peg::getHead() {
	return head;
}

void Peg::printStack() {
	Node* curr;
	cout << "Peg " << pegID << ": " << endl;

	for (curr = head; curr; curr = curr->next)
		cout << curr->ID << " ";

}