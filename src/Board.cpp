#include "Board.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Board::Board() : _remain_places(BOARD_SZ*BOARD_SZ) {
}

Board::~Board() {
}

int Board::get(int x, int y) const {
	return GET_ST(_content, x, y);
}
void Board::set(int x, int y, int stone) {
	SET_ST(_content, x, y, stone);
}
bool Board::isEmpty(int x, int y) const {
	return GET_ST(_content, x, y) == 0;
}
bool Board::isStone(int x, int y, int stone) const {
	return static_cast<int>(GET_ST(_content, x, y)) == stone;
}

std::vector<int>	check_destroyable(int x, int y, int stone) {
/*
check if the stone at 'x' 'y' can destroy some others stone
return the list of destroyable stones [[x1, y1], [x2, y2], ...]
*/
	std::vector<int> ret;

	// this tab contains all configuration to destroy stones
	// x1, y1, x2, y2, x3, y3
	std::array<std::array<int, 6>, 8> destroy_conf = {{
		{x, y-1, x, y-2, x, y-3},
		{x, y+1, x, y+2, x, y+3},
		{x-1, y, x-2, y, x-3, y},
		{x+1, y, x+2, y, x+3, y},
		{x+1, y+1, x+2, y+2, x+3, y+3},
		{x+1, y-1, x+2, y-2, x+3, y-3},
		{x-1, y+1, x-2, y+2, x-3, y+3},
		{x-1, y-1, x-2, y-2, x-3, y-3}
	}};

	// this is the condition to know if we can destroy some stones
	// x1y1 and x2y2 are the coordinate of potentials destroyed stones
	// x3y3 is the oposite stone
	for (std::array<int, 6> conf : destroy_conf) {
		if (0 <= conf[0] < BOARD_SZ) and 0 <= conf[2] < BOARD_SZ) and 0 <= conf[4] < BOARD_SZ) and
			0 <= conf[1] < BOARD_SZ) and 0 <= conf[3] < BOARD_SZ) and 0 <= conf[5] < BOARD_SZ) and
			self.content[conf[5]][conf[4]] == stone and
			self.content[conf[3]][conf[2]] == self.content[conf[1]][conf[0]] and
			self.content[conf[1]][conf[0]] not in (STONE_EMPTY, stone))
		{
			ret.push_back([destroy_tab_i[0], destroy_tab_i[1]]);
			ret.push_back([destroy_tab_i[2], destroy_tab_i[3]]);
		}
	}

	return ret
}

void putStone(int x, int y, int stone) {
/*
put a stone at 'x' 'y' with id 'stone'
this function put a stone and, if needed, destroy some stones
*/
	if x >= BOARD_SZ) or y >= BOARD_SZ):
		throw OutOfRangeException();

	SET_ST(_content, x, y, stone);
	--_remain_places;

	// // destroy some stones if needed
	// destroyed = check_destroyable(x, y, stone)
	// for dest_x, dest_y in destroyed:
	// 	content[dest_y][dest_x] = STONE_EMPTY
	// 	remain_places += 1
	// 	if not test:
	// 		game.players[stone].destroyed_stones_count += 1

	// // check if there is a winner
	// check_winner()

	// return len(destroyed)
}

// print the board (with colors)
std::ostream & operator << (std::ostream &out, const Board &c) {
	std::array<std::string, 2> color;

	out << '*';
	for (int i = 0; i < BOARD_SZ; ++i)
		out << "---";
	out << '*' << std::endl;
	for (int y = 0; y < BOARD_SZ; ++y) {
		out << '|';
		for (int x = 0; x < BOARD_SZ; ++x) {
			color = {C_EOC, C_EOC};
			if (c.get(x, y) == 1)
				color = {C_WHITE, C_F_WHITE};
			else if (c.get(x, y) == 2)
				color = {C_RED, C_F_RED};
			out << color[0] + color[1] + " . " + C_EOC;
		}
		out << "|" << std::endl;
	}
	out << '*';
	for (int i = 0; i < BOARD_SZ; ++i)
		out << "---";
	out << '*' << std::endl;

	return out;
}
