#ifndef NODE_HPP
#define NODE_HPP

#include "Board.hpp"

class Node {
	public:
		Node(Game &_game, Board &_board);

		Game &game;
		Board &board;
		int heuristic;
		bool isWin;
};

#endif