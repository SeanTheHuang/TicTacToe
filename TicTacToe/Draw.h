//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name : Draw.h
// Description : Static class with functions to draw onto console
//				 Also has the function of changing text colour in the console
// Author : Sean Huang
// Mail : sean.hua7281@mediadesig.school.nz
//

#pragma once

#include "Game.h"

#include <iostream>

#define BOARD_X_OFFSET 10
#define BOARD_Y_OFFSET 5

enum TEXT_COLOUR	//Different text colours on console
{
	NO_COLOUR = -1,
	COLOUR_WHITE_ON_BLACK, 
	COLOUR_RED_ON_BLACK, 
	COLOUR_GREEN_ON_BLACK, 
	COLOUR_YELLOW_ON_BLACK,
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

	static void ChangeDrawColour(TEXT_COLOUR);
	static void GoToXY(int, int);

	
private:
	static void ClearAll();
	static void ClearAllButTitle();


	static void DrawCross(int, int);
	static void DrawNought(int, int);
	static void ClearTile(int, int);
};