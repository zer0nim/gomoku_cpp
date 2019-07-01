#include "miniMax.hpp"
#include <algorithm>
#include <queue>
#include <cmath>
#include <future>
#include <vector>

struct CompareNode {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->getHeuristic() > rhs->getHeuristic();
	}
};
struct ReverseCompareNode {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->getHeuristic() < rhs->getHeuristic();
	}
};

std::tuple<Node*, int> miniMax(Game &game, Node &node, int depth, int thrDepth, bool maximize, int alpha, int beta) {
/*
min_max algorithm implementation
*/
	if (depth == 0
	// || node.setChilds() == 0
	|| getStatsM<int, Node>("node setChilds", node, &Node::setChilds) == 0
	)
		return {
			&node,
			// game.getHeuristic().heuristic(node)
			getStatsM<int, Heuristic, Node &>("heuristic", game.getHeuristic(), &Heuristic::heuristic, node)
		};

	if (game.isQuit)  // force quit minimax
		return {&node, HEURIS_NOT_SET};

	int range;
	int _best = (maximize)? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	std::vector<Node*>	bestLst;
	std::vector<Node*>  childs = node.getChilds();
	// To control async threads and their results
	std::vector<std::future<std::tuple<Node*, int> >> fut_vec;

	if (maximize) {
		std::priority_queue<Node*, std::vector<Node*>, ReverseCompareNode> keepChilds;
		for (auto &child : childs) {
			// game.getHeuristic().heuristic(*child);
			getStatsM<int, Heuristic, Node &>("heuristic", game.getHeuristic(), &Heuristic::heuristic, *child);

			if (child->getHeuristic() != HEURIS_NOT_SET) {
				if (depth == game.getHeuristic().getVal("DEPTH") && child->isWin)
					return {
						child,
						// game.getHeuristic().heuristic(node)
						getStatsM<int, Heuristic, Node &>("heuristic", game.getHeuristic(), &Heuristic::heuristic, node)
					};
				keepChilds.push(child);
			}
		}
		range = std::min(game.getHeuristic().getVal("MAX_KEEP_NODE"), std::max(game.getHeuristic().getVal("MIN_KEEP_NODE"), std::min<int>(keepChilds.size(), depth)));

		for (int i = 0; i < range; ++i) {
			Node *child = keepChilds.top();
			keepChilds.pop();
			#if DEBUG_KEEP_NODE_PERCENT
				if (depth == game.getHeuristic().getVal("DEPTH")) {
					game.getBoard().setMarkerColor(child->getX(), child->getY(), game.getPlayer(child->getStone()).getColor());
				}
			#endif

			if (thrDepth > 0) {
				fut_vec.push_back(std::async(std::launch::async, miniMax, std::ref(game), std::ref(*child), depth-1,
					thrDepth-1, false, alpha, beta));
			} else {
				// update _best
				std::tuple<Node*, int> childMin = miniMax(game, *child, depth-1, thrDepth-1, !maximize, alpha, beta);
				if (std::get<1>(childMin) == HEURIS_NOT_SET)
					continue;
				if (std::get<1>(childMin) > _best) {
					_best = std::get<1>(childMin);
					bestLst.clear();
					bestLst.push_back(std::get<0>(childMin));
				}
				else if (std::get<1>(childMin) == _best)
					bestLst.push_back(std::get<0>(childMin));
				alpha = std::max<float>(alpha, _best);
				if (beta <= alpha)
					break;
			}
		}
	}
	else {  // minimize
		std::priority_queue<Node*, std::vector<Node*>, CompareNode> keepChilds;
		for (auto &child : childs) {
			// game.getHeuristic().heuristic(*child);
			getStatsM<int, Heuristic, Node &>("heuristic", game.getHeuristic(), &Heuristic::heuristic, *child);

			if (child->getHeuristic() != HEURIS_NOT_SET)
				keepChilds.push(child);
		}
		range = std::min(game.getHeuristic().getVal("MAX_KEEP_NODE"), std::max(game.getHeuristic().getVal("MIN_KEEP_NODE"), std::min<int>(keepChilds.size(), depth)));

		for (int i = 0; i < range; ++i) {
			Node *child = keepChilds.top();
			keepChilds.pop();

			if (thrDepth > 0) {
				fut_vec.push_back(std::async(std::launch::async, miniMax, std::ref(game), std::ref(*child), depth-1,
					thrDepth-1, true, alpha, beta));
			} else {
				// update _best
				std::tuple<Node*, int> childMin = miniMax(game, *child, depth-1, thrDepth-1, !maximize, alpha, beta);
				if (std::get<1>(childMin) == HEURIS_NOT_SET)
					continue;
				if (std::get<1>(childMin) < _best) {
					_best = std::get<1>(childMin);
					bestLst.clear();
					bestLst.push_back(std::get<0>(childMin));
				}
				else if (std::get<1>(childMin) == _best)
					bestLst.push_back(std::get<0>(childMin));
				beta = std::min<float>(beta, _best);
				if (beta <= alpha)
					break;
			}
		}
	}

	if (thrDepth > 0) {
		// Wait all results from async threads
		for (size_t i = 0; i < fut_vec.size(); ++i) {
			std::tuple<Node*, int> childMin = fut_vec[i].get();
			Node *testNode = std::get<0>(childMin);

			if (testNode->getHeuristic() == HEURIS_NOT_SET)
				continue;
			if ((maximize && testNode->getHeuristic() > _best)
			|| (!maximize && testNode->getHeuristic() < _best)) {
				_best = testNode->getHeuristic();
				bestLst.clear();
				bestLst.push_back(testNode);
			}
			else if (testNode->getHeuristic() == _best)
				bestLst.push_back(testNode);
			if (maximize)
				alpha = std::max<float>(alpha, _best);
			else
				beta = std::min<float>(beta, _best);
			if (beta <= alpha)
				break;
		}
	}

	if (bestLst.empty())
		return {&node, HEURIS_NOT_SET};
	#if MINMAX_RANDOM_CHOICE
		Node *_node = bestLst[static_cast<int>(std::rand() % bestLst.size())];
	#else
		Node *_node = bestLst[0];
	#endif
	return {_node, _best};
}
