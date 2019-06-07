#include "players/RealPlayer.hpp"
#include "Game.hpp"

RealPlayer::RealPlayer(Game &game, int _color) : Player(game, _color) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
	_clickedPos[0] = -1;
	_clickedPos[1] = -1;
	while (!game.isQuit) {
		if (_clickedPos[0] >= 0 && _clickedPos[1] >= 0) {
			int x = _clickedPos[0];
			int y = _clickedPos[1];
			game.getBoard().putStone(x, y, game.getPlayerActId());
			break ;
		}
	}
}
