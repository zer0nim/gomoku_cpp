#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "gui/Gui.hpp"
#include "players/Player.hpp"

struct GameInfo {
	bool playerAI[3];  // 0: unused, 1: player1, 2: player2
	int difficulty;
};

class Game {
	public:
		Game();
		~Game();
		Player &getPlayer(int id) const;
		Player &getPlayerAct() const;
		MasterBoard &getBoard() const;
		Gui &getGui() const;
		int getPlayerActId() const;
		void startMenu();
		void startGame();
		void nextPlayer();
		void run();
		void quit();

		bool isQuit;
		GameInfo gameInfo;
	private:
		bool _loadInProgress;
		MasterBoard *board;
		Gui			*gui;
		Player		*players[2];
		int			_idPlayerAct;  // 1 or 2 -> players[idPlayerAct-1]
};

#endif