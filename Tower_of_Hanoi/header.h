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

void initAllegro(ALLEGRO_DISPLAY** display, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** event_queue);
void initTower(int numDisc);
void hanoi(int n, Peg s, Peg d, Peg i);
void move(int n, Peg s, Peg d);





