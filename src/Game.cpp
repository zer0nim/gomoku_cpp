#include "Game.hpp"
#include "players/RealPlayer.hpp"
#include "players/AIPlayer.hpp"

Game::Game() :
	isQuit(false),
	gameInfo{{false, false, false}, 1},
	_loadInProgress(true),
	_finished(false),
	_idPlayerAct(1) {
	_gui = new Gui(*this);
	_board = new MasterBoard(*this);
	_players[0] = new Player(*this, GUI_COLOR_1);
	_players[1] = new Player(*this, GUI_COLOR_2);
}

bool	Game::has_win(int id) {
	if (getPlayer(id).getWinAligned()) {
		std::cout << "Win with " << NB_ALIGNED_VICTORY << " or more stones aligned" << std::endl;
		_finished = true;
	}
	if (getPlayer(id).getNbDestroyedStones() >= NB_DESTROYED_VICTORY) {
		std::cout << "Win because of " << NB_DESTROYED_VICTORY << " stones destroyed" << std::endl;
		_finished = true;
	}
	if (_finished)
		std::cout << "player " << id << " has win" << std::endl;

	return _finished;
}

void	Game::checkWinner() {
	if (!has_win(OP_ST(_idPlayerAct)))
		if (!has_win(_idPlayerAct))
			if (_board->getRemainPlaces() <= 0) {
				std::cout << "Equality ! no winner in this game !" << std::endl;
				_finished = true;
			}

	if (_finished)
		std::cout << *_board << std::endl;
}

void	Game::run() {
	while (!isQuit) {
		if (!_loadInProgress) {
			if (getGui().getGuiType() == GUI_TYPE_MENU) {
			}
			else if (getGui().getGuiType() == GUI_TYPE_GAME) {
				if (!_finished) {
					getPlayerAct().moving();
					nextPlayer();
					checkWinner();
				}
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
	delete _board;
	_board = new MasterBoard(*this);

	// create new player 1
	delete _players[0];
	if (gameInfo.playerAI[1])  // AI
		_players[0] = new AIPlayer(*this, GUI_COLOR_1);
	else  // real
		_players[0] = new RealPlayer(*this, GUI_COLOR_1);

	if (getPlayerActId() == 2)
		nextPlayer();

	// create new player 2
	delete _players[1];
	if (gameInfo.playerAI[2])  // AI
		_players[1] = new AIPlayer(*this, GUI_COLOR_2);
	else  // real
		_players[1] = new RealPlayer(*this, GUI_COLOR_2);

	// set the GUI to game
	getGui().setGuiType(GUI_TYPE_GAME);

	// reset end of the game
	_finished = false;
}

void Game::nextPlayer() {
	_idPlayerAct = OP_ST(_idPlayerAct);
}

void Game::quit() {
	isQuit = true;
}

MasterBoard &Game::getBoard() const { return *_board; }
Gui &Game::getGui() const { return *_gui; }
Player &Game::getPlayer(int id) const { return *_players[id - 1]; }
Player &Game::getPlayerAct() const { return *_players[_idPlayerAct - 1]; }
int Game::getPlayerActId() const { return _idPlayerAct; }

Game::~Game() {
	delete _board;
	delete _gui;
	delete _players[0];
	delete _players[1];
}