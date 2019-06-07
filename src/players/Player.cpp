#include "players/Player.hpp"
#include "Game.hpp"

Player::Player(Game &game, int color) :
  game(game),
  _color(color),
  _nbDestroyedStones(0),
  _winAligned(false) {
}

Player::~Player() {
}

void Player::move() {
	std::cout << "base move" << std::endl;
}

void Player::click(int x, int y) {
	_clickedPos[0] = x;
	_clickedPos[1] = y;
}

void	Player::setWinAligned() {
	_winAligned = true;
}

int Player::getColor() const {
	return _color;
}
void	Player::incrNbDestroyedStones() { ++_nbDestroyedStones; }
int		Player::getNbDestroyedStones() const { return _nbDestroyedStones; }
