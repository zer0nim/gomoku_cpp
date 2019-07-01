#ifndef MINIMAX_HPP
# define MINIMAX_HPP

# include "Game.hpp"
# include "Node.hpp"
# include "Heuristic.hpp"
# include "utils/Stats.hpp"
# include "ThreadPool.hpp"
# include <tuple>
# include <limits>

std::tuple<Node*, int> miniMax(Game &game, Node &node, int depth, int thrDepth=THR_DEPTH, bool maximize=true,
	int alpha=std::numeric_limits<int>::min(), int beta=std::numeric_limits<int>::max());

#endif
