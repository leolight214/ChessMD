#include "chessmd_utilities.h"
#ifndef CHESSMD_PIECE_H
#define CHESSMD_PIECE_H

class Piece {
public:
	PCOL color;
	PTYPE type;
	Piece();
	virtual ~Piece() = default;
	bool move_path[8][8];
	virtual Bool_Matrix Movement(Piece* (&Piece_Matrix)[8][8], Position);
	bool isEnemy(PCOL col);
	bool moved = false;
};

typedef Piece* (&Piece_Matrix)[8][8];
void CreatePiece(Piece* &p, PTYPE type = PTYPE::NONE);

class Pawn : public Piece {
public:
	Pawn();
	virtual ~Pawn() = default;
	virtual Bool_Matrix Movement(Piece* (&Piece_Matrix)[8][8], Position);
};

class Rook : public Piece {
public:
	Rook();
	virtual ~Rook() = default;
};

class Knight : public Piece {
public:
	Knight();
	virtual ~Knight() = default;
};

class Bishop : public Piece {
public:
	Bishop();
	virtual ~Bishop() = default;
};

class King : public Piece {
public:
	King();
	virtual ~King() = default;
};

class Queen : public Piece {
public:
	Queen();
	virtual ~Queen() = default;
};



#endif