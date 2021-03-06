#include <unistd.h>
#include <algorithm>
#include "players/RealPlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"

RealPlayer::RealPlayer(Game &game, int _color) : Player(game, _color) {
}

RealPlayer::~RealPlayer() {
}

std::array<int, 2> RealPlayer::move() {
	_clickedPos[0] = -1;
	_clickedPos[1] = -1;
	int x = -1;
	int y = -1;
	while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
		if (_clickedPos[0] >= 0 && _clickedPos[1] >= 0) {
			if (x != -1 || y != -1)
				game.getBoard().setMarkerColor(x, y);
			x = _clickedPos[0];
			y = _clickedPos[1];
			if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
				return {{x, y}};
			}
			else {
				game.getBoard().setMarkerColor(x, y, 0xFF0000FF);
				_clickedPos[0] = -1;
				_clickedPos[1] = -1;
			}
		}
		usleep(1000);
	}
	return {{-1, -1}};
}

std::string RealPlayer::getType() const { return "Real Player"; }
