#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <iostream>
#include <unordered_map>
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
		int getMul(int stone);
		int getDifficulty();
		int getMaxDifficulty();
		int getVal(std::string name);

		Game &game;
	protected:
		void checkAlignedDir(Node &node, int x, int y, int stone, int addx, int addy,
			std::unordered_map<std::string, int> &checkReturn, int multiplier);
		void checkStone(Node &node, int x, int y,
			std::unordered_map<std::string, int> &checkReturn, int multiplier);

		std::unordered_map<std::string, int> _defVal{
			// global parameter
			{"DEPTH", 4},  // the depth of the algorithm
			{"NB_SQUARE_ARROUND", 1},  // the number of squares arround taked pos to limit search zone
			{"KEEP_NODE_PERCENT", 20},  // the percentage of node to keep (in minmax algo)
			{"MIN_KEEP_NODE", 3},  // keep at least MIN_KEEP_NODE nodes (if the percentage return less than MIN_KEEP_NODE)
			{"MAX_KEEP_NODE", 4},  // keep max MAX_KEEP_NODE nodes (if the percentage return more than MAX_KEEP_NODE)
			{"MULTIPLIER_POSITIVE", 1},  // used to count more the positive or negative action in heuristic
			{"MULTIPLIER_NEGATIVE", -3},  // used to count more the positive or negative action in heuristic

			// value for multiplier
			{"NB_STONES", 1},  // A
			{"TWO", 10 / 2},  // BAA.
			{"FREE_TWO", 15 / 2},  // .AA.
			{"THREE", 30 / 3},  // BAAA.
			{"FREE_THREE", 130 / 3},  // .AAA. .A.AA.
			{"FOUR", 130 / 4},  // BAAAA.
			{"FREE_FOUR", 1500 / 4},  // .AAAA.
			{"WIN", 6000 / 5},  // AAAAA
			{"VULNERABILITY", -35},  // BAA.
			{"DESTROYED", 150},  // BAA. -> B..B
			{"DESTROY_VICTORY_ADDER", 10}  // if this is the last destroyed stone, mul this stone by DESTROY_VICTORY_ADDER
		};
		std::unordered_map<std::string, int> _defValEasy{
			// changes for easy mode
			{"DEPTH", 1},
			{"MULTIPLIER_POSITIVE", 1},
			{"MULTIPLIER_NEGATIVE", -2}
		};
		std::unordered_map<std::string, int> _defValNormal{
			// changes for normal mode
			{"DEPTH", 2},
			{"VULNERABILITY", 0},
			{"DESTROYED", 0}
		};
		std::unordered_map<std::string, int> _defValHard{};  // the hard mode has the same parameters as the default mode
		std::unordered_map<std::string, int> _difficultyVal[NB_DIFFICULTY_LEVEL];
		int _difficulty;
};

#endif