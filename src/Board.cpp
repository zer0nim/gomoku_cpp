#include "Board.hpp"
#include <iostream>
#include <string>

Board::Board() {
	_lastStone[0] = 0;
	_lastStone[1] = 0;
}

Board::~Board() {
}

int Board::get(int x, int y) const {
	return GET_ST(_content, x, y);
}
void Board::set(int x, int y, int stone) {
	SET_ST(_content, x, y, stone);
	_lastStone[0] = x;
	_lastStone[1] = y;
}
bool Board::isEmpty(int x, int y) const {
	return GET_ST(_content, x, y) == 0;
}
bool Board::isStone(int x, int y, int stone) const {
	return static_cast<int>(GET_ST(_content, x, y)) == stone;
}
bool Board::isLastStone(int x, int y) {
	return (x == _lastStone[0] && y == _lastStone[1]);
}

// print the board (with colors)
std::ostream & operator << (std::ostream &out, const Board &c) {
	(void)c;
	return out;
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
}

void MasterBoard::setIsWin(int x, int y, bool val) {
	_isWin[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y, int val) {
	_markerColor[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y) {
	setMarkerColor(x, y, -1);
}
void MasterBoard::setMarkerTxt(int x, int y, std::string txt, int color) {
	_markerTxt[y][x].txt = txt;
	_markerTxt[y][x].color = color;
}
void MasterBoard::setMarkerTxt(int x, int y, std::string txt) {
	setMarkerTxt(x, y, txt, 0xFFFFFFFF);
}
void MasterBoard::setMarkerTxt(int x, int y) {
	setMarkerTxt(x, y, 0, 0);
}
bool MasterBoard::getIsWin(int x, int y) {
	return _isWin[y][x];
}
int MasterBoard::getMarkerColor(int x, int y) {
	return _markerColor[y][x];
}
struct markerTxt MasterBoard::getMarkerTxt(int x, int y) {
	return _markerTxt[y][x];
}
