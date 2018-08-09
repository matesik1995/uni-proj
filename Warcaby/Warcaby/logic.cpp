#include "logic.h"

void logic_makeMove(Pawn * p, Tile * t)
{
	int id = 0;
	int n = 0;
	for (int i = 0; i < 12; i++)
	{
		if (p[i].alive == 1) 
		{
			printf("%d, %d\n", i, engine_checkPossibleMoves(i));
			if (n < engine_checkPossibleMoves(i)) 
			{
				n = engine_checkPossibleMoves(i);
				id = i;
			}
		}
	}

	objects_updateTiles(t, p);
	objects_selectPawn(id); 
	engine_checkPossibleMoves(objects_getSelectedPawn());
	graphics_drawBoard(t);
	graphics_drawPawns(p);

	al_flip_display();
	al_rest(0.5);

	printf("RUSZYLBYM %d\n", objects_getSelectedPawn());
	if (n >= 100)
	{
		for (int i = 0; i < 64; i++)
		{
			printf("%d\t", t[i].pawnId);
			if (t[i].pawnId == -3)
			{
				engine_movePawn(objects_getSelectedPawn(), i);
				printf("RUSZYLBYM %d NA %d\n", objects_getSelectedPawn(), i);
				break;
			}
			if (i % 8 == 7)
				printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			if (t[i].pawnId == -2)
			{
				engine_movePawn(objects_getSelectedPawn(), i);
				printf("RUSZYLBYM %d NA %d\n", objects_getSelectedPawn(), i);
				break;
			}
		}
	}

	//engine_movePawn(id,TO)
}