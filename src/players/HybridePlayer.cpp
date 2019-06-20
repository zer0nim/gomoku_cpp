#include <unistd.h>
#include "players/HybridePlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"

HybridePlayer::HybridePlayer(Game &game, int color) : AIPlayer(game, color) {
}

HybridePlayer::~HybridePlayer() {
}

std::array<int, 2> HybridePlayer::move() {

	_clickedPos[0] = -1;
	_clickedPos[1] = -1;
	_spacePressed = false;
	int x = -1;
	int y = -1;
	std::array<int, 2> putStonePos = {{-1, -1}};
	while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
		if (_spacePressed) {
			_spacePressed = false;
			if (putStonePos[0] == -1) {
				putStonePos = moveAI();
				game.getBoard().setMarkerColor(putStonePos[0], putStonePos[1], GUI_COLOR_MARKER_HELP);
			}
			else {
				game.getBoard().setMarkerColor(putStonePos[0], putStonePos[1]);
				return {{putStonePos[0], putStonePos[1]}};
			}
		}
		if (_clickedPos[0] >= 0 && _clickedPos[1] >= 0) {
			if (x != -1 || y != -1)
				game.getBoard().setMarkerColor(x, y);
			x = _clickedPos[0];
			y = _clickedPos[1];
			if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
				if (putStonePos[0] >= 0) {
					game.getBoard().setMarkerColor(putStonePos[0], putStonePos[1]);
				}
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

std::string HybridePlayer::getType() const { return "Hybride"; }