#ifndef GAME_HPP
# define GAME_HPP

# include "Board.hpp"
# include "gui/Gui.hpp"
# include "players/Player.hpp"
# include "Heuristic.hpp"

# define NB_TYPE_PLAYER 3

struct GameInfo {
	// value: 0->AI, 1->Real, 2->Hybride
	int playerAI[3];  // 0: unused, 1: player1, 2: player2
	int difficulty;
	bool pressSpaceBeforeAI;
};

class Game {
	public:
		Game();
		~Game();
		Player &getPlayer(int id) const;
		Player &getPlayerAct() const;
		MasterBoard &getBoard() const;
		Gui &getGui() const;
		Heuristic &getHeuristic() const;
		int getPlayerActId() const;
		bool isFinished() const;
		void startMenu();
		void startGame();
		void nextPlayer();
		void run();
		void quit();

		bool isQuit;
		GameInfo gameInfo;
	private:
		bool 		_loadInProgress;
		bool		_finished;
		MasterBoard *_board;
		Gui			*_gui;
		Heuristic	*_heuristic;
		std::array<Player *, 2>	_players;
		int			_idPlayerAct;  // 1 or 2 -> players[idPlayerAct-1]

		bool		has_win(int id);
		void		checkWinner();
};

#endif