#include "Game.h"
#include "Draw.h"
#include <conio.h>
#include <time.h>
#include <math.h>

Game::Game()
{
	srand((size_t)time(NULL));	//Randomize numbers	
}

void Game::StartGame()
{
	_nextState = PROG_MENU;
	ProgramStateMachine();
}

void Game::ProgramStateMachine()
{
	while (_nextState != PROG_EXIT)
	{
		switch (_nextState)
		{
		case (PROG_MENU):
		{
			MainMenuState();
			break;
		}
		case (PROG_VS_PLAYER):
		{
			GameTwoPlayers();
			break;
		}
		case (PROG_VS_COMPUTER_NORMAL):
		{
			GameVsNormalBot();
			break;
		}
		case (PROG_VS_COMPUTER_HARD):
		{
			GameVsHardBot();
			break;
		}
		default:
			break;
		}
	}
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
			_nextState = PROG_VS_PLAYER;
			validUserInput = true;
			break;
		}
		case ('2'):	//VS NORMAL COMPUTER
		{
			_nextState = PROG_VS_COMPUTER_NORMAL;
			validUserInput = true;
			break;
		}
		case ('3'):	//VS HARD COMPUTER
		{
			_nextState = PROG_VS_COMPUTER_HARD;
			validUserInput = true;
			break;
		}
		case ('0'):	//Quit Game
		{
			_nextState = PROG_EXIT;
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
	ClearBoard();

	GAMEOVER_STATE currentGameState = GAME_NOT_OVER;

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

		
		int playersChoice = GetPlayerChoice();

		if (whosTurn == 0)	//Nought placement
			_gameBoard[playersChoice] = NOUGHT;
		else				//Cross placement
			_gameBoard[playersChoice] = CROSS;

		//Check current game state
		currentGameState = CheckGameOver3x3();

		//Next person's turn
		if (currentGameState == GAME_NOT_OVER)
			whosTurn = (whosTurn+1) % 2;
	}

	//Reach here: Game ended, announce winner

	Draw::CurrentBoardState(_gameBoard);
	Draw::GoToXY(6, 3);

	switch (currentGameState)
	{
	case (NOUGHT_WIN):
	{
		std::cout << "[GAME OVER: Noughts Wins!]   ";
		break;
	}
	case (CROSS_WIN):
	{
		std::cout << "[GAME OVER: Crosses Wins!]   ";
		break;
	}
	case (DRAW):
	{
		std::cout << "[GAME OVER: It's a draw!]   ";
		break;
	}
	default:
		break;
	}

	//Player choose what to do next
	Draw::GoToXY(0, 17);
	std::cout << "   Choose:" << std::endl;
	std::cout << "   --------------------" << std::endl;
	std::cout << "   1) Play again" << std::endl;
	std::cout << "   2) Back to main menu" << std::endl;

	bool validInput = false;
	while (!validInput)
	{
		int userInput = _getch();

		//Special key inputted, get special key
		if (userInput == 0 || userInput == 0xE0)
		{
			userInput = _getch();
		}

		switch ((char)userInput)
		{
		case ('1'):
		{
			validInput = true;
			break;
		}
		case ('2'):
		{
			_nextState = PROG_MENU;
			validInput = true;
			break;
		}
		default:
			break;
		}
	}
}

void Game::GameVsNormalBot()
{
	Draw::GameUI();
}

void Game::GameVsHardBot()
{
	Draw::GameUI();
}

GAMEOVER_STATE Game::CheckGameOver3x3()
{
	bool boardIsFull = true;

	//Check adjacent win
	for (size_t i = 0; i < 3; i++)
	{
		//Horizontal win
		if (_gameBoard[(i*3)] != EMPTY && _gameBoard[(i * 3)] == _gameBoard[(i * 3) + 1]
			&& _gameBoard[(i * 3)] == _gameBoard[(i * 3) + 2])
		{
			return (_gameBoard[i*3] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
		}
		//Vertical Win
		else if (_gameBoard[i] != EMPTY && _gameBoard[i] == _gameBoard[i + 3]
			&& _gameBoard[i] == _gameBoard[i + 6])
		{
			return (_gameBoard[i] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
		}

		//If empty slot found in row, board is not empty
		if (_gameBoard[i] == EMPTY || _gameBoard[i + 3] == EMPTY || _gameBoard[i + 6] == EMPTY)
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

int Game::GetPlayerChoice()
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

void Game::ClearBoard()
{
	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		_gameBoard[i] = EMPTY;
	}
}

