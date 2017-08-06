#pragma once

#include "Game.h"

#include <iostream>

#define BOARD_X_OFFSET 10
#define BOARD_Y_OFFSET 5

enum TEXT_COLOUR
{
	NO_COLOUR = -1,
	COLOUR_WHITE_ON_BLACK, 
	COLOUR_RED_ON_BLACK, 
	COLOUR_GREEN_ON_BLACK, 
	COLOUR_BLACK_ON_GREY, 
};

class Draw
{
public:
	Draw() = delete;

	static void MainMenuScreen();
	static void GameUI();
	static void CurrentBoardState(enum TILE_STATE[]);
	static void HighlightTile(int, int, TILE_STATE);

	static void GoToXY(int, int);

	
private:
	static void ClearAll();
	static void ClearAllButTitle();

	static void ChangeDrawColour(TEXT_COLOUR);

	static void DrawCross(int, int);
	static void DrawNought(int, int);
	static void ClearTile(int, int);
};