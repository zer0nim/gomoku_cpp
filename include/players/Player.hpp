#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Player {
	public:
		Player();
		virtual ~Player();
		virtual void move();
};

#endif