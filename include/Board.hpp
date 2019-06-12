#ifndef BOARD_HPP
# define BOARD_HPP

# include "Define.hpp"
# include <array>
# include <vector>
# include <tuple>
# include <iostream>
# include <exception>

# define GET_ST(boardC, x, y) (static_cast<int>((boardC[y] & (3ull << (x*3))) >> (x*3)))
# define SET_ST(boardC, x, y, val) (boardC[y] = (boardC[y] & (((1ull << (BOARD_SZ*3))-1) ^ (3ull << (x*3)))) | (static_cast<uint64_t>(val) << (x*3)))

# define GET_VUL(boardC, x, y) (static_cast<bool>((boardC[y] & (4ull << (x*3))) >> (x*3 + 2)))
# define SET_VUL(boardC, x, y, val) (boardC[y] = (boardC[y] & (((1ull << (BOARD_SZ*3))-1) ^ (4ull << (x*3)))) | (static_cast<uint64_t>(val) << (x*3 + 2)))

// _content[y] & MASK_STONE -> get only stones and ignore vulnerability
# define MASK_STONE 0b0000000011011011011011011011011011011011011011011011011011011011ull

# define OP_ST(stone) (!(stone-1) + 1)

struct markerTxt {
	std::string txt;
	int color;
};

class Game;

class Board {
	public:
		Board(Game &game);
		Board(Board const &src);
		virtual	~Board();

		Board &operator=(Board const &rhs);

		int		get(int x, int y) const;
		void	set(int x, int y, int stone);
		bool	isVul(int x, int y) const;
		void	setVul(int x, int y, bool vul);
		bool	isEmpty(int x, int y) const;
		bool	isStone(int x, int y, int stone) const;
		bool	isLastStone(int x, int y);
		std::string getStrHashable();

		int		putStone(int x, int y, int stone);
		bool	isFreeThreeDir(int x, int y, int stone, int addx, int addy);
		bool	isAllowed(int x, int y, int stone);
		bool								checkVulnerability(int x, int y);
		void								check_winner();
		std::vector< std::array<int, 2> >	checkDestroyable(int x, int y, int stone);
		std::tuple<bool, bool>				checkAlignedDir(int x, int y, int stone, int addx, int addy, bool checkOnly=false);
		bool								checkAligned(int x, int y, bool checkOnly=false);

		std::array<uint64_t, BOARD_SZ>	getContent() const;
		std::array<int, 2>				getLastStone() const;
		std::array<bool, 2>				getIsVulVict() const;

		Game	&game;

		class OutOfRangeException: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Error: x:y is out of the board range";
				}
		};
	protected:
		bool	_softMode;
	private:
		Board();

		std::array<uint64_t, BOARD_SZ>	_content = {};
		std::array<int, 2>				_lastStone;
		std::array<bool, 2>				_isVulVict = {};
};

std::ostream & operator << (std::ostream &out, const Board &c);

class MasterBoard : public Board {
	public:
		MasterBoard(Game &game);
		// setter
		void	setIsWin(int x, int y, bool val);
		void	setMarkerColor(int x, int y, int val);
		void	setMarkerColor(int x, int y);  // reset
		void	setMarkerTxt(int x, int y, std::string txt, int color);
		void	setMarkerTxt(int x, int y, std::string txt);
		void	setMarkerTxt(int x, int y);  // reset
		void	incrRemainPlaces();
		void	decrRemainPlaces();
		// getter
		bool				getIsWin(int x, int y) const;
		int					getMarkerColor(int x, int y) const;
		struct markerTxt	getMarkerTxt(int x, int y) const;
		int					getRemainPlaces() const;
		// others
		void				resetDebug(int x, int y);  // reset all debug markers in xy
		void				resetDebug();  // reset all debug marker, txt, ...
	private:

		int	_remain_places;
		std::array< std::array<bool, BOARD_SZ> , BOARD_SZ> _isWin = {};
		std::array< std::array<int, BOARD_SZ> , BOARD_SZ> _markerColor = {};
		std::array< std::array<struct markerTxt, BOARD_SZ> , BOARD_SZ> _markerTxt = {};
};

#endif
