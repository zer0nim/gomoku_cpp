#include "players/RealPlayer.hpp"
#include "Game.hpp"
#include "Node.hpp"
#include <algorithm>

RealPlayer::RealPlayer(Game &game, int _color) : Player(game, _color) {
}

RealPlayer::~RealPlayer() {
}

void RealPlayer::move() {
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
				game.getBoard().putStone(x, y, game.getPlayerActId());
				break;
			}
			else {
				game.getBoard().setMarkerColor(x, y, 0xFF0000FF);
				_clickedPos[0] = -1;
				_clickedPos[1] = -1;
			}
		}
	}
	int depth = std::min<int>(game.getHeuristic().getVal("DEPTH"), game.getBoard().getRemainPlaces());
	Node node(game, !game.getPlayerActId(), -1, -1, depth+1);  // ////////////////////////
	game.getHeuristic().heuristic(node);  // ///////////////////////////////////
	node.setChilds();
	node.getChilds()[0].setChilds();
	int heuristic;
	heuristic = game.getHeuristic().heuristic(node);
	std::cout << std::endl << "heuristic: " << heuristic << std::endl;  // /////////////
	heuristic = game.getHeuristic().heuristic(node.getChilds()[0]);
	std::cout << "child heuristic: " << heuristic << std::endl;
	heuristic = game.getHeuristic().heuristic(node.getChilds()[0].getChilds()[0]);
	std::cout << "childchild heuristic: " << heuristic << std::endl;
}

std::string RealPlayer::getType() const { return "Real Player"; }
