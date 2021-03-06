#ifndef HYBRIDE_PLAYER_HPP
#define HYBRIDE_PLAYER_HPP

#include "players/AIPlayer.hpp"
#include "utils/Stats.hpp"
#include <iostream>

class Game;

class HybridePlayer : public AIPlayer {
	public:
		HybridePlayer(Game &game, int color);
		~HybridePlayer();
		std::string getType() const;
	protected:
		std::array<int, 2> move();
	private:
		HybridePlayer();
};

#endif