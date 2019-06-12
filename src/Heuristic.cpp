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
std::unordered_map<std::string, int> checkReturn, int multiplier) {
	int nb_aligned = 1;  // number of aligned stones
    int nb_almost_aligned = 1;  // number of pseudo aligned stones (pseudo mean that there is a hole)
    bool free_side[] = {false, false};  // True if there is a free space around alignement
    int nb_hole[] = {0, 0};
	int new_x;
	int new_y;

    new_x = x + addx;
    new_y = y + addy;
    while (1) {
        // if out of bound
        if (new_x < 0 || new_x >= BOARD_SZ || new_y < 0 || new_y >= BOARD_SZ) {
            if (node.board.isEmpty(new_x - addx, new_y - addy))
                free_side[0] = true;
            break;
		}
        // if player stone
        else if (node.board.get(new_x, new_y) == stone) {
            nb_almost_aligned += 1;
            if (nb_hole[0] == 0)
                nb_aligned += 1;
		}
        // if empty
        else if (node.board.isEmpty(new_x, new_y)) {
            if (node.board.get(new_x - addx, new_y - addy) == stone) {
                if (nb_hole[0] == 0) {
                    nb_hole[0] = 1;
				}
                else {
                    free_side[0] = true;
                    break;
				}
			}
            else if (node.board.isEmpty(new_x - addx, new_y - addy)) {
                nb_hole[0] = 0;
                free_side[0] = true;
                break;
			}
		}
        // if other stone
        else {
            if (node.board.isEmpty(new_x - addx, new_y - addy)) {
                nb_hole[0] = 0;
                free_side[0] = true;
			}
            break;
		}
        new_x += addx;
        new_y += addy;
	}
    new_x = x - addx;
    new_y = y - addy;
    while (1) {
        // if out of bound
        if (new_x < 0 || new_x >= BOARD_SZ || new_y < 0 || new_y >= BOARD_SZ) {
            if (node.board.isEmpty(new_x + addx, new_y + addy))
                free_side[0] = true;
            break;
		}
        // if player stone
        else if (node.board.get(new_x, new_y) == stone) {
            nb_almost_aligned += 1;
            if (nb_hole[0] == 0)
                nb_aligned += 1;
		}
        // if empty
        else if (node.board.isEmpty(new_x, new_y)) {
            if (node.board.get(new_x + addx, new_y + addy) == stone) {
                if (nb_hole[0] == 0) {
                    nb_hole[0] = 1;
				}
                else {
                    free_side[0] = true;
                    break;
				}
			}
            else if (node.board.isEmpty(new_x + addx, new_y + addy)) {
                nb_hole[0] = 0;
                free_side[0] = true;
                break;
			}
		}
        // if other stone
        else {
            if (node.board.isEmpty(new_x + addx, new_y + addy)) {
                nb_hole[0] = 0;
                free_side[0] = true;
			}
            break;
		}
        new_x -= addx;
        new_y -= addy;
	}

    // if nb_aligned >= G.GET("NB_ALIGNED_VICTORY"):  // AAAAA
    //     if game.id_player_act == stone:
    //         node.is_win = True
    //     check_return['nb_win'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    // elif nb_aligned >= 4:
    //     if free_side[0] + free_side[1] == 2:  // .AAAA.
    //         check_return['nb_free_four'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    //     elif free_side[0] + free_side[1] == 1:  // BAAAA.
    //         check_return['nb_four'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    // elif nb_aligned >= 3:
    //     if free_side[0] + free_side[1] == 2:  // .AAA.
    //         check_return['nb_free_three'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    //     elif free_side[0] + free_side[1] == 1:  // BAAA.
    //         check_return['nb_three'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    // elif nb_aligned >= 2:
    //     if free_side[0] + free_side[1] == 2:  // .AA.
    //         check_return['nb_free_two'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    //     elif free_side[0] + free_side[1] == 1:  // BAA.
    //         check_return['nb_two'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    // elif nb_almost_aligned >= 4:  // AA.AA  AAA.AA
    //     check_return['nb_four'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
    // elif nb_almost_aligned == 3:
    //     if free_side[0] + free_side[1] == 2:  // .A.AA.  .AAA.
    //         check_return['nb_free_three'] += multiplier * (G.GET("H_POSITIVE_MULTIPLIER") if game.id_player_act == stone else G.GET("H_NEGATIVE_MULTIPLIER"))
}

void Heuristic::checkStone(Node &node, int x, int y,
std::unordered_map<std::string, int> checkReturn, int multiplier) {
	int stone = node.board.get(x, y);
	if (node.board.isEmpty(x, y))
		return ;
	if (node.board.checkVulnerability(x, y)) {
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
	return 0;
}

void Heuristic::setDifficulty(int difficulty) {
	_difficulty = difficulty;
}
int Heuristic::getDifficulty() { return _difficulty; }
int Heuristic::getMaxDifficulty() { return NB_DIFFICULTY_LEVEL;}