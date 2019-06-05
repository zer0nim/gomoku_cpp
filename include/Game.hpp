#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "gui/Gui.hpp"
#include "players/Player.hpp"

class Game {
	public:
		Game();
		~Game();
		Player *getPlayer(int id);
		Player *getPlayerAct();
		int getPlayerActId();
		void run();
		void quit();

		MasterBoard *board;
		Gui *gui;
	private:
		Player *players[2];
		int _idPlayerAct;  // 1 or 2 -> players[idPlayerAct-1]
		bool _isQuit;
};

#endif