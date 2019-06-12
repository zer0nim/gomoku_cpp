#include "Node.hpp"
#include "Game.hpp"

Node::Node(Game &game, int stone, int x, int y, int depth, Node *parent) :
	game(game),
	isWin(false),
	_board(Board( (parent != nullptr) ? parent->getBoard() : this->game.getBoard() )),
	_x(x),
	_y(y),
	_parent(parent),
	_stone(stone),
	_depth(depth) {
}

Node::~Node() {
}

int		Node::getX() const { return _x; }
int		Node::getY() const { return _y; }
int		Node::getStone() const { return _stone; }
Node	*Node::getParent() const { return _parent; }
int		Node::getHeuristic() const { return _heuristic; }
void	Node::setHeuristic(int val) { _heuristic = val; }

Board	&Node::getBoard() { return _board; }

std::map<int, bool> Node::get_childs_coord() {
	std::map<int, bool> testChilds;

	for (int y = 0; y < BOARD_SZ; ++y)
		for (int x = 0; x < BOARD_SZ; ++x)
			if (!_board.isEmpty(x, y)) {
				// add the squares arround the curent pos to testChilds
				for (int _y = y - NB_SQUARE_ARROUND; _y < y + NB_SQUARE_ARROUND + 1; ++_y)
					for (int _x = x - NB_SQUARE_ARROUND; _x < x + NB_SQUARE_ARROUND + 1; ++_x)
						if (_x >= 0 && _x < BOARD_SZ && _y >= 0 && _y < BOARD_SZ && _board.isEmpty(_x, _y))
							testChilds[_y * BOARD_SZ + _x] = true;
			}
	Node *tmp = this;
	while (tmp->_parent != nullptr)
		for (int _y = tmp->_y - NB_SQUARE_ARROUND; _y < tmp->_y + NB_SQUARE_ARROUND + 1; ++_y)
			for (int _x = tmp->_x - NB_SQUARE_ARROUND; _x < tmp->_x + NB_SQUARE_ARROUND + 1; ++_x)
				if (_x >= 0 && _x < BOARD_SZ && _y >= 0 && _y < BOARD_SZ && _board.isEmpty(_x, _y))
					testChilds[_y * BOARD_SZ + _x] = true;
		tmp = tmp->_parent;
	return testChilds;
}

void	Node::setChilds() {
	std::map<int, bool> testChilds = get_childs_coord();

	#if DEBUG_SEARCH_ZONE == true
		game.getBoard().resetDebug();
	#endif

	for (auto const& child : testChilds) {
		int x = child.first % BOARD_SZ;
		int y = child.first / BOARD_SZ;
		if (DEBUG_SEARCH_ZONE)
			game.getBoard().setMarkerColor(x, y, 0xFF0000FF);
		_childs.push_back(Node(game, !game.getPlayerActId(), x, y, _depth - 1));
	}
}

std::ostream & operator << (std::ostream &out, const Node &n) {
	out << "(" << n.getX() << ":" << n.getY() << "->" << n.getHeuristic() << ")";
	return out;
}
