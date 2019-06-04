#ifndef BOARD_HPP
# define BOARD_HPP

# include "Define.hpp"
# include <array>

class Board {
	public:
		Board();
		virtual	~Board();
	private:
		std::array<char, BOARD_SZ> _content;
};

#endif