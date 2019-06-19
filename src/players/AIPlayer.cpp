#include <unistd.h>
#include "players/AIPlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"
#include "miniMax.hpp"

AIPlayer::AIPlayer(Game &game, int color) : Player(game, color) {
}

AIPlayer::~AIPlayer() {
}

void AIPlayer::move() {
	if (game.gameInfo.pressSpaceBeforeAI) {
		_spacePressed = false;
		while (!_spacePressed) {
			if (game.getGui().getGuiType() != GUI_TYPE_GAME)
				return;
			usleep(1000);
		}
	}
	moveAI();
}

void AIPlayer::moveAI() {
	#if DEBUG_RESET_GUI
		game.getBoard().resetDebug();
	#endif
	// put the first stone in the middle
	if (game.getBoard().getRemainPlaces() == BOARD_SZ*BOARD_SZ)
		game.getBoard().putStone(BOARD_SZ / 2, BOARD_SZ / 2, game.getPlayerActId());
	else {
		bool usingMiniMax = true;
		if (game.getBoard().getIsVulVict()[OP_ST(game.getPlayerActId())-1]) {
			// if the other player has 5 stones aligned, try to block his alignement
			usingMiniMax = !moveBlockWin();
		}

		if (usingMiniMax) {
			int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
			Node node(game, OP_ST(game.getPlayerActId()), -1, -1, depth+1);
			// std::tuple<Node*, int> move = miniMax(game, node, depth);
			std::tuple<Node*, int> move = getStats<std::tuple<Node*, int>, Game &, Node &, int, bool, int, int>("miniMax", miniMax, game, node, depth, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

			Node *nodeRes = std::get<0>(move);
			#if DEBUG_ANTICIPATION
				int tmpDepth = depth - 1;
			#endif
			while (nodeRes->getParent() && nodeRes->getParent()->getParent()) {
				#if DEBUG_ANTICIPATION
					game.getBoard().setMarkerTxt(nodeRes->getX(), nodeRes->getY(), std::to_string(tmpDepth),
						game.getPlayer(nodeRes->getBoard().get(nodeRes->getX(), nodeRes->getY())).getColor());
					tmpDepth--;
				#endif
				nodeRes = nodeRes->getParent();
			}
			game.getBoard().putStone(nodeRes->getX(), nodeRes->getY(), game.getPlayerActId());
		}
	}
}

bool AIPlayer::moveBlockWin() {
	int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
	Node node(game, OP_ST(game.getPlayerActId()), -1, -1, depth+1);
	node.getBoard().setIsVulVict(false, false);
	getStatsM<int, Node>("node setChilds", node, &Node::setChilds);
	for (auto &child : node.getChilds()) {
		if (child->getBoard().isAllowed(child->getX(), child->getY(), child->getStone())) {
			child->getBoard().putStone(child->getX(), child->getY(), child->getStone());
			child->getBoard().check_winner();
			if (!child->getBoard().getIsVulVict()[OP_ST(game.getPlayerActId())-1]) {
				child->getBoard().setIsVulVict(false, false);
				game.getBoard().putStone(child->getX(), child->getY(), child->getStone());
				return true;
			}
		}
	}
	return false;
}

std::string AIPlayer::getType() const { return "AI"; }