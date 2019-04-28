#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "class.h"
#include <vector>
const int numPeg = 3;
const int pegHeight = 100;


enum FONTS {BOLD, REGULAR};

void initAllegro(ALLEGRO_DISPLAY** display, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** event_queue
, ALLEGRO_FONT ** font);
void initTower(int numDisc);

void hanoi(int n, int &move, Peg& s, Peg& d, Peg& i, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT** font);
void Move(int n, int &move, Peg& s, Peg& d);
void draw(int numDisc, int &move, Peg s, Peg d, Peg i, ALLEGRO_FONT ** font);
void titleScreen(int &numDisc, int &choice, int &move, Peg A, Peg C, Peg B, ALLEGRO_FONT** font,
	ALLEGRO_EVENT_QUEUE* event_queue);
void levelFourMinus(int numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
void levelFour(int &numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);
void levelFourPlus(int &numDisc, int move, Peg A, Peg C, Peg B, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT** font);