#include "Board.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Board::Board(Game &game)
: _remain_places(BOARD_SZ*BOARD_SZ), _game(game) {
	_lastStone[0] = 0;
	_lastStone[1] = 0;
}

Board::~Board() {
}

int Board::get(int x, int y) const {
	return GET_ST(_content, x, y);
}
void Board::set(int x, int y, int stone) {
	SET_ST(_content, x, y, stone);
	_lastStone[0] = x;
	_lastStone[1] = y;
}
bool Board::isEmpty(int x, int y) const {
	return GET_ST(_content, x, y) == 0;
}
bool Board::isStone(int x, int y, int stone) const {
	return static_cast<int>(GET_ST(_content, x, y)) == stone;
}
bool Board::isLastStone(int x, int y) {
	return (x == _lastStone[0] && y == _lastStone[1]);
}

std::vector< std::array<int, 2> >	Board::check_destroyable(int x, int y, int stone) {
/*
check if the stone at 'x' 'y' can destroy some others stone
return the list of destroyable stones [[x1, y1], [x2, y2], ...]
*/
	std::vector< std::array<int, 2> > ret;

	// this tab contains all configuration to destroy stones
	// x1, y1, x2, y2, x3, y3
	std::array<std::array<int, 6>, 8> destroy_conf = {{
		{{ x, y-1, x, y-2, x, y-3 }},
		{{ x, y+1, x, y+2, x, y+3 }},
		{{ x-1, y, x-2, y, x-3, y }},
		{{ x+1, y, x+2, y, x+3, y }},
		{{ x+1, y+1, x+2, y+2, x+3, y+3 }},
		{{ x+1, y-1, x+2, y-2, x+3, y-3 }},
		{{ x-1, y+1, x-2, y+2, x-3, y+3 }},
		{{ x-1, y-1, x-2, y-2, x-3, y-3 }}
	}};

	// this is the condition to know if we can destroy some stones
	// x1y1 and x2y2 are the coordinate of potentials destroyed stones
	// x3y3 is the oposite stone
	for (std::array<int, 6> conf : destroy_conf) {
		if (conf[0] > 0 && conf[0] < BOARD_SZ && conf[2] > 0 && conf[2] < BOARD_SZ && conf[4] > 0 && conf[4] < BOARD_SZ &&
			conf[1] > 0 && conf[1] < BOARD_SZ && (conf[3] > 0 && conf[3] < BOARD_SZ) && conf[5] > 0 && conf[5] < BOARD_SZ &&
			get(conf[4], conf[5]) == stone &&
			get(conf[2], conf[3]) == get(conf[0], conf[1]) &&
			get(conf[0], conf[1]) != 0 && get(conf[0], conf[1]) != stone)
		{
			ret.push_back({{ conf[0], conf[1] }});
			ret.push_back({{ conf[2], conf[3] }});
		}
	}

	return ret;
}

bool	Board::isFreeThreeDir(int x, int y, int stone, int addx, int addy) {
/*
check if there is a free three from 'x' 'y' in direction given by 'addx' and 'addy'
return 1 if it's a free-three
else return 0
*/
	// list of all free-three configurations
	// 0 == every stone is OK
	// 1 == only empty stones
	// 2 == only actual stone
	// the 5th element is the 'x' 'y' element
	std::array<std::array<int, 9>, 9> free_three = {{
		{{ 0, 0, 1, 2, 2, 2, 1, 0, 0 }},
		{{ 0, 0, 0, 1, 2, 2, 2, 1, 0 }},
		{{ 0, 1, 2, 2, 2, 1, 0, 0, 0 }},
		{{ 0, 0, 0, 1, 2, 2, 1, 2, 1 }},
		{{ 1, 2, 1, 2, 2, 1, 0, 0, 0 }},
		{{ 0, 0, 0, 1, 2, 1, 2, 2, 1 }},
		{{ 0, 2, 2, 1, 2, 1, 0, 0, 0 }},
		{{ 0, 0, 1, 2, 2, 1, 2, 1, 0 }},
		{{ 0, 1, 2, 1, 2, 2, 1, 0, 0 }},
	}};
	int lenFT = 9;

	// get a list to compare with the free-three list
	std::vector<int> lst(lenFT, -2);
	int i = 0;
	int new_x = x - (addx * (lenFT >> 1));
	int new_y = y - (addy * (lenFT >> 1));

	for (int i = 0; i < lenFT; ++i) {
		if (new_x > 0 && new_x < BOARD_SZ && new_y > 0 && new_y < BOARD_SZ)
			lst[i] = GET_ST(_content, new_x, new_y);
		new_x += addx;
		new_y += addy;
	}

	lst[lenFT >> 1] = stone;
	int	is_free_three = true;
	for (std::array<int, 9> free_elem : free_three) {
		is_free_three = true;
		for (int i = 0; i < lenFT; ++i) {
			if (free_elem[i] == 0)  // no matter
				continue;
			else if (free_elem[i] == 1) {  // only empty
				if (lst[i] != 0) {
					is_free_three = false;
					break;
				}
			}
			else if (free_elem[i] == 2) {  // only player stone
				if (lst[i] != stone) {
					is_free_three = false;
					break;
				}
			}
		}
		if (is_free_three)
			return true;
	}
	return false;
}

bool	Board::isAllowed(int x, int y, int stone) {
/*
if we want to put a stone at 'x' 'y',
this function check if it's allowed (empty place, no free-threes, ...)
*/
	if (GET_ST(_content, x, y) != 0)
		return false;

	// check double three
	// if the stone destroy others stones -> no double three effect
	if (check_destroyable(x, y, stone).size() > 0)
		return true;

	int nbFreeThree = isFreeThreeDir(x, y, stone, 1, 0) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, 0, 1) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, 1, 1) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, -1, 1) ? 1 : 0;

	if (nbFreeThree >= 2) {
		SET_ST(_content, x, y, stone);
		bool check_aligned = check_aligned(x, y, true); // if true => double three
		SET_ST(_content, x, y, 0);
		return check_aligned;
	}
	return true;
}

int		Board::putStone(int x, int y, int stone, bool test) {
/*
put a stone at 'x' 'y' with id 'stone'
this function put a stone and, if needed, destroy some stones
*/
	if (x >= BOARD_SZ || y >= BOARD_SZ)
		throw OutOfRangeException();

	SET_ST(_content, x, y, stone);
	if (!test)
		--_remain_places;

	// destroy some stones if needed
	std::vector< std::array<int, 2> > destroyed = check_destroyable(x, y, stone);
	for (std::array<int, 2> dest : destroyed) {
		SET_ST(_content, dest[0], dest[1], 0);
		++_remain_places;
		if (!test)
			_game.getPlayer(stone).incrNbDestroyedStones();
	}

	// ????
	// if (!test)
	// 	check_winner();

	return destroyed.size();
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
			color = {{ C_EOC, C_EOC }};
			if (c.get(x, y) == 1)
				color = {{ C_WHITE, C_F_WHITE }};
			else if (c.get(x, y) == 2)
				color = {{ C_RED, C_F_RED }};
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

MasterBoard::MasterBoard(Game &game) : Board(game) {
}

void MasterBoard::setIsWin(int x, int y, bool val) {
	_isWin[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y, int val) {
	_markerColor[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y) {
	setMarkerColor(x, y, -1);
}
bool MasterBoard::getIsWin(int x, int y) {
	return _isWin[y][x];
}
int MasterBoard::getMarkerColor(int x, int y) {
	return _markerColor[y][x];
}
