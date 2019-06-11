#include "Heuristic.hpp"

Heuristic::Heuristic(Game &_game) :
	game(_game),
	_difficultyVal{_defValEasy, _defValNormal, _defValHard},
	_difficulty(NB_DIFFICULTY_LEVEL - 1) {
}

int Heuristic::getVal(std::string name) {
	// std::cout << _difficultyVal.at(_difficulty) << std::endl;
	if (_difficultyVal[_difficulty].find(name) == _difficultyVal[_difficulty].end()) {
		return _defVal[name];
	}
	else {
		return _difficultyVal[_difficulty][name];
	}
	std::cout << "invalid parameter " << name << std::endl;
	return 0;
}

int Heuristic::heuristic(Node &node) {
	std::unordered_map<std::string, int> check_return{
		{"nb_two", 0},
		{"nb_free_two", 0},
		{"nb_three", 0},
		{"nb_free_three", 0},
		{"nb_four", 0},
		{"nb_free_four", 0},
		{"nb_win", 0},
		{"nb_vulnerable", 0},
		{"nb_destroyed", 0}
	};

	return 0;
}

void Heuristic::setDifficulty(int difficulty) {
	_difficulty = difficulty;
}
int Heuristic::getDifficulty() { return _difficulty; }
int Heuristic::getMaxDifficulty() { return NB_DIFFICULTY_LEVEL;}