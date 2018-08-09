#pragma once
#include <stdio.h>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

void engine_start();
void quitGame();
void engine_initAllegro();
void engine_mouseClickLeft(int x, int y);
int engine_checkCaptureMove(int p, int t);
int engine_checkCaptureMove(int p, int t, int d);
int engine_checkPossibleMoves(int id);
void engine_movePawn(int id, int to);

