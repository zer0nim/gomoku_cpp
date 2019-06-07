#include "players/AIPlayer.hpp"
#include "Game.hpp"

AIPlayer::AIPlayer(Game &game, int color) : Player(game, color) {
}

AIPlayer::~AIPlayer() {
}

void AIPlayer::move() {
	int x = 0;
	int y = 0;
	while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
		x = std::rand() % BOARD_SZ;
		y = std::rand() % BOARD_SZ;
		if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
			game.getBoard().putStone(x, y, game.getPlayerActId());
			break;
		}
	}
}

std::string AIPlayer::getType() const { return "AI"; }