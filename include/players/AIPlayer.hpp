#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "players/Player.hpp"
#include <iostream>

class Game;

class AIPlayer : public Player {
	public:
		AIPlayer(Game &game, int color);
		~AIPlayer();
		std::string getType() const;
	protected:
		void move();
	private:
		bool moveBlockWin();  // if _isWinAligned -> block the ennemy
		AIPlayer();
};

#endif