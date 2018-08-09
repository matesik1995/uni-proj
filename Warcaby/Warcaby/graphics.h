#pragma once
#include "objects.h"
#include "engine.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

struct graphPos { int x; int y; };

void graphics_initFonts();
void graphics_drawMainMenu(int a);
void graphics_drawSelectGameMenu(int a);
void graphics_drawSideMenu(int a);

void graphics_drawBoard(Tile *tiles);
void graphics_drawPawns(Pawn *pawns);

graphPos graphics_getCenterOfTile(int id);