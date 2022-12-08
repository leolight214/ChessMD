#include "chessmd_piece.h"
#include <iostream>
Piece::Piece() {
	moved = false;
	color = PCOL::NONE;
	type = PTYPE::NONE;
	initBoolMatrix(move_path);
}

Piece::~Piece() {
	if (move_path) {
		for(int i=0;i<8;i++)
			if(move_path[i])
				free(move_path[i]);
		free(move_path);
	}
}

void CreatePiece(Piece* p, PTYPE type) {
	switch (type) {
	case PTYPE::PAWN:
		*p = *dynamic_cast<Piece*>(new Pawn);
		break;
	case PTYPE::ROOK:
		*p = *dynamic_cast<Piece*>(new Rook);
		break;
	case PTYPE::BISHOP:
		*p = *dynamic_cast<Piece*>(new Bishop);
		break;
	case PTYPE::KNIGHT:
		*p = *dynamic_cast<Piece*>(new Knight);
		break;
	case PTYPE::QUEEN:
		*p = *dynamic_cast<Piece*>(new Queen);
		break;
	case PTYPE::KING:
		*p = *dynamic_cast<Piece*>(new King);
		break;
	case PTYPE::NONE:
		if (p == nullptr)
			p = new Piece();
		break;
	default:
		break;
	}
}

bool Piece::isEnemy(PCOL col) {
	if (this->color == PCOL::NONE)
		return false;
	if ((short)this->color - (short)col != 0)
		return true;
	return false;
}

bool** Piece::Movement(Position pos) {
	bool** selection = nullptr;
	initBoolMatrix(selection);

	return selection;
}

/*
bool** Pawn::Movement(Piece** board, Position pos) {
	int mod = (board[pos.x][pos.y].p->color == PCOL::BLACK) ? -1 : 1; //modifier for Black side (reversed) 
	short int x, y;
	x = pos.x;
	char move_mod = moved ? 1 : 2;
	for (int i = 0; i < move_mod; i++) {
		y = pos.y + (i * mod);
		if (y >= 8 || y < 0)
			break;
		else if (board[x][y].p->color == PCOL::NONE) { //set available path
			movePath[x][y] = true;
		}
	}
	if (withinBounds(x + 1, y + mod)) //X,Y within bounds
		movePath[x + 1][y + mod] = (isEnemy(board[x + 1][y + mod].p->color)) ? true : false;
	return movePath;
};
*/
Pawn::Pawn() {
	type = PTYPE::PAWN;
	initBoolMatrix(move_path);
};

bool** Pawn::Movement(Position pos) {
	int mod = (this->color == PCOL::BLACK) ? -1 : 1;
	bool** path = nullptr;
	initBoolMatrix(path);
	for (int i = 1;i <= this->moved ? 1 : 2;i++) {
		if (withinBounds(pos.x,pos.y + (i * mod))){
			path[pos.x][pos.y + (i * mod)] = true;
		}
	}
	return path;
}

Rook::Rook() {
	type = PTYPE::ROOK;
	initBoolMatrix(move_path);
};

Knight::Knight() {
	type = PTYPE::KNIGHT;
	initBoolMatrix(move_path);
};

Bishop::Bishop() {
	type = PTYPE::BISHOP;
	initBoolMatrix(move_path);
};

King::King() {
	type = PTYPE::KING;
	initBoolMatrix(move_path);
};

Queen::Queen() {
	type = PTYPE::QUEEN;
	initBoolMatrix(move_path);
};

Pawn::~Pawn() {};
Rook::~Rook() {};
Knight::~Knight() {};
Bishop::~Bishop() {};
King::~King() {};
Queen::~Queen() {};