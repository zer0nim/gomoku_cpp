#ifndef MINIMAX_HPP
# define MINIMAX_HPP

# include "Game.hpp"
# include "Node.hpp"
# include "Heuristic.hpp"
# include <tuple>
# include <limits>
# define COST_NONE std::numeric_limits<int>::max()

std::tuple<Node, int> miniMax(Game &game, Node &node, int depth, bool maximize=true,
    float alpha=(- std::numeric_limits<float>::infinity()), float beta=(std::numeric_limits<float>::infinity()));

#endif