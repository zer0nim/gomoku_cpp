#include "Game.hpp"
#include "players/RealPlayer.hpp"

Game::Game() {
	board = new MasterBoard(*this);
	gui = new Gui(*this);
	isQuit = false;
	_idPlayerAct = 1;
	players[0] = new RealPlayer(*this, GUI_COLOR_1);
	players[1] = new RealPlayer(*this, GUI_COLOR_2);
}

void Game::run() {
	while (!isQuit) {
		getPlayerAct().moving();
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

MasterBoard &Game::getBoard() const {
	return *board;
}
Gui &Game::getGui() const {
	return *gui;
}
Player &Game::getPlayer(int id) const {
	return *players[id - 1];
}
Player &Game::getPlayerAct() const {
	return *players[_idPlayerAct - 1];
}
int Game::getPlayerActId() const {
	return _idPlayerAct;
}

Game::~Game() {
	delete board;
	delete gui;
	delete players[0];
	delete players[1];
}