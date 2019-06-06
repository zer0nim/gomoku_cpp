#include "players/Player.hpp"
#include "Game.hpp"

Player::Player(Game &_game, int _color) : game(_game), color(_color) {
}

Player::~Player() {
}

void Player::move() {
	std::cout << "base move" << std::endl;
}

void Player::click(int x, int y) {
	clickedPos[0] = x;
	clickedPos[1] = y;
}

int Player::getColor() const {
	return color;
}