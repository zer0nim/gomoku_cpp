#include <unistd.h>
#include "players/HybridePlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"

HybridePlayer::HybridePlayer(Game &game, int color) : AIPlayer(game, color) {
}

HybridePlayer::~HybridePlayer() {
}

void HybridePlayer::move() {

	_clickedPos[0] = -1;
	_clickedPos[1] = -1;
	_spacePressed = false;
	int x = -1;
	int y = -1;
	std::tuple<int, int> putStonePos = {-1, -1};
	while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
		if (_spacePressed) {
			_spacePressed = false;
			if (std::get<0>(putStonePos) == -1) {
				putStonePos = moveAI();
				if (std::get<0>(putStonePos) >= 0) {
					game.getBoard().setMarkerColor(std::get<0>(putStonePos), std::get<1>(putStonePos), GUI_COLOR_MARKER_HELP);
				}
			}
			else {
				game.getBoard().setMarkerColor(std::get<0>(putStonePos), std::get<1>(putStonePos));
				game.getBoard().putStone(std::get<0>(putStonePos), std::get<1>(putStonePos), game.getPlayerActId());
				break;
			}
		}
		if (_clickedPos[0] >= 0 && _clickedPos[1] >= 0) {
			if (x != -1 || y != -1)
				game.getBoard().setMarkerColor(x, y);
			x = _clickedPos[0];
			y = _clickedPos[1];
			if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
				game.getBoard().putStone(x, y, game.getPlayerActId());
				break;
			}
			else {
				game.getBoard().setMarkerColor(x, y, 0xFF0000FF);
				_clickedPos[0] = -1;
				_clickedPos[1] = -1;
			}
		}
		usleep(1000);
	}
}

std::string HybridePlayer::getType() const { return "Hybride"; }