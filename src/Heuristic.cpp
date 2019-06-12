#include "Game.hpp"
#include "Node.hpp"
#include "Heuristic.hpp"

Heuristic::Heuristic(Game &_game) :
	game(_game),
	_difficultyVal{_defValEasy, _defValNormal, _defValHard},
	_difficulty(NB_DIFFICULTY_LEVEL - 1) {
}

int Heuristic::getVal(std::string name) {
	if (_difficultyVal[_difficulty].find(name) == _difficultyVal[_difficulty].end()) {
		return _defVal[name];
	}
	else {
		return _difficultyVal[_difficulty][name];
	}
	std::cout << "invalid parameter " << name << std::endl;
	return 0;
}
int Heuristic::getMul(int stone) {
	if (game.getPlayerActId() == stone)
		return getVal("MULTIPLIER_POSITIVE");
	return getVal("MULTIPLIER_NEGATIVE");
}

void Heuristic::checkAlignedDir(Node &node, int x, int y, int stone, int addx, int addy,
std::unordered_map<std::string, int> &checkReturn, int multiplier) {
	int nbAligned = 1;  // number of aligned stones
    int nbAlmostAligned = 1;  // number of pseudo aligned stones (pseudo mean that there is a hole)
    bool freeSide[] = {false, false};  // True if there is a free space around alignement
    int nbHole[] = {0, 0};
	int newX;
	int newY;

    newX = x + addx;
    newY = y + addy;
    while (1) {
        // if out of bound
        if (newX < 0 || newX >= BOARD_SZ || newY < 0 || newY >= BOARD_SZ) {
            if (node.getBoard().isEmpty(newX - addx, newY - addy))
                freeSide[0] = true;
            break;
		}
        // if player stone
        else if (node.getBoard().get(newX, newY) == stone) {
            nbAlmostAligned += 1;
            if (nbHole[0] == 0)
                nbAligned += 1;
		}
        // if empty
        else if (node.getBoard().isEmpty(newX, newY)) {
            if (node.getBoard().get(newX - addx, newY - addy) == stone) {
                if (nbHole[0] == 0) {
                    nbHole[0] = 1;
				}
                else {
                    freeSide[0] = true;
                    break;
				}
			}
            else if (node.getBoard().isEmpty(newX - addx, newY - addy)) {
                nbHole[0] = 0;
                freeSide[0] = true;
                break;
			}
		}
        // if other stone
        else {
            if (node.getBoard().isEmpty(newX - addx, newY - addy)) {
                nbHole[0] = 0;
                freeSide[0] = true;
			}
            break;
		}
        newX += addx;
        newY += addy;
	}
    newX = x - addx;
    newY = y - addy;
    while (1) {
        // if out of bound
        if (newX < 0 || newX >= BOARD_SZ || newY < 0 || newY >= BOARD_SZ) {
            if (node.getBoard().isEmpty(newX + addx, newY + addy))
                freeSide[0] = true;
            break;
		}
        // if player stone
        else if (node.getBoard().get(newX, newY) == stone) {
            nbAlmostAligned += 1;
            if (nbHole[0] == 0)
                nbAligned += 1;
		}
        // if empty
        else if (node.getBoard().isEmpty(newX, newY)) {
            if (node.getBoard().get(newX + addx, newY + addy) == stone) {
                if (nbHole[0] == 0) {
                    nbHole[0] = 1;
				}
                else {
                    freeSide[0] = true;
                    break;
				}
			}
            else if (node.getBoard().isEmpty(newX + addx, newY + addy)) {
                nbHole[0] = 0;
                freeSide[0] = true;
                break;
			}
		}
        // if other stone
        else {
            if (node.getBoard().isEmpty(newX + addx, newY + addy)) {
                nbHole[0] = 0;
                freeSide[0] = true;
			}
            break;
		}
        newX -= addx;
        newY -= addy;
	}

    if (nbAligned >= NB_ALIGNED_VICTORY) {  // AAAAA
        if (game.getPlayerActId() == stone)
            node.isWin = true;
        checkReturn["nb_win"] += multiplier * getMul(stone);
	}
    else if (nbAligned >= 4) {
        if (freeSide[0] + freeSide[1] == 2)  // .AAAA.
            checkReturn["nb_free_four"] += multiplier * getMul(stone);
        else if (freeSide[0] + freeSide[1] == 1)  // BAAAA.
            checkReturn["nb_four"] += multiplier * getMul(stone);
	}
    else if (nbAligned >= 3) {
        if (freeSide[0] + freeSide[1] == 2)  // .AAA.
            checkReturn["nb_free_three"] += multiplier * getMul(stone);
        else if (freeSide[0] + freeSide[1] == 1)  // BAAA.
            checkReturn["nb_three"] += multiplier * getMul(stone);
	}
    else if (nbAligned >= 2) {
        if (freeSide[0] + freeSide[1] == 2)  // .AA.
            checkReturn["nb_free_two"] += multiplier * getMul(stone);
        else if (freeSide[0] + freeSide[1] == 1)  // BAA.
            checkReturn["nb_two"] += multiplier * getMul(stone);
	}
    else if (nbAlmostAligned >= 4) {  // AA.AA  AAA.AA
        checkReturn["nb_four"] += multiplier * getMul(stone);
	}
    else if (nbAlmostAligned == 3) {
        if (freeSide[0] + freeSide[1] == 2)  // .A.AA.  .AAA.
            checkReturn["nb_free_three"] += multiplier * getMul(stone);
	}
}

void Heuristic::checkStone(Node &node, int x, int y,
std::unordered_map<std::string, int> &checkReturn, int multiplier) {
	int stone = node.getBoard().get(x, y);
	if (node.getBoard().isEmpty(x, y))
		return ;
	if (node.getBoard().checkVulnerability(x, y)) {
		int mul = multiplier;
		if (game.getPlayer(stone).getNbDestroyedStones() + 2 >= NB_DESTROYED_VICTORY)
			mul *= getVal("DESTROY_VICTORY_ADDER");
		checkReturn["nb_vulnerable"] += mul * (game.getPlayer(stone).getNbDestroyedStones() + 1) * getMul(stone);
	}
	checkAlignedDir(node, x, y, stone, -1, 0, checkReturn, multiplier);
	checkAlignedDir(node, x, y, stone, 0, 1, checkReturn, multiplier);
	checkAlignedDir(node, x, y, stone, 1, 1, checkReturn, multiplier);
	checkAlignedDir(node, x, y, stone, 1, -1, checkReturn, multiplier);
}

int Heuristic::heuristic(Node &node) {
	std::unordered_map<std::string, int> checkReturn{
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
	for (int x=0; x < BOARD_SZ; x++)
		for (int y=0; y < BOARD_SZ; y++)
			checkStone(node, x, y, checkReturn, 1);

	int val = 0;
	std::unordered_map<std::string, int>::iterator it = checkReturn.begin();
	while (it != checkReturn.end()) {
		val += it->second;
		it++;
	}
	return val;
}

void Heuristic::setDifficulty(int difficulty) {
	_difficulty = difficulty;
}
int Heuristic::getDifficulty() { return _difficulty; }
int Heuristic::getMaxDifficulty() { return NB_DIFFICULTY_LEVEL;}