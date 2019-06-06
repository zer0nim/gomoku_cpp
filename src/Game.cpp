#include "Game.hpp"
#include "players/RealPlayer.hpp"

Game::Game() {
	board = new MasterBoard(*this);
	gui = new Gui(this);
	isQuit = false;
	_idPlayerAct = 1;
	players[0] = new RealPlayer(*this);
	players[1] = new RealPlayer(*this);
}

void Game::run() {
	while (!isQuit) {
		getPlayerAct().move();
		nextPlayer();
	}
}

void Game::nextPlayer() {
	if (_idPlayerAct == 1)
		_idPlayerAct = 2;
	else
		_idPlayerAct = 1;
}

void Game::quit() {
	isQuit = true;
}

Player &Game::getPlayer(int id) {
	return *(players[id - 1]);
}
Player &Game::getPlayerAct() {
	return *(players[_idPlayerAct - 1]);
}
int Game::getPlayerActId() {
	return _idPlayerAct;
}

Game::~Game() {
}