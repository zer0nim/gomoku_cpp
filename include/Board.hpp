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
	private:
		std::array<uint64_t, BOARD_SZ> _content = {};
};

std::ostream & operator << (std::ostream &out, const Board &c);

#endif