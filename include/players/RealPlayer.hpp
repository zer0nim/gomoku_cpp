#ifndef REAL_PLAYER_HPP
#define REAL_PLAYER_HPP

#include "players/Player.hpp"
#include <iostream>

class Game;

class RealPlayer : public Player {
	public:
		RealPlayer(Game &game, int _color);
		~RealPlayer();
		std::string getType() const;
	protected:
		std::array<int, 2> move();
	private:
		RealPlayer();
};

#endif