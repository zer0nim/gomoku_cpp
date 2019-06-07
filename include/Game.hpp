#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "gui/Gui.hpp"
#include "players/Player.hpp"

class Game {
	public:
		Game();
		~Game();
		Player &getPlayer(int id) const;
		Player &getPlayerAct() const;
		MasterBoard &getBoard() const;
		Gui &getGui() const;
		int getPlayerActId() const;
		void nextPlayer();
		void run();
		void quit();

		bool isQuit;
	private:
		MasterBoard *board;
		Gui			*gui;
		Player		*players[2];
		int			_idPlayerAct;  // 1 or 2 -> players[idPlayerAct-1]
};

#endif