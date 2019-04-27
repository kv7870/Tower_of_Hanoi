#pragma once

struct Node {
	//disc number 
	int ID;
	//bottom right corner 
	int x, y;
	int radius;
	ALLEGRO_COLOR colour;
	Node* next;
};


class Peg {
public:
	Peg(char);
	Peg(char, int);

	void push(Node*);
	Node * pop();
	char pegID;
	Node* getHead(); 
	void printStack(); 

private:
	Node* head;
};


