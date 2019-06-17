#include "Board.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>
#include <algorithm>

Board::Board(Game &game)
: game(game), _softMode(true), _isVulVict{false, false} {
	_lastStone[0] = 0;
	_lastStone[1] = 0;
}

Board::Board(Board const &src): game(src.game) {
	*this = src;
}

Board::~Board() {
}

Board &Board::operator=(Board const &rhs) {
	if (this != &rhs) {
		this->_softMode = true;
		this->_isVulVict = rhs.getIsVulVict();
		this->_lastStone = rhs.getLastStone();
		this->_content = rhs.getContent();
	}
	return *this;
}

int Board::get(int x, int y) const {
	return GET_ST(_content, x, y);
}
void Board::set(int x, int y, int stone) {
	SET_ST(_content, x, y, stone);
	_lastStone[0] = x;
	_lastStone[1] = y;
}
bool Board::isVul(int x, int y) const {
	return GET_VUL(_content, x, y);
}
void Board::setVul(int x, int y, bool vul) {
	SET_VUL(_content, x, y, vul);
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
std::size_t Board::getHash() {
	std::size_t contentHash = 0;
	for (int i=0; i < BOARD_SZ; i++)
		contentHash += std::hash<uint64_t>{}(_content[i] & MASK_STONE);
	return contentHash;
}

bool Board::checkVulnerability(int x, int y) {
/*
check the vulnerability of one stone
*/
	int stone = GET_ST(_content, x, y);
	if (stone == 0)
		return false;

	// this tab contains all configuration to vulnerables stones
	// x1, y1, x2, y2, x3, y3
	std::array<std::array<int, 6>, 8> vul_conf = {{
		{{ x-1, y, x+1, y, x+2, y }},
		{{ x+1, y, x-1, y, x-2, y }},
		{{ x, y-1, x, y+1, x, y+2 }},
		{{ x, y+1, x, y-1, x, y-2 }},
		{{ x-1, y-1, x+1, y+1, x+2, y+2 }},
		{{ x-1, y+1, x+1, y-1, x+2, y-2 }},
		{{ x+1, y-1, x-1, y+1, x-2, y+2 }},
		{{ x+1, y+1, x-1, y-1, x-2, y-2 }},
	}};

	for (std::array<int, 6> conf : vul_conf) {
		// for 4 stones: abcd with b is x y -> a=x1y1 b=xy c=x2y2 d=x3y3
		if (conf[0] >= 0 && conf[0] < BOARD_SZ && conf[2] >= 0 && conf[2] < BOARD_SZ && conf[4] >= 0 && conf[4] < BOARD_SZ &&
			conf[1] >= 0 && conf[1] < BOARD_SZ && conf[3] >= 0 && conf[3] < BOARD_SZ && conf[5] >= 0 && conf[5] < BOARD_SZ &&
			stone == GET_ST(_content, conf[2], conf[3]) &&
			GET_ST(_content, conf[0], conf[1]) != stone && GET_ST(_content, conf[4], conf[5]) != stone &&
			GET_ST(_content, conf[0], conf[1]) != GET_ST(_content, conf[4], conf[5]) &&
			(GET_ST(_content, conf[0], conf[1]) == 0 || GET_ST(_content, conf[4], conf[5]) == 0))
		{
			SET_VUL(_content, x, y, true);
			return true;
		}
	}

	SET_VUL(_content, x, y, false);
	return false;
}

void	Board::check_winner() {
	for (int y = 0; y < BOARD_SZ; ++y)
		for (int x = 0; x < BOARD_SZ; ++x)
			checkVulnerability(x, y);

	std::array<bool, 2>	tmpIsVulVict = {};
	for (int y = 0; y < BOARD_SZ; ++y)
		for (int x = 0; x < BOARD_SZ; ++x)
			if (GET_ST(_content, x, y) != 0)
				tmpIsVulVict[GET_ST(_content, x, y) - 1] = tmpIsVulVict[GET_ST(_content, x, y) - 1] || checkAligned(x, y);
	_isVulVict = tmpIsVulVict;
}

std::vector< std::array<int, 2> >	Board::checkDestroyable(int x, int y, int stone) {
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
		if (conf[0] >= 0 && conf[0] < BOARD_SZ && conf[2] >= 0 && conf[2] < BOARD_SZ && conf[4] >= 0 && conf[4] < BOARD_SZ &&
			conf[1] >= 0 && conf[1] < BOARD_SZ && (conf[3] >= 0 && conf[3] < BOARD_SZ) && conf[5] >= 0 && conf[5] < BOARD_SZ &&
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

std::tuple<bool, bool> Board::checkAlignedDir(int x, int y, int stone, int addx, int addy, bool checkOnly) {
/*
check the alignement in one direction (given by addx and addy)
if checkOnly -> don't update the player victory
return bool (if 5 or more aligned) and bool (if he aligneement is not vulnerable)
*/
	int nbAligned = 1;
	std::tuple<bool, bool> isAlignedVuln = { false, false };
	if (GET_VUL(_content, x, y))
		isAlignedVuln = { true, true };
	int nbAlignedNonVul = 1;
	int newX = x + addx;
	int newY = y + addy;
	while (newX >= 0 && newX < BOARD_SZ && newY >= 0 && newY < BOARD_SZ) {
		if (GET_ST(_content, newX, newY) == stone) {
			if (GET_VUL(_content, newX, newY))
				std::get<0>(isAlignedVuln) = true;
			if (! std::get<0>(isAlignedVuln))
				nbAlignedNonVul += 1;
			nbAligned += 1;
		}
		else {
			break;
		}
		newX += addx;
		newY += addy;
	}
	newX = x - addx;
	newY = y - addy;
	while (newX >= 0 && newX < BOARD_SZ && newY >= 0 && newY < BOARD_SZ) {
		if (GET_ST(_content, newX, newY) == stone) {
			if (GET_VUL(_content, newX, newY))
				std::get<1>(isAlignedVuln) = true;
			if (! std::get<1>(isAlignedVuln))
				nbAlignedNonVul += 1;
			nbAligned += 1;
		}
		else {
			break;
		}
		newX -= addx;
		newY -= addy;
	}
	if (nbAligned >= NB_ALIGNED_VICTORY) {
		if (! checkOnly) {
			newX = x;
			newY = y;
			while (newX >= 0 && newX < BOARD_SZ && newY >= 0 && newY < BOARD_SZ) {
				if (GET_ST(_content, newX, newY) == stone) {
					if (!_softMode && (_isVulVict[stone - 1] || nbAlignedNonVul >= NB_ALIGNED_VICTORY))
						reinterpret_cast<MasterBoard*>(this)->setIsWin(newX, newY, true);
				}
				else {
					break;
				}
				newX += addx;
				newY += addy;
			}
			newX = x - addx;
			newY = y - addy;
			while (newX >=0 && newX < BOARD_SZ && newY >= 0 &&newY < BOARD_SZ) {
				if (GET_ST(_content, newX, newY) == stone) {
					if (!_softMode && (_isVulVict[stone - 1] || nbAlignedNonVul >= NB_ALIGNED_VICTORY))
						reinterpret_cast<MasterBoard*>(this)->setIsWin(newX, newY, true);
				}
				else {
					break;
				}
				newX -= addx;
				newY -= addy;
			}
		}
		if (nbAlignedNonVul >= NB_ALIGNED_VICTORY)
			return { true, true };  // nbAligned == OK, not_vulnerable == true;
		else
			return { true, false };  // nbAligned == OK, not_vulerable == false -> wait one turn before win;
	}
	return { false, false };  // nbAligned too low
}

bool	Board::checkAligned(int x, int y, bool checkOnly) {
/*
check if there is 5 or more aligned stones
also check vulnerability of all stones

if checkOnly -> don't update player victory

return the new state of _isVulVict
*/
	int stone = GET_ST(_content, x, y);
	if (stone == 0)
		return false;
	bool isAlignedTot = false;
	bool isNotVulTot = false;
	std::tuple<bool, bool> alignedDir;

	// horizontal
	alignedDir = checkAlignedDir(x, y, stone, 1, 0, checkOnly);
	isAlignedTot = isAlignedTot || std::get<0>(alignedDir);
	isNotVulTot = isNotVulTot || std::get<1>(alignedDir);
	// vertical
	alignedDir = checkAlignedDir(x, y, stone, 0, 1, checkOnly);
	isAlignedTot = isAlignedTot || std::get<0>(alignedDir);
	isNotVulTot = isNotVulTot || std::get<1>(alignedDir);
	// up diagonal
	alignedDir = checkAlignedDir(x, y, stone, 1, 1, checkOnly);
	isAlignedTot = isAlignedTot || std::get<0>(alignedDir);
	isNotVulTot = isNotVulTot || std::get<1>(alignedDir);
	// down diagonal
	alignedDir = checkAlignedDir(x, y, stone, 1, -1, checkOnly);
	isAlignedTot = isAlignedTot || std::get<0>(alignedDir);
	isNotVulTot = isNotVulTot || std::get<1>(alignedDir);

	if (isAlignedTot) {
		if (!checkOnly) {
			if (_isVulVict[stone - 1] || isNotVulTot)
				game.getPlayer(stone).setWinAligned();
			if (! isNotVulTot) // if vulnerable
				return true;
		}
		else {
			return true;
		}
	}
	return false;
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
	int newX = x - (addx * (lenFT >> 1));
	int newY = y - (addy * (lenFT >> 1));

	for (int i = 0; i < lenFT; ++i) {
		if (newX >= 0 && newX < BOARD_SZ && newY >= 0 && newY < BOARD_SZ)
			lst[i] = GET_ST(_content, newX, newY);
		newX += addx;
		newY += addy;
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
	if (checkDestroyable(x, y, stone).size() > 0)
		return true;

	int nbFreeThree = isFreeThreeDir(x, y, stone, 1, 0) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, 0, 1) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, 1, 1) ? 1 : 0;
	nbFreeThree += isFreeThreeDir(x, y, stone, -1, 1) ? 1 : 0;

	if (nbFreeThree >= 2) {
		set(x, y, stone);
		bool check_aligned = checkAligned(x, y, true); // if true => double three
		set(x, y, 0);
		return check_aligned;
	}
	return true;
}

int		Board::putStone(int x, int y, int stone) {
/*
put a stone at 'x' 'y' with id 'stone'
this function put a stone and, if needed, destroy some stones
*/
	if (x >= BOARD_SZ || y >= BOARD_SZ)
		throw OutOfRangeException();

	set(x, y, stone);
	if (!_softMode) {
		reinterpret_cast<MasterBoard*>(this)->decrRemainPlaces();
		game.getPlayer(stone).incrNbStones();
	}

	// destroy some stones if needed
	std::vector< std::array<int, 2> > destroyed = checkDestroyable(x, y, stone);
	for (std::array<int, 2> dest : destroyed) {
		set(dest[0], dest[1], 0);
		if (!_softMode) {
			reinterpret_cast<MasterBoard*>(this)->incrRemainPlaces();
			game.getPlayer(stone).incrNbDestroyedStones();
			game.getPlayer(OP_ST(stone)).decrNbStones();
		}
	}

	if (!_softMode)
		check_winner();

	return destroyed.size();
}

std::array<uint64_t, BOARD_SZ>	Board::getContent() const { return _content; }
std::array<int, 2>				Board::getLastStone() const { return _lastStone; }
std::array<bool, 2>				Board::getIsVulVict() const { return _isVulVict; }

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
				color = {{ C_RED, C_F_RED }};
			else if (c.get(x, y) == 2)
				color = {{ C_WHITE, C_F_WHITE }};
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

void	Board::printVuln() {
	std::array<std::string, 2> color;

	std::cout << '*';
	for (int i = 0; i < BOARD_SZ; ++i)
		std::cout << "---";
	std::cout << '*' << std::endl;
	for (int y = 0; y < BOARD_SZ; ++y) {
		std::cout << '|';
		for (int x = 0; x < BOARD_SZ; ++x) {
			color = {{ C_EOC, C_EOC }};
			if (this->isVul(x, y))
				color = {{ C_CYAN, C_F_CYAN }};
			std::cout << color[0] + color[1] + " . " + C_EOC;
		}
		std::cout << "|" << std::endl;
	}
	std::cout << '*';
	for (int i = 0; i < BOARD_SZ; ++i)
		std::cout << "---";
	std::cout << '*' << std::endl;
}

MasterBoard::MasterBoard(Game &game)
: Board(game), _remain_places(BOARD_SZ*BOARD_SZ) {
	_softMode = false;
	resetDebug();
}

void MasterBoard::resetDebug(int x, int y) {
	_isWin[y][x] = false;
	_markerColor[y][x] = 0;
	_markerTxt[y][x].txt = "";
	_markerTxt[y][x].color = 0;
}
void MasterBoard::resetDebug() {
	for (int x=0; x < BOARD_SZ; x++)
		for (int y=0; y < BOARD_SZ; y++)
			resetDebug(x, y);
}

void MasterBoard::setIsWin(int x, int y, bool val) {
	_isWin[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y, int val) {
	_markerColor[y][x] = val;
}
void MasterBoard::setMarkerColor(int x, int y) {
	setMarkerColor(x, y, 0);
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
bool MasterBoard::getIsWin(int x, int y) const {
	return _isWin[y][x];
}
int MasterBoard::getMarkerColor(int x, int y) const {
	return _markerColor[y][x];
}
struct markerTxt MasterBoard::getMarkerTxt(int x, int y) const {
	return _markerTxt[y][x];
}
void	MasterBoard::incrRemainPlaces() {
	_remain_places = _remain_places + 1 < BOARD_SZ*BOARD_SZ ? _remain_places + 1 : BOARD_SZ*BOARD_SZ;
}
void	MasterBoard::decrRemainPlaces() {
	_remain_places = _remain_places - 1 > 0 ? _remain_places - 1: 0;
}
int	MasterBoard::getRemainPlaces() const { return _remain_places; }
