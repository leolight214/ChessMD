﻿
#ifndef CHESSMD_H
#define CHESSMD_H
#include <string>
#include <iostream>
#include "chessmd_piece.h"
#include "chessmd_utilities.h"

class ChessMD {
private:
	bool _running;
	bool _game;
	PCOL turn;
	PCOL checked;
	PCOL winner;
	Piece* board[8][8];
	Piece* king_white;
	Piece* king_black;
	bool (*boardSel)[8] = nullptr; //board current piece selection
	bool whiteChecked[8][8]; //white checked territory
	bool blackChecked[8][8]; //black checked territory
	void initBoard(Piece* (&)[8][8]);
	void initGame(Piece* (&)[8][8]);
	void initBoardPlacement(Piece* (&)[8][8]);
	std::string handleEvent();
	std::string lastError;
	Piece* pSel = nullptr;
	Position stringToPosition(std::string);
	bool parseEvent(std::string);
	PCOL updateSelection();
	void addMatrix(bool(*source)[8], bool(*target)[8]);
	bool isPlayValid(Position source, Position dest);
	void Play(Position source, Position dest);
	void updateEnPassant();

public:
	ChessMD();
	~ChessMD();
	bool getRunning();
	void update(std::string event);
	Piece_Matrix getBoard();
	Piece const* getSelected();
	PCOL getWinner();
	bool isNotEmpty(char x, char y);
	Piece* getChecked();
	std::string getLastError();
	void debug(); //use for debugging, remove after program finish
};

#endif
