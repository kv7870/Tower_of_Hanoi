//header.h
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "class.h"
#include <vector>
const int numPeg = 3;
const int pegHeight = 100;
const int MAX_DISC = 8;


enum FONTS { BOLD, REGULAR };

void initAllegro(ALLEGRO_DISPLAY** display, ALLEGRO_EVENT_QUEUE** event_queue
	, ALLEGRO_FONT** font);

void hanoi(int n, int& move, bool lvlFour, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE* event_queue,
	ALLEGRO_FONT** font);
void Move(int n, int& numMove, Peg& s, Peg& d);
void draw(int numDisc, int& numMove, bool lvlFour, Peg s, Peg d, Peg i,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
void titleScreen(int& numDisc, int& choice, int& numMove, Peg A, Peg C, Peg B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
void levelFourMinus(int& numDisc, int& choice, int& numMove, Peg& A, Peg& C, Peg& B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
void levelFour(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue,
	ALLEGRO_FONT** font);
void levelFourPlus(int& numDisc, int numMove, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue,
	ALLEGRO_FONT** font);

void walkthrough(int n, Peg s, Peg d, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
bool selectDisc(float mx, float my, Peg** s, Peg& A, Peg& C, Peg& B);
bool chkValidMove(float mx, float my, Peg& A, Peg& C, Peg& B, Peg* s, Peg** d);
void drawOptions(Peg* s, Peg& A, Peg& C, Peg& B, ALLEGRO_FONT** font);
void changeNumDisc(int& numDisc, int numMove, Peg& A, Peg& C, Peg& B,
	ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
bool chkSolved(int numDisc, Peg& C);
void finishScreen(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);