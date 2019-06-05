#ifndef REAL_PLAYER_HPP
#define REAL_PLAYER_HPP

#include "players/Player.hpp"
#include <iostream>

class RealPlayer : public Player {
	public:
		RealPlayer();
		~RealPlayer();
		void move();
};

#endif