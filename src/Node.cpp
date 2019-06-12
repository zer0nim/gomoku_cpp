#include "Node.hpp"
#include "Game.hpp"

Node::Node(Game &game, Node *parent) :
	game(game),
	isWin(false),
	_board(Board( (parent != nullptr) ? parent->getBoard() : this->game.getBoard() )),
	_parent(parent) {
}

Node::~Node() {
}

int		Node::getX() const { return _x; }
int		Node::getY() const { return _y; }
int		Node::getHeuristic() const { return _heuristic; }
void	Node::setHeuristic(int val) { _heuristic = val; }

Board	&Node::getBoard() { return _board; }

std::ostream & operator << (std::ostream &out, const Node &n) {
	out << "(" << n.getX() << ":" << n.getY() << "->" << n.getHeuristic() << ")";
	return out;
}
