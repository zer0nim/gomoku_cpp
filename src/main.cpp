#include <iostream>
#include "Board.hpp"

int main(void) {
	Board board;

	std::cout << std::endl;
	board.set(10, 10, 2);
	board.set(0, 0, 1);

	std::cout << board << std::endl;

	return 0;
}
