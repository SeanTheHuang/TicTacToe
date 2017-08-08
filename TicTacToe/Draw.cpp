//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name : Draw.cpp
// Description : Implementation of Draw class
// Author : Sean Huang
// Mail : sean.hua7281@mediadesig.school.nz
//

#include "Draw.h"

#include <Windows.h>


// Function: MainMenuScreen
// Inputs: none
// Output: none
// Task: Draws game title and options for players to choose from

void Draw::MainMenuScreen()
{
	ClearAll();

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	std::cout << "Sean's TIC TAC TOE" << std::endl;
	std::cout << "=========================" << std::endl << std::endl;

	std::cout << "Choose game mode:" << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "1) Player vs player" << std::endl;
	std::cout << "2) Player vs computer" << std::endl;
	std::cout << "3) Player vs computer [Hard]" << std::endl << std::endl;

	std::cout << "0) Quit Game" << std::endl;


}

// Function: GameUI
// Inputs: none
// Output: none
// Task: Draws gameboard and instructions on how to play 

void Draw::GameUI()
{
	ClearAllButTitle();

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	GoToXY(0, BOARD_Y_OFFSET);
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "          -----+-----+-----     [Arrow Keys] to pick your move" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |          [Enter] to confirm your move!" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "          -----+-----+-----" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;

}

// Function: CurrentBoardState
// Inputs: Tile_STATE array - array with state of all tiles
// Output: none
// Task: Draws the states of all tiles in the current game board

void Draw::CurrentBoardState(enum TILE_STATE gameBoard[])
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{			
			switch (gameBoard[x + (3 * y)])
			{
			case (EMPTY):
			{
				Draw::ClearTile(x, y);
				break;
			}
			case (NOUGHT):
			{
				Draw::DrawNought(x, y);
				break;
			}
			case (CROSS):
			{
				Draw::DrawCross(x, y);
				break;
			}
			default:
				break;
			}
		}
	}

}

// Function: ClearAll
// Inputs: none
// Output: none
// Task: Fills the console with nothing (clearing it out)

void Draw::ClearAll()
{
	GoToXY(0, 0);

	for (size_t i = 0; i < 25; i++)
	{
		std::cout << "                                                                                                                                                " << std::endl;
	}

	GoToXY(0, 0);
}

// Function: ClearAllButTitle
// Inputs: none
// Output: none
// Task: Clears all text from console except for the first 2 rows

void Draw::ClearAllButTitle()
{
	GoToXY(0, 3);

	for (size_t i = 0; i < 22; i++)
	{
		std::cout << "                                                                                                                                                           " << std::endl; 
	}

	GoToXY(0, 3);
}

// Function: GoToXY
// Inputs: int, x & y position
// Output: none
// Task: Moves the console cursor to [x,y] position in console

void Draw::GoToXY(int xPos, int yPos)
{
	COORD point;
	point.X = xPos;
	point.Y = yPos;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// Function: ChangeDrawColour
// Inputs: TEXT_COLOUR - colour to change to (foreground & background)
// Output: none
// Task: Changes the draw colour on the console

void Draw::ChangeDrawColour(TEXT_COLOUR newColour)
{
	switch (newColour)
	{
	case (COLOUR_WHITE_ON_BLACK):
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	}
	case (COLOUR_RED_ON_BLACK):
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	}
	case (COLOUR_GREEN_ON_BLACK):
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	}
	case (COLOUR_BLACK_ON_GREY):
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		break;
	}
	case (COLOUR_YELLOW_ON_BLACK):
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	}
	default:
		break;
	}
}

// Function: DrawCross
// Inputs: x & y position - top left corner
// Output: none
// Task: Draws a 5x3 sized cross on the console at position [x,y]

void Draw::DrawCross(int x, int y)
{
	ChangeDrawColour(COLOUR_GREEN_ON_BLACK);

	int xPos = BOARD_X_OFFSET + (x * 6);
	int yPos = BOARD_Y_OFFSET + (y * 4);

	GoToXY(xPos, yPos);
	std::cout << "#   #";
	GoToXY(xPos, yPos+1);
	std::cout << "  #  ";
	GoToXY(xPos, yPos+2);
	std::cout << "#   #";

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);
}

// Function: DrawNought
// Inputs: x & y position - top left corner
// Output: none
// Task: Draws a 5x3 sized nought on the console at position [x,y]


void Draw::DrawNought(int x, int y)
{
	ChangeDrawColour(COLOUR_RED_ON_BLACK);

	int xPos = BOARD_X_OFFSET + (x * 6);
	int yPos = BOARD_Y_OFFSET + (y * 4);

	GoToXY(xPos, yPos);
	std::cout << "#####";
	GoToXY(xPos, yPos+1);
	std::cout << "#   #";
	GoToXY(xPos, yPos+2);
	std::cout << "#####";

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);
}

// Function: ClearTile
// Inputs: x & y position - top left corner
// Output: none
// Task: Clear out a 5x3 box in console at position [x,y]

void Draw::ClearTile(int x, int y)
{
	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	int xPos = BOARD_X_OFFSET + (x * 6);
	int yPos = BOARD_Y_OFFSET + (y * 4);

	GoToXY(xPos, yPos);
	std::cout << "     ";
	GoToXY(xPos, yPos+1);
	std::cout << "     ";
	GoToXY(xPos, yPos+2);
	std::cout << "     ";

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);
}

// Function: HighlightTile
// Inputs: x & y position - top left corner. TILE_STATE - what to draw at this position
// Output: none
// Task: Draws a grey 5x3 box. The box can be filled with a nought, cross, or nothing
//		 depending on input.

void Draw::HighlightTile(int x, int y, TILE_STATE state)
{
	ChangeDrawColour(COLOUR_BLACK_ON_GREY);

	int xPos = BOARD_X_OFFSET + (x * 6);
	int yPos = BOARD_Y_OFFSET + (y * 4);

	switch (state)	//Draw different symbol according to current tile placed
	{
	case (EMPTY):
	{
		GoToXY(xPos, yPos);
		std::cout << "     ";
		GoToXY(xPos, yPos + 1);
		std::cout << "     ";
		GoToXY(xPos, yPos + 2);
		std::cout << "     ";
		break;
	}
	case (NOUGHT):
	{
		GoToXY(xPos, yPos);
		std::cout << "#####";
		GoToXY(xPos, yPos + 1);
		std::cout << "#   #";
		GoToXY(xPos, yPos + 2);
		std::cout << "#####";
		break;
	}
	case (CROSS):
	{
		GoToXY(xPos, yPos);
		std::cout << "#   #";
		GoToXY(xPos, yPos + 1);
		std::cout << "  #  ";
		GoToXY(xPos, yPos + 2);
		std::cout << "#   #";
		break;
	}
	default:
		break;
	}

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);
}
