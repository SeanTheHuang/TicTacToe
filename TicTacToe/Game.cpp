//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name : Game.cpp
// Description : Implementation of Game class functions
// Author : Sean Huang
// Mail : sean.hua7281@mediadesig.school.nz
//

#include "Game.h"
#include "Draw.h"
#include <conio.h>
#include <time.h>
#include <math.h>

Game::Game()
{
	srand((size_t)time(NULL));	//Randomize numbers	according to current time
}

// Function: StartGame
// Inputs: none
// Output: none
// Task: Start point of the game.
//		 External calls may only use this function to start the game

void Game::StartGame()
{
	_nextState = PROG_MENU;
	ProgramStateMachine();
}

// Function: ProgramStateMachine
// Inputs: none
// Output: none
// Task: Function is used to jump between states of the game
//		 _nextState class variable is used to determine next state to go to

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
			GameVsComputer(COMP_NORMAL);
			break;
		}
		case (PROG_VS_COMPUTER_HARD):
		{
			GameVsComputer(COMP_HARD);
			break;
		}
		default:
			break;
		}
	}
}

// Function: MainMenuState
// Inputs: none
// Output: none
// Task: Menu for player to choose what mode they would like to play
//		 Choices:	Player vs Player
//					Player vs Computer (Normal or Hard)
//					Quit Game
//
//		Choices are made using keyboard inputs

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

// Function: GameTwoPlayers
// Inputs: none
// Output: none
// Task: Player vs player game.
//		 Runs a simulation of tic tac toe

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
		Draw::GoToXY(8, 3);

		if (whosTurn == 0)
			std::cout << "Noughts turn to play!";
		else
			std::cout << "Crosses turn to play!";

		
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
	Draw::GoToXY(7, 3);
	Draw::ChangeDrawColour(COLOUR_YELLOW_ON_BLACK);
	switch (currentGameState)
	{
	case (NOUGHT_WIN):
	{
		std::cout << "GAME OVER: Noughts Wins!   ";
		break;
	}
	case (CROSS_WIN):
	{
		std::cout << "GAME OVER: Crosses Wins!   ";
		break;
	}
	case (DRAW):
	{
		std::cout << "GAME OVER: It's a draw!   ";
		break;
	}
	default:
		break;
	}

	Draw::ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	PostGameUI();
}

// Function: GameVsComputer
// Inputs: difficulty - AI level of the computer player
// Output: none
// Task: Player vs computer game of tic tac toe.
//		 
void Game::GameVsComputer(COMPUPTER_LEVEL difficulty)
{
	Draw::GameUI();
	ClearBoard();

	Draw::GoToXY(7, 3);
	std::cout << "You = O   Computer = X";

	//PLAYER = NOUGHTS
	//COMPUTER = CROSSES
	
	int whosTurn = rand() % 2;
	//whosTurn = 0 <= Noughts turn
	//whosTurn = 1 <= Crosses turn

	GAMEOVER_STATE currentGameState = GAME_NOT_OVER;

	while (currentGameState == GAME_NOT_OVER)
	{
		Draw::CurrentBoardState(_gameBoard);

		if (whosTurn == 0)	//Players turn
		{
			_gameBoard[GetPlayerChoice()] = NOUGHT;
		}
		else	//Computers turn
		{
			if (difficulty == COMP_NORMAL)
				_gameBoard[GetComputerMoveRandom()] = CROSS;
			else
				_gameBoard[GetComputerMoveSmart()] = CROSS;
		}

		//Check for win condition
		currentGameState = CheckGameOver3x3();

		//Switch turns
		whosTurn = (whosTurn+1) % 2;
	}

	//Reach here: End game condition met

	Draw::CurrentBoardState(_gameBoard);
	Draw::ChangeDrawColour(COLOUR_YELLOW_ON_BLACK);
	Draw::GoToXY(7, 3);

	switch (currentGameState)
	{
	case (NOUGHT_WIN):	//Player won
	{
		std::cout << "Nice! You bet the computer!!         ";
		break;
	}
	case (CROSS_WIN):	//Computer won
	{
		std::cout << "Computer wins. Better luck next time!";
		break;
	}
	case (DRAW):		//No winnner
	{
		std::cout << "Wow! It's a draw!                ";
		break;
	}
	default:
		break;
	}
	Draw::ChangeDrawColour(COLOUR_WHITE_ON_BLACK);

	PostGameUI();
}

// Function: CheckGameOver3x3
// Inputs: none
// Output: GAMEOVER_STATE = State of the game current board (i.e. if a player has won)
// Task: Checks the _gameBoard class array to see if a winner is found
//		 Function also checks if the game ends in a draw

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
		&& _gameBoard[2] == _gameBoard[6])
	{
		return (_gameBoard[2] == NOUGHT) ? NOUGHT_WIN : CROSS_WIN;
	}

	if (!boardIsFull)
		return GAME_NOT_OVER;

	//Reach here: Board is full and no winner
	return DRAW;
}

// Function: GetsPlayerChoice
// Inputs: none
// Output: int - index of tile which player has confirmed to play
// Task: Gets which tile the player wants to play on
//		 Function uses keyboard inputs to move around board and
//		 The enter key to confirm their choice.
//		 Only empty tiles are accepted as possible choices

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

// Function: GetComputerMoveRandom
// Inputs: none
// Output: int - index of tile which computer is playing
// Task: Randomly pick a free tile to play on

int Game::GetComputerMoveRandom()
{
	int newMove = 0;
	int randRange = BOARD_SIZE * BOARD_SIZE;

	//Sanity check: There is a possible move, else return -1
	bool boardIsFull = true;
	for (size_t i = 0; i < randRange; i++)
	{
		if (_gameBoard[i] == EMPTY)
			boardIsFull = false;
	}

	if (boardIsFull)
	{
		return -1;
	}
		

	//Begin randomizing next move

	while (true)
	{
		newMove = rand() % randRange;

		if (_gameBoard[newMove] == EMPTY)
		{
			break;
		}
	}

	return newMove;
}

// Function: GetComputerMoveSmart
// Inputs: none
// Output: int - index of tile computer is playing on in a smart way.
// Task: Start point of the minimax algorithm to figure out where to play next.

int Game::GetComputerMoveSmart()
{
	return MiniMaxAlgorithm(-1000, 1000, 0, true);
}

// Function: ClearBoard
// Inputs: none
// Output: none
// Task: Set all values in _gameBoard array to empty (clear the board)

void Game::ClearBoard()
{
	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		_gameBoard[i] = EMPTY;
	}
}

// Function: PostGameUI
// Inputs: none
// Output: none
// Task: Call after a game ends. Asks user if they want to play again
//		 or quit back to main menu. Uses keyboard input to get user option

void Game::PostGameUI()
{
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
		case ('1'):	//User play again
		{
			validInput = true;
			break;
		}
		case ('2'):	//User quit to main menu
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

// Function: MiniMaxAlgorithm
// Inputs: alpha & beta - Used for alphabeta pruning
//		   depth - Used to figure out when to return the best move
//		   goingForMax - Used to figure out if we want to maximise or minimise outcome.
//
// Output: int - Returns best move if depth = 0 else, returns alpha/beta value used for alphabeta pruning
// Task: Uses Minimax algorithm with alphabeta pruning to find best move to play.

int Game::MiniMaxAlgorithm(int alpha, int beta, int depth, bool goingForMax)
{
	//Check end game states
	GAMEOVER_STATE state = CheckGameOver3x3();

	switch (state)
	{
	case (CROSS_WIN):	//Computer win
	{
		return 10;
		break;
	}
	case (NOUGHT_WIN):	//Player win
	{
		return -10;
		break;
	}
	case (DRAW):		//No winner
	{
		return 0;
		break;
	}
	default:
		break;
	}

	//Reach here: Game is not over

	//Variable for best move
	int bestMove = -1;

	//Loop through each tile and call recursively
	for (size_t i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		if (_gameBoard[i] == EMPTY)
		{
			if (goingForMax)	//Going for max score
			{
				_gameBoard[i] = CROSS;
				int temp = MiniMaxAlgorithm(alpha, beta, depth+1, !goingForMax);

				if (temp > alpha)
				{
					bestMove = i;	//Remember current best move for computer
					alpha = temp;

					if (alpha >= beta)
					{
						_gameBoard[i] = EMPTY;

						if (depth == 0)
							return bestMove;

						return alpha;
					}
				}
				

				_gameBoard[i] = EMPTY;
				 
			}
			else				//Going for min score
			{
				_gameBoard[i] = NOUGHT;
				int temp = MiniMaxAlgorithm(alpha, beta, depth + 1, !goingForMax);

				if (temp < beta)
				{
					beta = temp;

					if (alpha >= beta)
					{
						_gameBoard[i] = EMPTY;

						return beta;
					}
				}

				_gameBoard[i] = EMPTY;
			}
		}
	}

	//Reach here: No pruning occured
	if (goingForMax)
	{
		if (depth == 0)
			return bestMove;

		return alpha;
	}
	else
	{
		return beta;
	}
}

