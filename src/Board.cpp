#include "Board.hpp"
#include <iostream>

Board::Board() {
	std::cout << "content size: " << _content.size() << std::endl;
	_content[1] = 42;
	std::cout << "_content[1]: " << _content[1] << std::endl;
}

Board::~Board() {
}