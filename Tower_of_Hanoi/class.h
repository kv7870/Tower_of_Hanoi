#pragma once

struct Node {
	//disc number 
	int ID;
	//x = centre of disc, y = top edge of disc 
	int x, y;
	//radius of disc (origin at peg)
	int radius;
	ALLEGRO_COLOR colour;
	Node* next;
};


//stack 
class Peg {
public:
	//constructors
	Peg(char, int);
	Peg(char, int, int);

	//push disc to peg stack
	void push(Node*);
	//pop top disc; if mainMenu is true, user can decrease # of discs, which requires delete operator 
	Node * pop(bool mainMenu);
	//A, B, C
	char pegID;
	Node* getHead(); 
	void printStack(); 
	
	//x-coordinate of peg's centre
	int cx; 
	//y-coordinate of top edge of the topmost disc
	int topY; 
	//number of discs on the peg
	int size; 

private:
	Node* head;
};


