#ifndef REAL_PLAYER_HPP
#define REAL_PLAYER_HPP

#include "players/Player.hpp"
#include <iostream>

class Game;

class RealPlayer : public Player {
	public:
		RealPlayer(Game &_game, int _color);
		~RealPlayer();
	protected:
		void move();
	private:
		RealPlayer();
};

#endif