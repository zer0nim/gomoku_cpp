#include "players/RealPlayer.hpp"
#include "Game.hpp"

RealPlayer::RealPlayer(Game &game, int _color) : Player(game, _color) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
	_clickedPos[0] = -1;
	_clickedPos[1] = -1;
	int x = 0;
	int y = 0;
	while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
		if (_clickedPos[0] >= 0 && _clickedPos[1] >= 0) {
			x = _clickedPos[0];
			y = _clickedPos[1];
			if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
				game.getBoard().putStone(x, y, game.getPlayerActId());
				break;
			}
			else
				; // need to show an error !
		}
	}
}

std::string RealPlayer::getType() const { return "Real Player"; }
