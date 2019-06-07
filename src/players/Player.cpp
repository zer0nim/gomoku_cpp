#include "players/Player.hpp"
#include "Game.hpp"

Player::Player(Game &_game, int _color) :
  game(_game),
  color(_color),
	_nbDestroyedStones(0) {
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
void	Player::incrNbDestroyedStones() { ++_nbDestroyedStones; }
int		Player::getNbDestroyedStones() const { return _nbDestroyedStones; }
