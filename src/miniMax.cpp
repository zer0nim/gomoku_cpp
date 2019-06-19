#include "miniMax.hpp"
#include <algorithm>
#include <queue>
#include <cmath>

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

void updateBest(Game &game, Node &node, int depth, bool maximize, int &alpha, int &beta, int &_best, std::vector<Node*> &bestLst) {
	std::tuple<Node*, int> childMin = miniMax(game, node, depth-1, !maximize, alpha, beta);
	if (std::get<1>(childMin) == HEURIS_NOT_SET)
		return;
	if (maximize) {
		if (std::get<1>(childMin) > _best) {
			_best = std::get<1>(childMin);
			bestLst.clear();
			bestLst.push_back(std::get<0>(childMin));
		}
		else if (std::get<1>(childMin) == _best)
			bestLst.push_back(std::get<0>(childMin));
		alpha = std::max<float>(alpha, _best);
	} else {
		if (std::get<1>(childMin) < _best) {
			_best = std::get<1>(childMin);
			bestLst.clear();
			bestLst.push_back(std::get<0>(childMin));
		}
		else if (std::get<1>(childMin) == _best)
			bestLst.push_back(std::get<0>(childMin));
		beta = std::min<float>(beta, _best);
	}
}

std::tuple<Node*, int> miniMax(Game &game, Node &node, int depth, bool maximize, int alpha, int beta) {
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
	int range;
	if (maximize) {
		int _best = - std::numeric_limits<int>::min();
		std::vector<Node*>	bestLst;
		std::vector<Node*>  childs = node.getChilds();
		#if ENABLE_KEEP_NODE_PERCENT
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
			range = std::max<int>(std::ceil(keepChilds.size()
			* (static_cast<float>(game.getHeuristic().getVal("KEEP_NODE_PERCENT")) / 100)), game.getHeuristic().getVal("MIN_KEEP_NODE"));
			if (range > static_cast<int>(keepChilds.size()))
				range = keepChilds.size();
			#if USE_MAX_KEEP_NODE
				range = std::min<int>(range, game.getHeuristic().getVal("MAX_KEEP_NODE"));
			#endif
		#else
			range = node.getChilds().size();
		#endif

		for (int i = 0; i < range; ++i) {
			#if ENABLE_KEEP_NODE_PERCENT
				Node *child = keepChilds.top();
				keepChilds.pop();
				#if DEBUG_KEEP_NODE_PERCENT
					if (depth == game.getHeuristic().getVal("DEPTH")) {
						game.getBoard().setMarkerColor(child->getX(), child->getY(), game.getPlayer(child->getStone()).getColor());
					}
				#endif
			#else
				Node *child = childs[i];
			#endif

			updateBest(game, *child, depth, maximize, alpha, beta, _best, bestLst);
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
	else {  // minimize
		int _best = std::numeric_limits<int>::max();
		std::vector<Node*>	bestLst;
		std::vector<Node*>	childs = node.getChilds();
		#if ENABLE_KEEP_NODE_PERCENT
			std::priority_queue<Node*, std::vector<Node*>, CompareNode> keepChilds;
			for (auto &child : childs) {
				// game.getHeuristic().heuristic(*child);
				getStatsM<int, Heuristic, Node &>("heuristic", game.getHeuristic(), &Heuristic::heuristic, *child);

				if (child->getHeuristic() != HEURIS_NOT_SET) {
					keepChilds.push(child);
				}
			}
			range = std::max<int>(std::ceil(keepChilds.size() * (static_cast<float>(game.getHeuristic().getVal("KEEP_NODE_PERCENT")) / 100)), game.getHeuristic().getVal("MIN_KEEP_NODE"));
			if (range > static_cast<int>(keepChilds.size()))
				range = keepChilds.size();
			#if USE_MAX_KEEP_NODE
				range = std::min<int>(range, game.getHeuristic().getVal("MAX_KEEP_NODE"));
			#endif
		#else
			range = node.getChilds().size();
		#endif

		for (int i = 0; i < range; ++i) {
			#if ENABLE_KEEP_NODE_PERCENT
				Node *child = keepChilds.top();
				keepChilds.pop();
			#else
				Node *child = childs[i];
			#endif

			updateBest(game, *child, depth, maximize, alpha, beta, _best, bestLst);
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
}
