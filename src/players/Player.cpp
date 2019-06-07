#include "players/Player.hpp"
#include "Game.hpp"

Player::Player(Game &_game, int _color) :
	game(_game),
	color(_color),
	_timeLastMove(0),
	_nbDestroyedStones(0) {
}

Player::~Player() {
}

void Player::moving() {
	auto startTime = std::chrono::system_clock::now();
	move();
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> execTime = endTime - startTime;
	_timeLastMove = execTime.count();
}

void Player::move() {
	std::cout << "base move" << std::endl;
}

void Player::click(int x, int y) {
	clickedPos[0] = x;
	clickedPos[1] = y;
}

int		Player::getColor() const { return color; }
void	Player::incrNbDestroyedStones() { ++_nbDestroyedStones; }
int		Player::getNbDestroyedStones() const { return _nbDestroyedStones; }
double	Player::getTimeLastMove() const { return _timeLastMove; }
std::string Player::getType() const { return "Player"; }
