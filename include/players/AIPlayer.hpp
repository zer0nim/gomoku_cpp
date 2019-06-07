#ifndef AI_PLAYER_HPP
#define AI_PLAYER_HPP

#include "players/Player.hpp"
#include <iostream>

class Game;

class AIPlayer : public Player {
	public:
		AIPlayer(Game &_game, int _color);
		~AIPlayer();
		std::string getType() const;
	protected:
		void move();
	private:
		AIPlayer();
};

#endif