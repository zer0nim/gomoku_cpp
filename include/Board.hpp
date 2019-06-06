#ifndef BOARD_HPP
# define BOARD_HPP

# include "Define.hpp"
# include <array>
# include <iostream>

# define GET_ST(boardC, x, y) ((boardC[y] & (3ull << (x*3))) >> (x*3))
# define SET_ST(boardC, x, y, val) (boardC[y] = (boardC[y] & (((1ull << (BOARD_SZ*3))-1) ^ (3ull << (x*3)))) | (static_cast<uint64_t>(val) << (x*3)))

# define GET_VUL(boardC, x, y) ((boardC[y] & (4ull << (x*3))) >> (x*3 + 2))
# define SET_VUL(boardC, x, y, val) (boardC[y] = (boardC[y] & (((1ull << (BOARD_SZ*3))-1) ^ (4ull << (x*3)))) | (static_cast<uint64_t>(val) << (x*3 + 2)))


class Board {
	public:
		Board();
		virtual	~Board();

		int get(int x, int y) const;
		void set(int x, int y, int stone);
		bool isEmpty(int x, int y) const;
		bool isStone(int x, int y, int stone) const;
		bool isLastStone(int x, int y);
	private:
		std::array<uint64_t, BOARD_SZ> _content = {};
		int _lastStone[2];
};

class MasterBoard : public Board {
	public:
		MasterBoard();
		// setter
		void setIsWin(int x, int y, bool val);
		void setMarkerColor(int x, int y, int val);
		void setMarkerColor(int x, int y);  // reset
		// getter
		bool getIsWin(int x, int y);
		int getMarkerColor(int x, int y);
	private:
		bool _isWin[BOARD_SZ][BOARD_SZ];
		int _markerColor[BOARD_SZ][BOARD_SZ];
};

std::ostream & operator << (std::ostream &out, const Board &c);

#endif