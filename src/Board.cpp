#include "Board.hpp"
#include <iostream>

Board::Board() {
}

Board::~Board() {
}

std::ostream & operator << (std::ostream &out, const Board &c) {
	out << "work in progress: " << c.get(0, 0);
	return out;
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