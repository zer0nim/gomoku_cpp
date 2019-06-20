#include <unistd.h>
#include "Game.hpp"
#include "players/RealPlayer.hpp"
#include "players/AIPlayer.hpp"
#include "players/HybridePlayer.hpp"

Game::Game() :
	isQuit(false),
	gameInfo{{-1, PLAYER1_TYPE, PLAYER2_TYPE}, 0, SPACE_BEFORE_AI_MOVE},
	_loadInProgress(true),
	_finished(false),
	_idPlayerAct(1) {
	_gui = new Gui(*this);
	_board = new MasterBoard(*this);
	_players[0] = new Player(*this, GUI_COLOR_1);
	_players[1] = new Player(*this, GUI_COLOR_2);
	_heuristic = new Heuristic(*this);
	gameInfo.difficulty = getHeuristic().getDifficulty();
}

bool	Game::has_win(int id) {
	if (getPlayer(id).getWinAligned()) {
		for (int x=0; x < BOARD_SZ; x++)
			for (int y=0; y < BOARD_SZ; y++)
				if (getBoard().get(x, y) == OP_ST(id))
					getBoard().setIsWin(x, y, false);  // disable win for the other player
		std::cout << "Win with " << NB_ALIGNED_VICTORY << " or more stones aligned" << std::endl;
		_finished = true;
	}
	if (getPlayer(id).getNbDestroyedStones() >= NB_DESTROYED_VICTORY) {
		for (int x=0; x < BOARD_SZ; x++)
			for (int y=0; y < BOARD_SZ; y++)
				if (getBoard().get(x, y) == getPlayerActId())
					getBoard().setIsWin(x, y, true);
		std::cout << "Win because of " << NB_DESTROYED_VICTORY << " stones destroyed" << std::endl;
		_finished = true;
	}
	if (_finished) {
		getPlayer(id).setWinner(true);
		std::cout << "player " << id << " has win" << std::endl;
	}

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
			if (getGui().getGuiType() == GUI_TYPE_GAME) {
				if (!_finished) {
					getPlayerAct().moving();
					checkWinner();
					nextPlayer();
				}
			}
		}
		_loadInProgress = false;
	}
}

void Game::startMenu() {
	// set GUI to loading mode
	getGui().setGuiType(GUI_TYPE_LOADING);
	_loadInProgress = true;

	while (_loadInProgress) {
		usleep(1000);
	}
	if (getPlayerActId() == 2)
		nextPlayer();

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
	if (gameInfo.playerAI[1] == 0) { // AI
		_players[0] = new AIPlayer(*this, GUI_COLOR_1);
	}
	else if (gameInfo.playerAI[1] == 1) { // real
		_players[0] = new RealPlayer(*this, GUI_COLOR_1);
	}
	else { // hybride
		_players[0] = new HybridePlayer(*this, GUI_COLOR_1);
	}

	if (getPlayerActId() == 2)
		nextPlayer();

	// create new player 2
	delete _players[1];
	if (gameInfo.playerAI[2] == 0)  // AI
		_players[1] = new AIPlayer(*this, GUI_COLOR_2);
	else if (gameInfo.playerAI[2] == 1)  // real
		_players[1] = new RealPlayer(*this, GUI_COLOR_2);
	else  // hybride
		_players[1] = new HybridePlayer(*this, GUI_COLOR_2);

	// set difficulty
	getHeuristic().setDifficulty(gameInfo.difficulty);

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
Heuristic &Game::getHeuristic() const { return *_heuristic; }
bool Game::isFinished() const { return _finished; }

Game::~Game() {
	delete _board;
	delete _gui;
	delete _players[0];
	delete _players[1];
}