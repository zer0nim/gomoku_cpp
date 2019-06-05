#include <iostream>
#include "Board.hpp"

int main(void) {
	Board board;
	std::cout << std::endl;

	std::cout << "stone: " << board.get(10, 10) << std::endl;
	std::cout << "isEmpty: " << board.isEmpty(10, 10) << std::endl;
	std::cout << "isStone: " << board.isStone(10, 10, 2) << std::endl;
	board.set(10, 10, 2);
	std::cout << "stone: " << board.get(10, 10) << std::endl;
	std::cout << "isEmpty: " << board.isEmpty(10, 10) << std::endl;
	std::cout << "isStone: " << board.isStone(10, 10, 2) << std::endl;
	return 0;
}
