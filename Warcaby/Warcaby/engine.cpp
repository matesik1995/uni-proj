#include "objects.h"
#include "graphics.h"
#include "engine.h"
#include "logic.h"

bool done;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
Tile tiles[64];
Pawn pawns[64];

int GAME_STATE = 0; // 0 - main menu; 1 - game type select; 2 - game play;
int GAME_TYPE = 0; // 0 - AI; 1 - vs friend;

void engine_mouseHover(int x, int y);

int menu_opt;

void engine_start()
{
	engine_initAllegro();
	// TEMP
	objects_initTiles(tiles);
	objects_initPawns(pawns);

	//pawns[10].type = 2;
	//pawns[13].type = 2;
	//pawns[13].tileId = 30;
	//pawns[17].tileId = 35;

	objects_updateTiles(tiles, pawns);
	// END

	int m_pos_x = 0;
	int m_pos_y = 0;

	bool redraw = false;
	done = false;
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			m_pos_x = ev.mouse.x;
			m_pos_y = ev.mouse.y;
			 
			engine_mouseHover(m_pos_x, m_pos_y);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
				engine_mouseClickLeft(m_pos_x, m_pos_y);
		}

		if (redraw && al_event_queue_is_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 32, 0));
			switch (GAME_STATE)
			{
			case 0:
				graphics_drawMainMenu(menu_opt);
				break;
			case 1:
				graphics_drawSelectGameMenu(menu_opt);
				break;
			case 2:
				graphics_drawBoard(tiles);
				graphics_drawPawns(pawns);
				graphics_drawSideMenu(menu_opt);
				break;
			}
			al_flip_display();
		}		
	}


}


void quitGame()
{
	done = true;
}



void engine_initAllegro()
{
	al_init();
	timer = al_create_timer(1.0 / 30);
	display = al_create_display(620, 420);
	event_queue = al_create_event_queue();

	al_install_mouse();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_init_font_addon();
	al_init_ttf_addon();
	graphics_initFonts();

	al_start_timer(timer);

	al_init_primitives_addon();
}

int abs(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

int turn = 2; // 2 - biale, 1 - czarne; CHOCIAZ RAZ CZARNE LEPSZE HEHE

void nextTurn()
{
	if (turn == 1)
		turn = 2;
	else
	{
		if (GAME_TYPE == 1) {
			turn = 1;
		}
		else
		{
			printf("AI MOVE\n");
			turn = 1;
			logic_makeMove(pawns, tiles);
		}
	}
}


void engine_mouseHover(int x, int y)
{
	if (GAME_STATE < 2)
	{
		if (y > 175 && y < 205)
			menu_opt = 1;
		else if (y > 225 && y < 255)
			menu_opt = 2;
		else if (y > 275 && y < 305)
			menu_opt = 3;
		else menu_opt = 0;
	}
	else
	{
		if (x > 470 && x < 570 && y > 350 && y < 360)
			menu_opt = 1;
		else if (x > 490 && x< 555 && y>380 && y<390)
			menu_opt = 2;
		else menu_opt = 0;
	}
}

void engine_mouseClickLeft(int x, int y)
{
	switch (GAME_STATE)
	{
	case 0:
		if (menu_opt == 1) {
			GAME_STATE = 1;
		}
		else if (menu_opt == 2)
		{
			//LOAD GAME
			std::fstream saveFile;
			saveFile.open("save.txt", std::ios::in | std::ios::out | std::fstream::app);
			saveFile >> GAME_TYPE >> turn;
			for (int i = 0; i < 64; i++)
			{
				saveFile >> tiles[i].id >> tiles[i].row >> tiles[i].col >>tiles[i].pawnId;
			}
			for (int i = 0; i < 24; i++)
			{
				saveFile >> pawns[i].alive >> pawns[i].id >> pawns[i].selectable >> pawns[i].team >> pawns[i].tileId >> pawns[i].type;
			}

			saveFile.close();

			GAME_STATE = 2;
			objects_updateTiles(tiles, pawns);			
		}
		else if (menu_opt == 3) quitGame();
		break;
	case 1:
		if (menu_opt == 1) {
			objects_initTiles(tiles);
			objects_initPawns(pawns);
			objects_updateTiles(tiles, pawns);
			GAME_STATE = 2;
			GAME_TYPE = 0;
		} else
		if (menu_opt == 2) {
			objects_initTiles(tiles);
			objects_initPawns(pawns);
			objects_updateTiles(tiles, pawns);
			GAME_STATE = 2;
			GAME_TYPE = 1;
		}
		else if (menu_opt == 3) GAME_STATE = 0;
		break;
	case 2:  //IN GAME
		if (menu_opt == 2)
			GAME_STATE = 0;
		else if (menu_opt == 1)
		{// SAVE GAME
			std::fstream saveFile;
			saveFile.open("save.txt", std::ios::in | std::ios::out | std::fstream::trunc);
			if (saveFile.good()) {
				saveFile << GAME_TYPE << "\t" << turn << std::endl;
				for (int i = 0; i < 64; i++)
				{
					saveFile << tiles[i].id << "\t" << tiles[i].row << "\t" << tiles[i].col << "\t" << tiles[i].pawnId << std::endl;
				}
				for (int i = 0; i < 24; i++)
				{
					saveFile << pawns[i].alive << "\t" << pawns[i].id << "\t" << pawns[i].selectable << "\t" << pawns[i].team << "\t" << pawns[i].tileId << "\t" << pawns[i].type << std::endl;
				}

				saveFile.close();
			}else 
			printf("ZAPIS BLAD\n");
		}
		for (int i = 0; i < 64; i++)
		{
			graphPos pos = graphics_getCenterOfTile(i);
			if (abs(x - pos.x) < 25 && abs(y - pos.y) < 25)
			{
				if (objects_getSelectedPawn() >= 0 && tiles[i].pawnId <= -2)//MAKE MOVE TO ALLOWED TILE
					engine_movePawn(objects_getSelectedPawn(), i);
				objects_updateTiles(tiles, pawns);

				if (objects_getSelectedPawn() == tiles[i].pawnId && !objects_getSelectionBlock()) //DESELECT PAWN
					objects_selectPawn(-1);
				else if (turn == pawns[tiles[i].pawnId].team) //SELECT PAWN AND CHECK MOVES
				{
					objects_selectPawn(tiles[i].pawnId);
					if (!objects_getSelectionBlock())
					{
						if (!engine_checkPossibleMoves(objects_getSelectedPawn()))
							objects_selectPawn(-1);
					}
					else
					{
						engine_checkCaptureMove(objects_getSelectedPawn(), pawns[objects_getSelectedPawn()].tileId);
					}

					printf("SELECTED: %d TILE: %d\n", objects_getSelectedPawn(), tiles[i].id);

				}

				break;
			}
		}
		break;

	}
	
	
}



int checkDiag(int pawn, int tile, int dir)
{
	
	if (dir > 0) {
		if (dir % 7 == 0 && tile % 8 == 0) return -1;
		if (dir % 9 == 0 && tile % 8 == 7) return -1;
	}
	else
	{
		if (dir % 7 == 0 && tile % 8 == 7) return -1;
		if (dir % 9 == 0 && tile % 8 == 0) return -1;
	}
	tile += dir;
	
	//printf("t: %d\tt8: %d\td: %d\n", tile, tile % 8, dir);
	if (tiles[tile].pawnId < 0) return tile;
	return -2;
}

int engine_checkCaptureMove(int p, int t)
{
	int ret = 0;
		if (t + 7 < 64 && checkDiag(p, t + 7, 7) >= 0)
			if (tiles[t + 7].pawnId >= 0 && pawns[tiles[t + 7].pawnId].team != pawns[p].team && tiles[t + 14].pawnId < 0)
			{
				objects_setTileCapture(tiles, t + 14);
				ret+=100;
			}

		if (t + 9 < 64 && checkDiag(p, t + 9, 9) >= 0)
			if (tiles[t + 9].pawnId >= 0 && pawns[tiles[t + 9].pawnId].team != pawns[p].team && tiles[t + 18].pawnId < 0)
			{
				objects_setTileCapture(tiles, t + 18);
				ret+=100;
			}

		if (t + -7 >= 0 && checkDiag(p, t + -7, -7) >= 0)
			if (tiles[t - 7].pawnId >= 0 && pawns[tiles[t - 7].pawnId].team != pawns[p].team && tiles[t - 14].pawnId < 0)
			{
				objects_setTileCapture(tiles, t - 14);
				ret+=100;
			}

		if (t + -9 >= 0 && checkDiag(p, t + -9, -9) >= 0)
			if (tiles[t - 9].pawnId >= 0 && pawns[tiles[t - 9].pawnId].team != pawns[p].team && tiles[t - 18].pawnId < 0)
			{
				objects_setTileCapture(tiles, t - 18);
				ret+=100;
			}
	return ret;
}

int engine_checkCaptureMove(int p, int t, int d)
{
	int ret = 0;
	
	//printf("p: %d\tt: %d\td: %d\n", p,t,d);
	//printf("%d >= 0\t%d != %d\t%d < 0\n", tiles[t + d].pawnId, pawns[tiles[t + d].pawnId].team, pawns[p].team, tiles[t + d * 2].pawnId);
	if(tiles[t].col != 1 && tiles[t].col !=6)
		if (tiles[t + d].pawnId >= 0 && pawns[tiles[t+d].pawnId].team != pawns[p].team && tiles[t + d*2].pawnId < 0)
		{
			objects_setTileCapture(tiles, t + d*2);
			ret+=100;
		//	printf("BICIE\n");
		}
	return ret;
}

int engine_checkPossibleMoves(int id)
{
	int ret = 0;
	int tmp;
	if (pawns[id].type == 1) {
		if (pawns[id].team == 1) {
			if ((tmp = checkDiag(id, pawns[id].tileId, 7)) >= 0) {
				objects_setTileMove(tiles, tmp);
				ret++;
			}
			if ((tmp = checkDiag(id, pawns[id].tileId, 9)) >= 0) {
				objects_setTileMove(tiles, tmp);
				ret++;
			}
		}
		else
		{
			if ((tmp = checkDiag(id, pawns[id].tileId, -7)) >= 0) {
				objects_setTileMove(tiles, tmp);
				ret++;
			}

			if ((tmp = checkDiag(id, pawns[id].tileId, -9)) >= 0) {
				objects_setTileMove(tiles, tmp);
				ret++;
			}
		}
	}
	else
	{
		int n = 0;
		while ((tmp = checkDiag(id, pawns[id].tileId + n, 7)) >= 0) {
			objects_setTileMove(tiles, tmp);
			n += 7;
			ret++;
		}
		if (tmp == -2)
		{
			ret += engine_checkCaptureMove(id, pawns[id].tileId + n, 7);
		}
		n = 0;
		while ((tmp = checkDiag(id, pawns[id].tileId + n, 9)) >= 0) {
			objects_setTileMove(tiles, tmp);
			n += 9;
			ret++;
		}
		if (tmp == -2)
		{
			ret += engine_checkCaptureMove(id, pawns[id].tileId + n, 9);
		}
		n = 0;
		while ((tmp = checkDiag(id, pawns[id].tileId + n, -7)) >= 0) {
			objects_setTileMove(tiles, tmp);
			n += -7;
			ret++;
		}
		if (tmp == -2)
		{
			ret += engine_checkCaptureMove(id, pawns[id].tileId + n, -7);
		}
		n = 0;
		while ((tmp = checkDiag(id, pawns[id].tileId + n, -9)) >= 0) {
			objects_setTileMove(tiles, tmp);
			n += -9;
			ret++;
		}
		if (tmp == -2)
		{
			ret += engine_checkCaptureMove(id, pawns[id].tileId + n, -9);
		}

	}
	return ret + engine_checkCaptureMove(id, pawns[id].tileId);
}

void engine_capturePawn(int id)
{
	objects_setPawnDie(pawns, tiles, id);
	objects_updateTiles(tiles, pawns);
}

void engine_movePawn( int id, int to)
{
	int from = pawns[id].tileId;
	if (tiles[to].pawnId==-3)
	{
		//engine_captuerPawn(tiles[from + (to - from) / 2].pawnId);

		int dir = (to - from);
		if (dir % 7 == 0)
		{
			if (dir > 0)
			{
				engine_capturePawn(tiles[to - 7].pawnId);
			}
			else
			{
				engine_capturePawn(tiles[to + 7].pawnId);
			}
		}
		else
		{
			if (dir > 0)
			{
				engine_capturePawn(tiles[to - 9].pawnId);
			}
			else
			{
				engine_capturePawn(tiles[to + 9].pawnId);
			}
		}

		tiles[pawns[id].tileId].pawnId = -1;
		pawns[id].tileId = to;
		objects_updateTiles(tiles, pawns);

		if (!engine_checkCaptureMove(id, pawns[id].tileId))
		{
			nextTurn();
			objects_setSelectionBlock(false);
		}
		else
		{//
			objects_selectPawn(id);
			objects_setSelectionBlock(true);
			//engine_checkCaptureMove(id, pawns[id].tileId);
			if(GAME_TYPE==0 && turn==1)
				logic_makeMove(pawns, tiles);
		}
	}
	else
	{
		tiles[pawns[id].tileId].pawnId = -1;
		pawns[id].tileId = to;
		objects_updateTiles(tiles, pawns);
		printf("JESTEM TU\n");
		nextTurn();
	}

	//DAMKOWANIE
	if (pawns[id].team == 2 && pawns[id].tileId / 8 == 0 && !objects_getSelectionBlock())
		objects_setSuperPawn(pawns, id);
	if (pawns[id].team == 1 && pawns[id].tileId / 8 == 7 && !objects_getSelectionBlock())
		objects_setSuperPawn(pawns, id);
}