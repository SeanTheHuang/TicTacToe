//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name : Game.h
// Description : Plays a simulation of Tic-Tac-Toe
//				 User can play vs: Other players, & normal/hard AI
// Author : Sean Huang
// Mail : sean.hua7281@mediadesig.school.nz
//

#pragma once

#include "Draw.h"

#define BOARD_SIZE 3	//Width & Height of the board

//Key Codes - Used to process keyboard input
const int KEY_DOWN = 80;
const int KEY_UP = 72;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ENTER = 13;

enum TILE_STATE	//State of a tile on the board
{
	NO_STATE = -1,
	EMPTY,
	NOUGHT,
	CROSS
};

enum PROGRAM_STATE	//Runtime state of the program, used by state machine
{
	PROG_NONE = -1,
	PROG_MENU,
	PROG_VS_PLAYER,
	PROG_VS_COMPUTER_NORMAL,
	PROG_VS_COMPUTER_HARD,
	PROG_EXIT
};

enum GAMEOVER_STATE	//Different states of a game of tic-tac-toe
{
	GAME_NOT_OVER = -1,
	NOUGHT_WIN,
	CROSS_WIN,
	DRAW
};

enum COMPUPTER_LEVEL //Variety of AI opponent difficulties
{
	NO_LEVEL = -1,
	COMP_NORMAL,
	COMP_HARD
};

class Game
{

public:
	Game();
	~Game() = default;
	
	void StartGame();
	

private:
	TILE_STATE _gameBoard[BOARD_SIZE*BOARD_SIZE];
	PROGRAM_STATE _nextState;

	void ProgramStateMachine();

	void MainMenuState();
	void GameTwoPlayers();
	void GameVsComputer(COMPUPTER_LEVEL);

	GAMEOVER_STATE CheckGameOver3x3();
	int GetPlayerChoice();
	int GetComputerMoveRandom();
	int GetComputerMoveSmart();
	void ClearBoard();
	void PostGameUI();

	int MiniMaxAlgorithm(int alpha, int beta, int depth, bool goingForMax);

};