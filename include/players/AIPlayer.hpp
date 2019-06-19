#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "players/Player.hpp"
#include "utils/Stats.hpp"
#include <iostream>

class Game;

class AIPlayer : public Player {
	public:
		AIPlayer(Game &game, int color);
		~AIPlayer();
		std::string getType() const;
	protected:
		void move();
		std::tuple<int, int> moveAI();
	private:
		std::tuple<int, int> moveBlockWin();  // if _isWinAligned -> block the ennemy
		AIPlayer();
};

#endif