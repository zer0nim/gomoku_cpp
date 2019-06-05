#include "Board.hpp"
#include <iostream>
#include <string>

Board::Board() {
}

Board::~Board() {
}

int Board::get(int x, int y) const {
	return GET_ST(_content, x, y);
}
void Board::set(int x, int y, int stone) {
	SET_ST(_content, x, y, stone);
}
bool Board::isEmpty(int x, int y) const {
	return GET_ST(_content, x, y) == 0;
}
bool Board::isStone(int x, int y, int stone) const {
	return static_cast<int>(GET_ST(_content, x, y)) == stone;
}

// print the board (with colors)
std::ostream & operator << (std::ostream &out, const Board &c) {
	// std::array<std::string, 2> color;

	// out << '*';
	// for (int i = 0; i < BOARD_SZ; ++i)
	// 	out << "---";
	// out << '*' << std::endl;
	// for (int y = 0; y < BOARD_SZ; ++y) {
	// 	out << '|';
	// 	for (int x = 0; x < BOARD_SZ; ++x) {
	// 		color = {C_EOC, C_EOC};
	// 		if (c.get(x, y) == 1)
	// 			color = {C_WHITE, C_F_WHITE};
	// 		else if (c.get(x, y) == 2)
	// 			color = {C_RED, C_F_RED};
	// 		out << color[0] + color[1] + " . " + C_EOC;
	// 	}
	// 	out << "|" << std::endl;
	// }
	// out << '*';
	// for (int i = 0; i < BOARD_SZ; ++i)
	// 	out << "---";
	// out << '*' << std::endl;

	// return out;
}

MasterBoard::MasterBoard() : Board() {
	for (int x=0; x < BOARD_SZ; x++) {
		for (int y=0; y < BOARD_SZ; y++) {
			setIsWin(x, y, false);
		}
	}
}

void MasterBoard::setIsWin(int x, int y, bool val) {
	_isWin[y][x] = val;
}
bool MasterBoard::getIsWin(int x, int y) {
	return _isWin[y][x];
}
