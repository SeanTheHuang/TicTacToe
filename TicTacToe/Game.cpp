#include "Game.h"
#include "Draw.h"
#include <conio.h>
#include <time.h>
#include <math.h>

Game::Game()
{
	srand((size_t)time(NULL));

	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		_gameBoard[i] = EMPTY;
	}
}

void Game::StartGame()
{
	MainMenuState();
}

void Game::MainMenuState()
{
	bool validUserInput = false;

	Draw::MainMenuScreen();

	while (!validUserInput)
	{
		int userInput = _getch();

		//Special key inputted, get special key
		if (userInput == 0 || userInput == 0xE0)
		{
			userInput = _getch();
		}

		//Check for valid key inputted
		switch ((char)userInput)
		{
		case ('1'):	//VS PLAYER
		{
			GameTwoPlayers();
			validUserInput = true;
			break;
		}
		case ('2'):	//VS NORMAL COMPUTER
		{
			GameVsNormalBot();
			validUserInput = true;
			break;
		}
		case ('3'):	//VS HARD COMPUTER
		{
			GameVsHardBot();
			validUserInput = true;
			break;
		}
		case ('0'):	//Quit Game
		{
			validUserInput = true;
			break;
		}
		default:
			break;
		}

	}

}

void Game::GameTwoPlayers()
{
	Draw::GameUI();

	GAME_OVER_STATES currentGameState = GAME_NOT_OVER;

	//0 = Noughts turn
	//1 = Crosses turn
	int whosTurn = rand() % 2;

	while (currentGameState == GAME_NOT_OVER)
	{
		//Write text for whos turn
		Draw::GoToXY(7, 3);

		if (whosTurn == 0)
			std::cout << "[Noughts turn to play!]";
		else
			std::cout << "[Crosses turn to play!]";

		
		int playersChoice = getPlayerChoice();

		if (whosTurn == 0)	//Nought placement
			_gameBoard[playersChoice] = NOUGHT;
		else				//Cross placement
			_gameBoard[playersChoice] = CROSS;

		//Next person's turn
		whosTurn = (whosTurn+1) % 2;
	}

	int hang;
	std::cin >> hang;
}

void Game::GameVsNormalBot()
{
	Draw::GameUI();
}

void Game::GameVsHardBot()
{
	Draw::GameUI();
}

GAME_OVER_STATES Game::checkGameOver3x3()
{
	bool boardIsFull = true;

	//Check adjacent win
	for (size_t i = 0; i < 3; i++)
	{
		//Horizontal win
		if (_gameBoard[i] != EMPTY && _gameBoard[i] == _gameBoard[i + 1]
			&& _gameBoard[i] == _gameBoard[i + 2])
		{
			return (_gameBoard[i] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
		}
		//Vertical Win
		else if (_gameBoard[i] != EMPTY && _gameBoard[i] == _gameBoard[i + 3]
			&& _gameBoard[i] == _gameBoard[i + 6])
		{
			return (_gameBoard[i] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
		}

		//If empty slot found in row, board is not empty
		if (_gameBoard[i] == EMPTY || _gameBoard[i + 1] == EMPTY || _gameBoard[i + 2] == EMPTY)
		{
			boardIsFull = false;
		}
	}

	//Check diagonal win
	if (_gameBoard[0] != EMPTY && _gameBoard[0] == _gameBoard[4]
		&& _gameBoard[0] == _gameBoard[8])
	{
		return (_gameBoard[0] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
	}
	else if (_gameBoard[2] != EMPTY && _gameBoard[2] == _gameBoard[4]
		&& _gameBoard[0] == _gameBoard[6])
	{
		return (_gameBoard[2] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
	}

	if (!boardIsFull)
		return GAME_NOT_OVER;

	//Reach here: Board is full and no winner
	return DRAW;
}

int Game::getPlayerChoice()
{
	int currentSelectedIndex = 0;

	bool validInput = false;

	while (!validInput)	//Keep looping until valid choice
	{
		//Highlight currently selected
		Draw::CurrentBoardState(_gameBoard);
		Draw::HighlightTile(currentSelectedIndex % BOARD_SIZE, 
			(int)currentSelectedIndex / BOARD_SIZE, _gameBoard[currentSelectedIndex]);

		//Check for inputs
		int userInput = _getch();

		//Special key inputted, get special key
		if (userInput == 0 || userInput == 0xE0)
		{
			userInput = _getch();
		}

		switch (userInput)
		{
		case (KEY_UP):
		{
			currentSelectedIndex -= 3;
			break;
		}
		case (KEY_DOWN):
		{
			currentSelectedIndex += 3;
			break;
		}
		case (KEY_LEFT):
		{
			currentSelectedIndex--;

			//Logic to loop across board properly
			if (currentSelectedIndex % BOARD_SIZE == 2 || currentSelectedIndex == -1)
				currentSelectedIndex += 3;

			break;
		}
		case (KEY_RIGHT):
		{
			currentSelectedIndex++;

			//Logic to loop across board properly
			if (currentSelectedIndex % BOARD_SIZE == 0)
				currentSelectedIndex -= 3;

			break;
		}
		case (KEY_ENTER):
		{
			//Do range check before checking selection
			int totalTiles = BOARD_SIZE * BOARD_SIZE;

			if (currentSelectedIndex < 0)
				currentSelectedIndex += totalTiles;

			else if (currentSelectedIndex >= totalTiles)
				currentSelectedIndex -= totalTiles;

			//Now check if player can place there
			if (_gameBoard[currentSelectedIndex] == EMPTY)
				validInput = true;

			break;
		}
		default:
			break;
		}

		//Keep current selection in range
		int totalTiles = BOARD_SIZE * BOARD_SIZE;

		if (currentSelectedIndex < 0)
			currentSelectedIndex += totalTiles;

		else if (currentSelectedIndex >= totalTiles)
			currentSelectedIndex -= totalTiles;
	}

	return currentSelectedIndex;
}

