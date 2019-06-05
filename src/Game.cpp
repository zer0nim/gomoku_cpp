#include "Game.hpp"
#include "players/RealPlayer.hpp"

Game::Game() {
	board = new MasterBoard();
	gui = new Gui(this);
	_isQuit = false;
	_idPlayerAct = 1;
	players[0] = new RealPlayer();
	players[1] = new RealPlayer();
}

void Game::run() {
	while (!_isQuit) {
		getPlayerAct()->move();
	}
}

void Game::quit() {
	_isQuit = true;
}

Player *Game::getPlayer(int id) {
	return players[id - 1];
}
Player *Game::getPlayerAct() {
	return players[_idPlayerAct];
}
int Game::getPlayerActId() {
	return _idPlayerAct;
}

Game::~Game() {
}