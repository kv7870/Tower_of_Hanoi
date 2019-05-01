//class.cpp
#include "stdafx.h"
#include "header.h"
#include "class.h"
#include <iostream>
#include <cstdio>
using namespace std;

Peg::Peg(char c, int i) {
	head = NULL;
	pegID = c;
	cx = i;
	size = 0;

	//top side
	topY = 400;
}

//constructor 
Peg::Peg(char c, int pegX, int numDiscs) {
	head = NULL;
	pegID = c;
	cx = pegX;
	size = 0;
	topY = 400;
	//disc width 
	int width = 50;
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 255, 255);


	float x = 102.5, y = 400, r = 90;

	for (int i = 0; i < numDiscs; i++) {
		Node* temp = new Node;
		ALLEGRO_COLOR colour = (i % 2) ? yellow : blue;
		temp->ID = numDiscs - i;
		temp->x = x;
		temp->y = y;
		temp->radius = r;
		temp->colour = colour;

		push(temp);

		y -= 20;
		r -= 10;
	}
}

void Peg::push(Node* newnode) {
	newnode->next = head;
	head = newnode;
	size++;
	topY -= 20;
}

Node* Peg::pop(bool initial) {
	Node* temp = head;
	head = head->next;
	topY += 20;
	size--;

	if (initial) {
		delete temp;
		temp = NULL;
	}

	return temp;
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