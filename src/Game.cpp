#include "Game.hpp"
#include "players/RealPlayer.hpp"
#include "players/AIPlayer.hpp"

Game::Game() :
	isQuit(false),
	gameInfo{{false, false, false}, 1},
	_loadInProgress(true),
	_idPlayerAct(1) {
	gui = new Gui(*this);
	board = new MasterBoard(*this);
	players[0] = new Player(*this, GUI_COLOR_1);
	players[1] = new Player(*this, GUI_COLOR_2);
}

void Game::run() {
	while (!isQuit) {
		if (!_loadInProgress) {
			if (getGui().getGuiType() == GUI_TYPE_MENU) {
			}
			else if (getGui().getGuiType() == GUI_TYPE_GAME) {
				getPlayerAct().moving();
				nextPlayer();
			}
		}
		if (!(getGui().getGuiType() == GUI_TYPE_LOADING)) {
			_loadInProgress = false;
		}
	}
}

void Game::startMenu() {
	// set GUI to loading mode
	getGui().setGuiType(GUI_TYPE_LOADING);
	_loadInProgress = true;

	// while (_loadInProgress);

	// set GUI to menu
	getGui().setGuiType(GUI_TYPE_MENU);
}

void Game::startGame() {
	// set GUI to loading mode
	getGui().setGuiType(GUI_TYPE_LOADING);
	_loadInProgress = true;

	// create new board
	delete board;
	board = new MasterBoard(*this);

	// create new player 1
	delete players[0];
	if (gameInfo.playerAI[1])  // AI
		players[0] = new AIPlayer(*this, GUI_COLOR_1);
	else  // real
		players[0] = new RealPlayer(*this, GUI_COLOR_1);

	if (getPlayerActId() == 2)
		nextPlayer();

	// create new player 2
	delete players[1];
	if (gameInfo.playerAI[2])  // AI
		players[1] = new AIPlayer(*this, GUI_COLOR_2);
	else  // real
		players[1] = new RealPlayer(*this, GUI_COLOR_2);

	// set the GUI to game
	getGui().setGuiType(GUI_TYPE_GAME);
}

void Game::nextPlayer() {
	_idPlayerAct = OP_ST(_idPlayerAct);
}

void Game::quit() {
	isQuit = true;
}

MasterBoard &Game::getBoard() const { return *board; }
Gui &Game::getGui() const { return *gui; }
Player &Game::getPlayer(int id) const { return *players[id - 1]; }
Player &Game::getPlayerAct() const { return *players[_idPlayerAct - 1]; }
int Game::getPlayerActId() const { return _idPlayerAct; }

Game::~Game() {
	delete board;
	delete gui;
	delete players[0];
	delete players[1];
}