#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <iostream>
#include <unordered_map>
#include "utils/Stats.hpp"
#include "Node.hpp"
#include "Define.hpp"

#define NB_DIFFICULTY_LEVEL 3

class Game;
class Node;

struct sNodeHist {
	int x;
	int y;
	int stone;
};

class Heuristic {
	public:
		Heuristic(Game &_game);
		int heuristic(Node &node);
		// setter
		void setDifficulty(int difficulty);
		// getter
		int getMul(Node &node, int stone);
		int getDifficulty();
		int getMaxDifficulty();
		int getVal(std::string name);

		Game &game;
	protected:
		void checkAlignedDir(Node &node, int x, int y, int stone, int addx, int addy,
			std::unordered_map<std::string, int> &checkReturn, int multiplier);
		void checkStone(Node &node, int x, int y,
			std::unordered_map<std::string, int> &checkReturn, int multiplier);

		// [WARNING]: the values should not be 0
		std::unordered_map<std::string, int> _defVal{
			// global parameter
			{"DEPTH", 6},  // the depth of the algorithm
			{"NB_SQUARE_ARROUND", 1},  // the number of squares arround taked pos to limit search zone
			{"KEEP_NODE_PERCENT", 10},  // the percentage of node to keep (in minmax algo)
			{"MIN_KEEP_NODE", 3},  // keep at least MIN_KEEP_NODE nodes (if the percentage return less than MIN_KEEP_NODE)
			{"MAX_KEEP_NODE", 5},  // keep max MAX_KEEP_NODE nodes (if the percentage return more than MAX_KEEP_NODE)
			{"DIFF_DIVISER", 20},  // add to the heuristic the diif with the parent heuristic * DIFF_MULTIPLIER
			{"LAST_MOVES_MAX_MULTIPLIER", 3},  // multiply the first move by 5, second 5, third 4, 4th 4, 5th 3, ... -> min 2
			{"NB_STONES_DIVISER", 5},  // divide with NB_STONES to calc some data like last_move_multiplier
			{"MULTIPLIER_POSITIVE", 1},  // used to count more the positive or negative action in heuristic
			{"MULTIPLIER_NEGATIVE", -5},  // used to count more the positive or negative action in heuristic
			{"ENABLE_DIFF", -1},  // enable (1) or disable (-1) diff usage in heuristic

			// value for multiplier
			{"NB_STONES", 1},  // A
			{"TWO", 10 / 2},  // BAA.
			{"FREE_TWO", 20 / 2},  // .AA.
			{"THREE", 30 / 3},  // BAAA.
			{"FREE_THREE", 600 / 3},  // .AAA. .A.AA.
			{"FOUR", 600 / 4},  // BAAAA.
			{"FREE_FOUR", 2000 / 4},  // .AAAA.
			{"WIN", 20000 / 5},  // AAAAA
			{"VULNERABILITY", -35},  // BAA.
			{"DESTROYED", 250},  // BAA. -> B..B
			{"DESTROY_VICTORY_ADDER", 10},  // if this is the last destroyed stone, mul this stone by DESTROY_VICTORY_ADDER
		};
		std::unordered_map<std::string, int> _defValEasy{
			// changes for easy mode
			{"VULNERABILITY", -50},
			{"DESTROYED", 500},
			{"DESTROY_VICTORY_ADDER", 20},
			{"ENABLE_DIFF", 1},
		};
		std::unordered_map<std::string, int> _defValNormal{
			// changes for normal mode
			{"LAST_MOVES_MAX_MULTIPLIER", 4},
			{"MULTIPLIER_POSITIVE", 1},
			{"MULTIPLIER_NEGATIVE", -2},
		};
		std::unordered_map<std::string, int> _defValHard{};  // the hard mode has the same parameters as the default mode
		std::unordered_map<std::string, int> _difficultyVal[NB_DIFFICULTY_LEVEL];
		int _difficulty;
};

#endif