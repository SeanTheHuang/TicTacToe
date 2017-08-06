#pragma once

#include "Draw.h"

#define BOARD_SIZE 3

//Key Codes
const int KEY_DOWN = 80;
const int KEY_UP = 72;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ENTER = 13;

enum TILE_STATE
{
	NO_STATE = -1,
	EMPTY,
	NOUGHT,
	CROSS
};

enum GAME_OVER_STATES
{
	GAME_NOT_OVER = -1,
	NOUGHT_WIN,
	CROSS_WIN,
	DRAW
};

class Game
{

public:
	Game();
	~Game() = default;
	
	void StartGame();
	

private:
	TILE_STATE _gameBoard[BOARD_SIZE*BOARD_SIZE];

	void MainMenuState();
	void GameTwoPlayers();
	void GameVsNormalBot();
	void GameVsHardBot();

	GAME_OVER_STATES checkGameOver3x3();
	int getPlayerChoice();

};