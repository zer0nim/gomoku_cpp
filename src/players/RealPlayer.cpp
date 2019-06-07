#include "players/RealPlayer.hpp"
#include "Game.hpp"

RealPlayer::RealPlayer(Game &_game, int _color) : Player(_game, _color) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
	clickedPos[0] = -1;
	clickedPos[1] = -1;
	while (!game.isQuit) {
		if (clickedPos[0] >= 0 && clickedPos[1] >= 0) {
			int x = clickedPos[0];
			int y = clickedPos[1];
			game.getBoard().set(x, y, game.getPlayerActId());
			break ;
		}
	}
}