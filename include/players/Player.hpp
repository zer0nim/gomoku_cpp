#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Game;

class Player {
	public:
		Player(Game &_game);
		virtual ~Player();
		virtual void move();
		void	click(int x, int y);
		void	incrNbDestroyedStones();
		int		getNbDestroyedStones() const;
		void	setWinAligned();
	protected:
		Game	&_game;
		int		clickedPos[2];
	private:
		Player();
		int		_nbDestroyedStones;
		bool	_winAligned;
};

#endif