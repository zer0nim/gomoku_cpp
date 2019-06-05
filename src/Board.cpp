#include "Board.hpp"
#include <iostream>

Board::Board() {
	std::cout << "content size: " << _content.size() << std::endl;
	std::cout << "__SET_ST( 0 ) to 0:0=> stone: ";
	SET_ST(_content, 1, 1, 0);
	std::cout << GET_ST(_content, 1, 1) << std::endl;

	std::cout << "__SET_ST( 1 ) to 0:0=> stone: ";
	SET_ST(_content, 1, 1, 1);
	std::cout << GET_ST(_content, 1, 1) << std::endl;

	std::cout << "__SET_ST( 2 ) to 0:0=> stone: ";
	SET_ST(_content, 1, 1, 2);
	std::cout << GET_ST(_content, 1, 1) << std::endl;
	std::cout << std::endl;


	std::cout << "__SET_ST( 0 ) to 18:5=> stone: ";
	SET_ST(_content, 18, 5, 0);
	std::cout << GET_ST(_content, 18, 5) << std::endl;

	std::cout << "__SET_ST( 1 ) to 18:5=> stone: ";
	SET_ST(_content, 18, 5, 1);
	std::cout << GET_ST(_content, 18, 5) << std::endl;

	std::cout << "__SET_ST( 2 ) to 18:5=> stone: ";
	SET_ST(_content, 18, 5, 2);
	std::cout << GET_ST(_content, 18, 5) << std::endl;
	std::cout << std::endl;


	std::cout << "test vulnerability__________________________" << std::endl;
	std::cout << std::endl;


	std::cout << "__SET_VUL( 0 ) to 18:5=> vuln: ";
	SET_VUL(_content, 18, 5, 0);
	std::cout << GET_VUL(_content, 18, 5) << ", stone: " << GET_ST(_content, 18, 5) << std::endl;

	std::cout << "__SET_VUL( 1 ) to 18:5=> vuln: ";
	SET_VUL(_content, 18, 5, 1);
	std::cout << GET_VUL(_content, 18, 5) << ", stone: " << GET_ST(_content, 18, 5) << std::endl;

	std::cout << "__SET_VUL( 0 ) to 18:5=> vuln: ";
	SET_VUL(_content, 18, 5, 0);
	std::cout << GET_VUL(_content, 18, 5) << ", stone: " << GET_ST(_content, 18, 5) << std::endl;
}

Board::~Board() {
}