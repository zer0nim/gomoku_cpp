#include "players/Player.hpp"
#include "Game.hpp"
#include <chrono>

Player::Player(Game &game, int color) :
	game(game),
	_color(color),
	_clickedPos{-1, -1},
	_spacePressed(false),
	_timeLastMove(0),
	_nbDestroyedStones(0),
	_nbStones(0),
	_winAligned(false),
	_isWinner(false) {
}

Player::~Player() {
}

void Player::moving() {
	auto startTime = std::chrono::system_clock::now();
	std::array<int, 2> movingPos = move();
	if (movingPos[0] == -1)
		return;
	else {
		game.getBoard().resetIsDestroyed();
		game.getBoard().putStone(movingPos[0], movingPos[1], game.getPlayerActId());
	}
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> execTime = endTime - startTime;
	_timeLastMove = execTime.count();
}

std::array<int, 2> Player::move() {
	std::cout << "base move" << std::endl;
	return {{-1, -1}};
}

void Player::click(int x, int y) {
	_clickedPos[0] = x;
	_clickedPos[1] = y;
}
void Player::setSpacePressed(bool pressed) { _spacePressed = pressed; }


void	Player::setWinAligned() {
	_winAligned = true;
}
void	Player::setWinner(bool win) {
	_isWinner = win;
}

uint	Player::getColor() const { return _color; }
void	Player::incrNbDestroyedStones() { ++_nbDestroyedStones; }
int		Player::getNbDestroyedStones() const { return _nbDestroyedStones; }
double	Player::getTimeLastMove() const { return _timeLastMove; }
std::string Player::getType() const { return "Player"; }
void	Player::incrNbStones() {
	_nbStones = _nbStones + 1 < BOARD_SZ*BOARD_SZ ? _nbStones + 1 : BOARD_SZ*BOARD_SZ;
}
void	Player::decrNbStones() {
	_nbStones = _nbStones - 1 > 0 ? _nbStones - 1 : 0;
}
int		Player::getNbStones() const { return _nbStones; }
bool	Player::getWinAligned() const { return _winAligned; }
bool	Player::isWinner() const { return _isWinner ; }
