#include "Node.hpp"
#include "Game.hpp"

Node::Node(Game &game, int stone, int x, int y, int depth, Node *parent,
std::unordered_map<std::size_t, std::unordered_map<std::string, int>> *_transpositionTable) :
	game(game),
	isWin(false),
	transpositionTable( (_transpositionTable != nullptr) ? *_transpositionTable : std::unordered_map<std::size_t, std::unordered_map<std::string, int>>{}),
	_board(Board( (parent != nullptr) ? parent->getBoard() : this->game.getBoard() )),
	_x(x),
	_y(y),
	_heuristic(HEURIS_NOT_SET),
	_parent(parent),
	_stone(stone),
	_depth(depth) {
}

Node::Node(Node const &src):
	game(src.game),
	_board(src.getBoardCopy()) {
	*this = src;
}

Node::~Node() {
}

Node &Node::operator=(Node const &rhs) {
	std::cout << "Copy called" << std::endl;
	if (this != &rhs) {
		this->isWin = rhs.isWin;
		this->_board = rhs.getBoardCopy();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_heuristic = rhs.getHeuristic();
		this->_parent = rhs.getParent();
		this->_stone = rhs.getStone();
		this->_depth = rhs.getDepth();
		this->_childs = rhs.getChilds();
	}
	return *this;
}

int		Node::getX() const { return _x; }
int		Node::getY() const { return _y; }
int		Node::getStone() const { return _stone; }
Node	*Node::getParent() const { return _parent; }
int		Node::getHeuristic() const { return _heuristic; }
void	Node::setHeuristic(int val) { _heuristic = val; }

Board	&Node::getBoard() { return _board; }
Board	Node::getBoardCopy() const { return _board; }
int		Node::getDepth() const { return _depth; }

std::map<int, bool> Node::get_childs_coord() {
	std::map<int, bool> testChilds;
	int nbSquareArround = game.getHeuristic().getVal("NB_SQUARE_ARROUND");

	for (int y = 0; y < BOARD_SZ; ++y)
		for (int x = 0; x < BOARD_SZ; ++x)
			if (!_board.isEmpty(x, y)) {
				// add the squares arround the curent pos to testChilds
				for (int _y = y - nbSquareArround; _y < y + nbSquareArround + 1; ++_y)
					for (int _x = x - nbSquareArround; _x < x + nbSquareArround + 1; ++_x)
						if (_x >= 0 && _x < BOARD_SZ && _y >= 0 && _y < BOARD_SZ && _board.isEmpty(_x, _y))
							testChilds[_y * BOARD_SZ + _x] = true;
			}
	Node *tmp = this;
	while (tmp->_parent != nullptr) {
		for (int _y = tmp->_y - nbSquareArround; _y < tmp->_y + nbSquareArround + 1; ++_y)
			for (int _x = tmp->_x - nbSquareArround; _x < tmp->_x + nbSquareArround + 1; ++_x)
				if (_x >= 0 && _x < BOARD_SZ && _y >= 0 && _y < BOARD_SZ && _board.isEmpty(_x, _y))
					testChilds[_y * BOARD_SZ + _x] = true;
		tmp = tmp->_parent;
	}
	return testChilds;
}

std::vector<Node*>	Node::getChilds() const { return _childs; }

int		Node::setChilds() {
	std::map<int, bool> testChilds = get_childs_coord();

	#if DEBUG_SEARCH_ZONE == true
		game.getBoard().resetDebug();
	#endif

	for (auto const& child : testChilds) {
		int x = child.first % BOARD_SZ;
		int y = child.first / BOARD_SZ;
		#if DEBUG_SEARCH_ZONE == true
			game.getBoard().setMarkerColor(x, y, 0xFF0000FF);
		#endif
		_childs.push_back(new Node(game, OP_ST(game.getPlayerActId()), x, y, _depth - 1, this, &transpositionTable));
	}
	return _childs.size();
}

bool    Node::operator >(Node const &rhs) const {
	return this->_heuristic > rhs.getHeuristic();
}
bool    Node::operator <(Node const &rhs) const {
	return this->_heuristic < rhs.getHeuristic();
}
bool    Node::operator >=(Node const &rhs) const {
	return this->_heuristic >= rhs.getHeuristic();
}
bool    Node::operator <=(Node const &rhs) const {
	return this->_heuristic <= rhs.getHeuristic();
}
bool    Node::operator ==(Node const &rhs) const {
	return this->_heuristic == rhs.getHeuristic();
}
bool    Node::operator !=(Node const &rhs) const {
	return this->_heuristic != rhs.getHeuristic();
}

std::ostream & operator << (std::ostream &out, const Node &n) {
	out << "(" << n.getX() << ":" << n.getY() << "->" << n.getHeuristic() << ")";
	return out;
}
