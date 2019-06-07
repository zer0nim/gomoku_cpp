#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Game;

class Player {
	public:
		Player(Game &_game, int _color);
		virtual ~Player();
		void moving();  // call this function at the player turn
		void click(int x, int y);
		int getColor() const;
		void	incrNbDestroyedStones();
		int		getNbDestroyedStones() const;
		double	getTimeLastMove() const;
		virtual std::string getType() const;

	protected:
		Game &game;
		int color;
		int clickedPos[2];
		double _timeLastMove;
		virtual void move();  // this function is called by moving (redefined in child)

	private:
		Player();
		int _nbDestroyedStones;
};

#endif