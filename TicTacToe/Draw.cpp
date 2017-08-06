#include "Draw.h"

#include <Windows.h>

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

void Draw::GameUI()
{
	ClearAllButTitle();

	ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	GoToXY(0, BOARD_Y_OFFSET);
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "          -----+-----+-----" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "          -----+-----+-----" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;
	std::cout << "               |     |" << std::endl;

}

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

void Draw::ClearAll()
{
	GoToXY(0, 0);

	for (size_t i = 0; i < 25; i++)
	{
		std::cout << "                                                                                                                        " << std::endl;
	}

	GoToXY(0, 0);
}

void Draw::ClearAllButTitle()
{
	GoToXY(0, 3);

	for (size_t i = 0; i < 22; i++)
	{
		std::cout << "                                                                                                                        " << std::endl; 
	}

	GoToXY(0, 3);
}

void Draw::GoToXY(int xPos, int yPos)
{
	COORD point;
	point.X = xPos;
	point.Y = yPos;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

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

void Draw::HighlightTile(int x, int y, TILE_STATE state)
{
	ChangeDrawColour(COLOUR_BLACK_ON_GREY);

	int xPos = BOARD_X_OFFSET + (x * 6);
	int yPos = BOARD_Y_OFFSET + (y * 4);

	switch (state)
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
