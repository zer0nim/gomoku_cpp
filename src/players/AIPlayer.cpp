#include "players/AIPlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"

AIPlayer::AIPlayer(Game &game, int color) : Player(game, color) {
}

AIPlayer::~AIPlayer() {
}

void AIPlayer::move() {
	// int x = 0;
	// int y = 0;
	// while (!game.isQuit && game.getGui().getGuiType() == GUI_TYPE_GAME) {
	// 	x = std::rand() % BOARD_SZ;
	// 	y = std::rand() % BOARD_SZ;
	// 	if (game.getBoard().isAllowed(x, y, game.getPlayerActId())) {
	// 		game.getBoard().putStone(x, y, game.getPlayerActId());
	// 		break;
	// 	}
	// }
	int depth = std::min<int>(DEPTH, game.getBoard().getRemainPlaces());
	Node node(game, !game.getPlayerActId(), -1, -1, depth+1);
	node.setChilds();
}

std::string AIPlayer::getType() const { return "AI"; }