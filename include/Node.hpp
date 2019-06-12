#ifndef NODE_HPP
#define NODE_HPP

#include "Board.hpp"
#include <vector>
#include <map>
#include <limits>

#define HEURIS_NOT_SET std::numeric_limits<float>::infinity()

class Node {
/*
this class store a possible move for the ai minMax algorithm
*/
	public:
		Node(Game &game, int stone, int x, int y, int depth, Node *parent=nullptr);
		Node(Node const &src);
		~Node();

		Node &operator=(Node const &rhs);

		int		getX() const;
 		int		getY() const;
		int		getStone() const;
		Node	*getParent() const;
		int		getHeuristic() const;
		void	setHeuristic(int val);
		Board	&getBoard();
		Board	getBoardCopy() const;
		void	setIsWin(bool win);
		int		getDepth() const;
		std::vector<Node>	&getChilds();
		std::vector<Node>	getChildsCopy() const;
		int		setChilds();

		Game		&game;
		bool		isWin;

		bool    operator>(Node const &rhs) const;
        bool    operator<(Node const &rhs) const;
        bool    operator>=(Node const &rhs) const;
        bool    operator<=(Node const &rhs) const;
        bool    operator==(Node const &rhs) const;
        bool    operator!=(Node const &rhs) const;
	private:
		std::map<int, bool>	get_childs_coord();

		Board	_board;
		int		_x;
		int		_y;
		int		_heuristic;
		Node	*_parent;
		int		_stone;
		int		_depth;
		std::vector<Node>	_childs = {};
};

std::ostream & operator << (std::ostream &out, const Node &n);

#endif
