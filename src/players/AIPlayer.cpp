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
	std::array<int, 2> putStonePos = moveAI();
	game.getBoard().putStone(putStonePos[0], putStonePos[1], game.getPlayerActId());
}

std::array<int, 2> AIPlayer::moveAI() {
	#if DEBUG_RESET_GUI
		game.getBoard().resetDebug();
	#endif
	// put the first stone in the middle
	if (game.getBoard().getRemainPlaces() == BOARD_SZ*BOARD_SZ)
		return {{BOARD_SZ / 2, BOARD_SZ / 2}};
	else {
		if (game.getBoard().getIsVulVict()[OP_ST(game.getPlayerActId())-1]) {
			// if the other player has 5 stones aligned, try to block his alignement
			std::array<int, 2> putStonePos = moveBlockWin();
			if (putStonePos[0] >= 0)
				return putStonePos;
		}

		int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
		Node node(game, OP_ST(game.getPlayerActId()), -1, -1, depth+1);
		// std::tuple<Node*, int> move = miniMax(game, node, depth);
		std::tuple<Node*, int> move = getStats<std::tuple<Node*, int>, Game &, Node &, int>("miniMaxThr", miniMaxThr, game, node, depth);

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
		return {{nodeRes->getX(), nodeRes->getY()}};
	}
	return {{-1, -1}};
}

std::array<int, 2> AIPlayer::moveBlockWin() {
	int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
	Node node(game, OP_ST(game.getPlayerActId()), -1, -1, depth+1);
	getStatsM<int, Node>("node setChilds", node, &Node::setChilds);
	for (auto &child : node.getChilds()) {
		if (child->getBoard().isAllowed(child->getX(), child->getY(), child->getStone())) {
			child->getBoard().putStone(child->getX(), child->getY(), child->getStone());
			child->getBoard().check_winner(true);
			if (!child->getBoard().getIsVulVict()[OP_ST(game.getPlayerActId())-1]) {
				return {{child->getX(), child->getY()}};
			}
		}
	}
	return {{-1, -1}};
}

std::string AIPlayer::getType() const { return "AI"; }