#pragma once

struct Tile {
	int id;
	int row;
	int col;
	int pawnId;
};

struct Pawn {
	int id;
	int team;
	int tileId;
	bool alive;
	int type;
	bool selectable;
};

void objects_initTiles(Tile * tiles);
void objects_initPawns(Pawn * pawns);
void objects_updateTiles(Tile *tiles, Pawn *pawns);

void objects_selectPawn(int id);
int objects_getSelectedPawn();
void objects_setSelectionBlock(bool t);
bool objects_getSelectionBlock();

void objects_setTileMove(Tile *tiles, int id);
void objects_setTileCapture(Tile *tiles, int id);
void objects_setPawnDie(Pawn *pawns, Tile *tiles, int id);
void objects_setSuperPawn(Pawn *pawns, int id);