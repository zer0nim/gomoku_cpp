#include "players/RealPlayer.hpp"
#include "Game.hpp"

RealPlayer::RealPlayer(Game *_game) : Player(_game) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
	clickedPos[0] = -1;
	clickedPos[1] = -1;
	while (!game->isQuit) {
		if (clickedPos[0] >= 0 && clickedPos[1] >= 0) {
			game->board->set(clickedPos[0], clickedPos[1], game->getPlayerActId());
			break ;
		}
	}
}