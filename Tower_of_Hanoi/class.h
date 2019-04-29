#pragma once

struct Node {
	//disc number 
	int ID;
	//top left corner 
	int x, y;
	int radius;
	ALLEGRO_COLOR colour;
	Node* next;
};


class Peg {
public:
	Peg(char, int);
	Peg(char, int, int);

	void push(Node*);
	Node * pop(bool initial);
	char pegID;
	Node* getHead(); 
	void printStack(); 

	int cx; 
	int topY; 
	int size; 

private:
	Node* head;
};


