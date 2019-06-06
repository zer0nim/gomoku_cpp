#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Game;

class Player {
	public:
		Player(Game &_game);
		virtual ~Player();
		virtual void move();
		void click(int x, int y);

	protected:
		Game &game;
		int clickedPos[2];
};

#endif