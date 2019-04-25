#pragma once
#include "stdafx.h"
#include "header.h"
#include "class.h"
#include <iostream>
using namespace std; 

Peg::Peg(char c) {
	head = NULL;
	ID = c; 
}

Peg::Peg(char c, int numDiscs) {
	head = NULL;
	ID = c;
	int disc = 1;

	for (int i = 0; i < numDiscs; i++)
		push(disc++);
}

void Peg::push(int ringID) {
	Node* newnode = new Node; 
	newnode->data = ringID;
	newnode->next = head;
	head = newnode; 
}

void Peg::pop() {
	if (head != NULL) {
		Node* temp = head;
		head = head->next;
		//delete temp;
	}
}

Node* Peg::getHead() {
	return head; 
}

void Peg::printStack() {
	Node* curr;
	for (curr = head; curr; curr = curr->next)
		cout << curr->data << endl; 
}


