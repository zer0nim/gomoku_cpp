#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Game;

class Player {
	public:
		Player(Game &_game, int _color);
		virtual ~Player();
		virtual void move();
		void click(int x, int y);
		int getColor() const;
		void	incrNbDestroyedStones();
		int		getNbDestroyedStones() const;

	protected:
		Game &game;
		int color;
		int clickedPos[2];
	private:
		Player();
		int _nbDestroyedStones;
};

#endif