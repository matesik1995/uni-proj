#include "objects.h"

void objects_initTiles(Tile *tiles)
{
	for (int i = 0; i < 64; i++)
	{
		tiles[i].id = i;
		tiles[i].row = i/8;
		tiles[i].col = i%8;
		tiles[i].pawnId = -1;
	}
}

void objects_initPawns(Pawn *pawns)
{
	for (int i = 0; i < 24; i++)
	{
		pawns[i].id = i;
		pawns[i].team = 1+i/12;
		if (i < 12)
		{
			if ((i / 4) % 2 == 0)
				pawns[i].tileId = 1 + i * 2;
			else
				pawns[i].tileId = i * 2;
		}
		else
		{

			if ((i / 4) % 2 == 0)
				pawns[i].tileId = 16 + 1 + i * 2;
			else
				pawns[i].tileId = 16 + i * 2;
		}
		pawns[i].selectable = false;
		pawns[i].type = 1;
		pawns[i].alive = true;
	}
}

void objects_updateTiles(Tile *tiles, Pawn *pawns)
{
	for (int i = 0; i < 24; i++)
	{
		tiles[pawns[i].tileId].pawnId = pawns[i].id;
	}
	for (int i = 0; i < 64; i++)
	{
		if(tiles[i].pawnId<0)
			tiles[i].pawnId=-1;
	}
}

int SELECTED = -1;
bool BLOCKED = false;

void objects_selectPawn(int id)
{
	if(!BLOCKED)
		SELECTED = id;
}

int objects_getSelectedPawn()
{
	return SELECTED;
}

void objects_setSelectionBlock(bool t)
{
	BLOCKED = t;
}

bool objects_getSelectionBlock()
{
	return BLOCKED;
}

void objects_setTileMove(Tile *tiles, int id)
{
	tiles[id].pawnId = -2;
}
void objects_setTileCapture(Tile *tiles, int id)
{
	tiles[id].pawnId = -3;
}

void objects_setPawnDie(Pawn *pawns, Tile *tiles, int id)
{
	tiles[pawns[id].tileId].pawnId = -1;
	pawns[id].alive = false;
	pawns[id].tileId = -1;
}

void objects_setSuperPawn(Pawn *pawns, int id)
{
	pawns[id].type = 2;
}
