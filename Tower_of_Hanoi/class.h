#pragma once

struct Node {
	int data;
	Node* next;
};

class Peg {
public:
	Peg(char); 
	Peg(char, int); 

	void push(int);
	void pop();
	//void printStack();
	char ID;
	Node* getHead();
	void printStack(); 

private:
	Node* head;
};