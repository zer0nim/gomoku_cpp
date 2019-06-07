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

int Board::putStone(int x, int y, int stone) {
/*
put a stone at 'x' 'y' with id 'stone'
this function put a stone and, if needed, destroy some stones
*/
	if (x >= BOARD_SZ || y >= BOARD_SZ)
		throw OutOfRangeException();

	SET_ST(_content, x, y, stone);
	--_remain_places;

	// destroy some stones if needed
	std::vector< std::array<int, 2> > destroyed = check_destroyable(x, y, stone);

	for (std::array<int, 2> dest : destroyed) {
		SET_ST(_content, dest[0], dest[1], 0);
		++_remain_places;
		_game.getPlayer(stone).incrNbDestroyedStones();
	}

	// check if there is a winner
	// check_winner()

	return destroyed.size();
}

// print the board (with colors)
std::ostream & operator << (std::ostream &out, const Board &c) {
	(void)c;
	return out;
	// std::array<std::string, 2> color;

	// out << '*';
	// for (int i = 0; i < BOARD_SZ; ++i)
	// 	out << "---";
	// out << '*' << std::endl;
	// for (int y = 0; y < BOARD_SZ; ++y) {
	// 	out << '|';
	// 	for (int x = 0; x < BOARD_SZ; ++x) {
	// 		color = {C_EOC, C_EOC};
	// 		if (c.get(x, y) == 1)
	// 			color = {C_WHITE, C_F_WHITE};
	// 		else if (c.get(x, y) == 2)
	// 			color = {C_RED, C_F_RED};
	// 		out << color[0] + color[1] + " . " + C_EOC;
	// 	}
	// 	out << "|" << std::endl;
	// }
	// out << '*';
	// for (int i = 0; i < BOARD_SZ; ++i)
	// 	out << "---";
	// out << '*' << std::endl;

	// return out;
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
void MasterBoard::setMarkerTxt(int x, int y, std::string txt, int color) {
	_markerTxt[y][x].txt = txt;
	_markerTxt[y][x].color = color;
}
void MasterBoard::setMarkerTxt(int x, int y, std::string txt) {
	setMarkerTxt(x, y, txt, 0xFFFFFFFF);
}
void MasterBoard::setMarkerTxt(int x, int y) {
	setMarkerTxt(x, y, 0, 0);
}
bool MasterBoard::getIsWin(int x, int y) {
	return _isWin[y][x];
}
int MasterBoard::getMarkerColor(int x, int y) {
	return _markerColor[y][x];
}
struct markerTxt MasterBoard::getMarkerTxt(int x, int y) {
	return _markerTxt[y][x];
}
