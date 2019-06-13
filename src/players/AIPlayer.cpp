#include "players/AIPlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"
#include "miniMax.hpp"

AIPlayer::AIPlayer(Game &game, int color) : Player(game, color) {
}

AIPlayer::~AIPlayer() {
}

void AIPlayer::move() {
	// put the first stone in the middle
	if (game.getBoard().getRemainPlaces() == BOARD_SZ*BOARD_SZ)
		game.getBoard().putStone(BOARD_SZ / 2, BOARD_SZ / 2, game.getPlayerActId());
	else {
		int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
		Node node(game, OP_ST(game.getPlayerActId()), -1, -1, depth+1);
		std::tuple<Node*, int> move = miniMax(game, node, depth);

		Node *nodeRes = std::get<0>(move);
		while (nodeRes->getParent() && nodeRes->getParent()->getParent()) {
			nodeRes = nodeRes->getParent();
		}
		game.getBoard().putStone(nodeRes->getX(), nodeRes->getY(), game.getPlayerActId());
	}
}

std::string AIPlayer::getType() const { return "AI"; }