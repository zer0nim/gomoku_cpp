#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Game;

class Player {
	public:
		Player(Game &game, int _color);
		virtual ~Player();
		virtual void move();
		void click(int x, int y);
		int getColor() const;
		void	incrNbDestroyedStones();
		int		getNbDestroyedStones() const;
		void	setWinAligned();

		Game	&game;
	protected:
		int		_color;
		int		_clickedPos[2];
	private:
		Player();
		int		_nbDestroyedStones;
		bool	_winAligned;
};

#endif