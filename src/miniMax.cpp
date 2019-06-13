#include "miniMax.hpp"
#include <algorithm>
#include <queue>
#include <cmath>

struct ReverseCompareNode {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->getHeuristic() < rhs->getHeuristic();
	}
};

std::tuple<Node*, int> miniMax(Game &game, Node &node, int depth, bool maximize, float alpha, float beta) {
/*
min_max algorithm implementation
*/
    if (depth == 0 || node.setChilds() == 0)
        return {&node, game.getHeuristic().heuristic(node)};
    if (maximize) {
        float _max = - std::numeric_limits<float>::infinity();
        std::vector<Node*>	maxlst;
		std::vector<Node*>  childs = node.getChilds();
        #if ENABLE_KEEP_NODE_PERCENT == true
			std::priority_queue<Node*> keepChilds;
			for (auto &child : childs) {
                game.getHeuristic().heuristic(*child);
                if (child->getHeuristic() != HEURIS_NOT_SET) {
                    if (depth == game.getHeuristic().getVal("DEPTH") && child->isWin)
                        return {child, game.getHeuristic().heuristic(node)};
					keepChilds.push(child);
				}
			}
            int range = std::max<int>(std::ceil(keepChilds.size()
            * (game.getHeuristic().getVal("KEEP_NODE_PERCENT") / 100)), game.getHeuristic().getVal("MIN_KEEP_NODE"));
            #if USE_MAX_KEEP_NODE == true
                range = std::min<int>(range, game.getHeuristic().getVal("MAX_KEEP_NODE"));
			#endif
        #else
			range = node.childs;
        #endif

        for (int i = 0; i < range; ++i) {
            #if ENABLE_KEEP_NODE_PERCENT == true
                Node *child = keepChilds.top();
                keepChilds.pop();
            #else
                Node *child = childs[i];
			#endif

            std::tuple<Node*, int> childMin = miniMax(game, *child, depth-1, false, alpha, beta);
            if (std::get<1>(childMin) == COST_NONE)
                continue;
            if (std::get<1>(childMin) > _max) {
                _max = std::get<1>(childMin);
                maxlst.push_back(std::get<0>(childMin));
            }
            else if (std::get<1>(childMin) == _max)
                maxlst.push_back(std::get<0>(childMin));
            alpha = std::max<float>(alpha, _max);
            if (beta <= alpha)
                break;
        }
        if (maxlst.empty())
            return {&node, COST_NONE};
        #if MINMAX_RANDOM_CHOICE == true
            Node *_node = random.choice(maxlst);
        #else
            Node *_node = maxlst[0];
		#endif
        return {_node, _max};
    }
    else {
        float _min = std::numeric_limits<float>::infinity();
        std::vector<Node*>	minlst;
		std::vector<Node*>	childs = node.getChilds();
        #if ENABLE_KEEP_NODE_PERCENT == true
			std::priority_queue<Node*, std::vector<Node*>, ReverseCompareNode> keepChilds;
			for (auto &child : childs) {
                game.getHeuristic().heuristic(*child);
                if (child->getHeuristic() != HEURIS_NOT_SET) {
					keepChilds.push(child);
				}
			}
            int range = std::max<int>(std::ceil(keepChilds.size() * (game.getHeuristic().getVal("KEEP_NODE_PERCENT") / 100)), game.getHeuristic().getVal("MIN_KEEP_NODE"));
            #if USE_MAX_KEEP_NODE == true
                range = std::min<int>(range, game.getHeuristic().getVal("MAX_KEEP_NODE"));
			#endif
        #else
			range = node.childs;
        #endif

        for (int i = 0; i < range; ++i) {
            #if ENABLE_KEEP_NODE_PERCENT == true
                Node *child = keepChilds.top();
                keepChilds.pop();
            #else
                Node *child = childs[i];
			#endif

            std::tuple<Node*, int> childMin = miniMax(game, *child, depth-1, true, alpha, beta);
            if (std::get<1>(childMin) == COST_NONE)
                continue;
            if (std::get<1>(childMin) < _min) {
                _min = std::get<1>(childMin);
                minlst.push_back(std::get<0>(childMin));
            }
            else if (std::get<1>(childMin) == _min)
                minlst.push_back(std::get<0>(childMin));
            beta = std::min<float>(beta, _min);
            if (beta <= alpha)
                break;
        }
        if (minlst.empty())
            return {&node, COST_NONE};
        #if MINMAX_RANDOM_CHOICE == true
            Node *_node = random.choice(minlst);
        #else
            Node *_node = minlst[0];
		#endif
        return {_node, _min};
    }
}
