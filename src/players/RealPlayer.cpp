#include "players/RealPlayer.hpp"
#include "Game.hpp"

RealPlayer::RealPlayer(Game &_game) : Player(_game) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
	clickedPos[0] = -1;
	clickedPos[1] = -1;
	while (!_game.isQuit) {
		if (clickedPos[0] >= 0 && clickedPos[1] >= 0) {
			int x = clickedPos[0];
			int y = clickedPos[1];
			_game.board->putStone(x, y, _game.getPlayerActId());
			break ;
		}
	}
}
