#include "chessmd_render.h"
#include "chessmd.h"
#include <iostream>
#include <string>

ChessMD_Render::ChessMD_Render() {

}

ChessMD_Render::~ChessMD_Render() {

}

void ChessMD_Render::setPos(COORD coord) {
	SetConsoleCursorPosition(hout, coord);
}

void ChessMD_Render::setColor(COLOR bg, COLOR fg) {
	SetConsoleTextAttribute(hout, ((int)bg * 16) + (int)fg);
}

void ChessMD_Render::cls(HANDLE hout) {
	setColor(COLOR::BLACK, COLOR::BLACK);
	if (hout == INVALID_HANDLE_VALUE) return;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, PieceCount;
	COORD homeCoords = { 0,0 };
	if (!GetConsoleScreenBufferInfo(hout, &csbi)) return;
	PieceCount = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hout, (TCHAR)' ', PieceCount, homeCoords, &count)) return;
	if (!FillConsoleOutputAttribute(hout, csbi.wAttributes, PieceCount, homeCoords, &count)) return;
	setPos({ 0,0 });
	setColor(COLOR::BLACK, COLOR::WHITE);
}

int ChessMD_Render::PieceCenter(int c) {
	return c * BOARD_SIZE + (BOARD_SIZE / 2);
}

void ChessMD_Render::render(ChessMD game) {
	cls(hout);
	char pLetters[8] = { ' ','P','R','H','B','K','Q' };
	int iPiece, jPiece;
	COLOR colors_board[2] = { COLOR::LGRAY, COLOR::GRAY };
	COLOR colors_selected_move[2] = { COLOR::LYELLOW, COLOR::YELLOW };
	COLOR colors_selected_target[2] = { COLOR::LAQUA, COLOR::AQUA };
	COLOR* colors_arr;
	Piece const* selected = game.getSelected();
	//Board Render
	for (int i = 0; i < (BOARD_SIZE*8); i++) {
		for (int j = 0; j < (BOARD_SIZE*8); j++){
			iPiece = (int)((i / BOARD_SIZE));
			jPiece = (int)((j / BOARD_SIZE));
			COLOR col = COLOR::BLACK;
			colors_arr = colors_board;
			if (game.getBoard()[iPiece][jPiece]) {
				switch (game.getBoard()[iPiece][jPiece]->color) {
				case PCOL::WHITE:
					col = COLOR::LBLUE;
					break;
				case PCOL::BLACK:
					col = COLOR::LRED;
					break;
				}
			}
			if (selected) {
				if (selected->move_path[iPiece][jPiece]) {
					colors_arr = colors_selected_move;
				}
			}
			if (game.getSelected() && game.getBoard()[iPiece][jPiece] == game.getSelected()) {
				colors_arr = colors_selected_target;
			}
			setPos({ (short)j,(short)i });
			if ((iPiece+jPiece) % 2 ==0) {
				setColor(colors_arr[0], col);
			}
			else {
				setColor(colors_arr[1], col);
			}
			int pval = 0;
			if (i == PieceCenter(iPiece) && j == PieceCenter(jPiece)){
				if (game.getBoard()[iPiece][jPiece])
					pval = (int)game.getBoard()[iPiece][jPiece]->type;
			}
			std::cout << pLetters[pval];
		}
	}
	//Board Letters
	setColor(COLOR::BLACK, COLOR::WHITE);
	for (int x = 0;x < 8;x++) {
		setPos({ (short)PieceCenter(x), (BOARD_SIZE*8) });
		std::cout << (char)('a' + x);
	}
	for (int y = 0;y < 8;y++) {
		setPos({(BOARD_SIZE * 8) + 1,(short)PieceCenter(y)});
		std::cout << 8-y;
	}
	
	//Error Message
	setPos({ 0,(BOARD_SIZE * 8) + 4 });
	setColor(COLOR::BLACK, COLOR::LRED);
	std::cout << game.getLastError();

	//Command
	setPos({ 0,(BOARD_SIZE * 8) + 3 });
	setColor(COLOR::BLACK, COLOR::WHITE);
	std::cout << "COMMAND: ";
}

void ChessMD_Render::initWindow() {
	SetConsoleTitleW(TITLE);
}

void ChessMD_Render::debug_render(ChessMD game) {
	char pLetters[8] = { ' ','P','R','H','B','K','Q' };
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++) {
			std::cout << game.getSelected()->move_path[i][j];
		}
		std::cout << std::endl;
	}
}