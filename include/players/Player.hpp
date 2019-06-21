#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <array>

class Game;

class Player {
	public:
		Player(Game &game, int _color);
		virtual ~Player();
		void	moving();  // call this function at the player turn
		void	click(int x, int y);
		void	setSpacePressed(bool pressed);
		uint	getColor() const;
		void	incrNbDestroyedStones();
		int		getNbDestroyedStones() const;
		void	setWinAligned();
		double	getTimeLastMove() const;
		virtual std::string getType() const;
		void	incrNbStones();
		void	decrNbStones();
		int		getNbStones() const;
		bool	getWinAligned() const;
		void	setWinner(bool win);
		bool	isWinner() const;

		Game	&game;
	protected:
		virtual std::array<int, 2> move();  // this function is called by moving (redefined in child)

		int		_color;
		int		_clickedPos[2];
		bool	_spacePressed;
		double	_timeLastMove;
	private:
		Player();
		int		_nbDestroyedStones;
		int		_nbStones;
		bool	_winAligned;
		bool	_isWinner;
};

#endif