#include "graphics.h"


ALLEGRO_FONT *f72;
ALLEGRO_FONT *f24;
ALLEGRO_FONT *f24b;
ALLEGRO_FONT *f12;
ALLEGRO_FONT *f12b;

void graphics_initFonts()
{
	f72 = al_load_font("f1.ttf", 72, 0);
	f24 = al_load_font("f1.ttf", 24, 0);
	f24b = al_load_font("f1b.ttf", 24, 0);
	f12 = al_load_font("f1.ttf", 12, 0);
	f12b = al_load_font("f1b.ttf", 12, 0);

}

void graphics_drawMainMenu(int a)
{
	al_draw_text(f72, al_map_rgb(128, 0, 0), 310, 30, ALLEGRO_ALIGN_CENTER, "WARCABY");


	if (a == 1) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 180, ALLEGRO_ALIGN_CENTER, "NOWA GRA");
	else al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 180, ALLEGRO_ALIGN_CENTER, "NOWA GRA");

	if (a == 2) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 230, ALLEGRO_ALIGN_CENTER, "KONTYNUUJ");
	else  al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 230, ALLEGRO_ALIGN_CENTER, "KONTYNUUJ");
	if (a == 3) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 280, ALLEGRO_ALIGN_CENTER, "WYJSCIE");
	else al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 280, ALLEGRO_ALIGN_CENTER, "WYJSCIE");
}

void graphics_drawSelectGameMenu(int a)
{
	al_draw_text(f72, al_map_rgb(128, 0, 0), 310, 30, ALLEGRO_ALIGN_CENTER, "WARCABY");


	if (a == 1) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 180, ALLEGRO_ALIGN_CENTER, "Z KOMPUTEREM");
	else al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 180, ALLEGRO_ALIGN_CENTER, "Z KOMPUTEREM");

	if (a == 2) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 230, ALLEGRO_ALIGN_CENTER, "ZE ZNAJOMYM");
	else  al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 230, ALLEGRO_ALIGN_CENTER, "ZE ZNAJOMYM");
	if (a == 3) al_draw_text(f24b, al_map_rgb(255, 255, 255), 310, 280, ALLEGRO_ALIGN_CENTER, "POWROT");
	else al_draw_text(f24, al_map_rgb(255, 255, 255), 310, 280, ALLEGRO_ALIGN_CENTER, "POWROT");
}

void graphics_drawSideMenu(int a)
{
	if (a == 1) al_draw_text(f12b, al_map_rgb(255, 255, 255), 520, 350, ALLEGRO_ALIGN_CENTER, "ZAPISZ GRE");
	else al_draw_text(f12, al_map_rgb(255, 255, 255), 520, 350, ALLEGRO_ALIGN_CENTER, "ZAPISZ GRE");

	if (a == 2) al_draw_text(f12b, al_map_rgb(255, 255, 255), 520, 380, ALLEGRO_ALIGN_CENTER, "WYJDZ");
	else  al_draw_text(f12, al_map_rgb(255, 255, 255), 520, 380, ALLEGRO_ALIGN_CENTER, "WYJDZ");
}

void graphics_drawBoard(Tile *tiles)
{

	//ramka
	int bW = 10;//borderWidth;
	al_draw_rectangle(bW / 2, bW / 2, bW + bW / 2 + 400, bW + bW / 2 + 400, al_map_rgb(33, 20, 8), bW);
	al_draw_rectangle(1 + bW / 2, 1 + bW / 2, bW + bW / 2 - 1 + 400, bW + bW / 2 - 1 + 400, al_map_rgb(185, 114, 70), 2);

	for (int i = 0; i < 64; i++)	//kratki
	{
		ALLEGRO_COLOR color;
		if (((i % 2) + (i / 8)) % 2 == 0)
			color = al_map_rgb(165, 104, 42);
		else
			color = al_map_rgb(66, 41, 16);

		al_draw_filled_rectangle(bW + (i % 8) * 50, bW + (i / 8) * 50, bW + 50 + (i % 8) * 50, bW + 50 + (i / 8) * 50, color);

		//POSSIBLE MOVES
		if (tiles[i].pawnId == -2)
		{
			graphPos pos = graphics_getCenterOfTile(i);
			al_draw_filled_circle(pos.x, pos.y, 20, al_map_rgba(32, 64, 32, 32));
			al_draw_circle(pos.x, pos.y, 20, al_map_rgb(32, 128, 32), 3);
		}
		if (tiles[i].pawnId == -3) // CAPTURE MOVES
		{
			graphPos pos = graphics_getCenterOfTile(i);
			al_draw_filled_circle(pos.x, pos.y, 20, al_map_rgba(128, 128, 0, 32));
			al_draw_circle(pos.x, pos.y, 20, al_map_rgb(255, 255, 0), 3);

		}
	}

}

void graphics_drawPawns(Pawn *pawns)
{
	for (int i = 0; i < 24; i++)
	{
		if (pawns[i].alive) 
		{
			ALLEGRO_COLOR color;
			if (pawns[i].team == 1)
				color = al_map_rgb(0, 0, 0);
			else
				color = al_map_rgb(255, 255, 255);

			graphPos pos = graphics_getCenterOfTile(pawns[i].tileId);
			al_draw_filled_circle(pos.x, pos.y, 20, color);
			al_draw_circle(pos.x, pos.y, 14, al_map_rgb(128, 128, 128), 2);
			al_draw_circle(pos.x, pos.y, 20, al_map_rgb(64, 64, 64), 1);
			if (objects_getSelectedPawn() == i)
			{
				al_draw_filled_circle(pos.x, pos.y, 20, al_map_rgba(0, 0, 128, 128));
			}
			if (pawns[i].type == 2)
			{
				al_draw_filled_circle(pos.x, pos.y, 5, al_map_rgb(128, 0, 0));
				al_draw_circle(pos.x, pos.y, 20, al_map_rgb(128, 0 , 0), 1);
				al_draw_circle(pos.x, pos.y, 14, al_map_rgb(192,0,0), 2);
			}
		}
	}
}

graphPos graphics_getCenterOfTile(int id)
{
	graphPos pos;
	pos.x = (id % 8) * 50 + 25+10;
	pos.y = (id / 8) * 50 + 25+10;
	return pos;
}