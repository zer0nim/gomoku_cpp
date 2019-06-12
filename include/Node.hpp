#ifndef NODE_HPP
#define NODE_HPP

#include "Board.hpp"
#include <vector>

class Node {
	public:
		Node(Game &_game, Node *parent=nullptr);
		~Node();
		int		getX() const;
 		int		getY() const;
		int		getHeuristic() const;
		Board	&getBoard();
		bool	getIsWin() const;
		void	setIsWin(bool win);

		Game		&game;
		bool		isWin;
	private:
		Board	_board;
		int		_x;
		int		_y;
		int		_heuristic;
		Node	*_parent;
		int		_stone;
		int		_depth;
		std::vector<Node>	_childs;
};

std::ostream & operator << (std::ostream &out, const Node &n);

#endif
