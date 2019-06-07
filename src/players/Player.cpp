#include "players/Player.hpp"
#include "Game.hpp"

Player::Player(Game &game)
: _game(game), _nbDestroyedStones(0), _winAligned(false) {
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

void	Player::setWinAligned() {
	_winAligned = true;
}

void	Player::incrNbDestroyedStones() { ++_nbDestroyedStones; }
int		Player::getNbDestroyedStones() const { return _nbDestroyedStones; }
