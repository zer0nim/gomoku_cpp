#ifndef GUI_HPP
#define GUI_HPP

#include "Define.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define GUI_WIN_W 800
#define GUI_WIN_H (int)GUI_WIN_W * 0.7
#define GUI_BOARD_SZ GUI_WIN_H
#define GUI_BOARD_START_X GUI_WIN_W - GUI_BOARD_SZ

// all colors are in format RGBA
#define GUI_COLOR_1   0x000000FF
#define GUI_COLOR_2   0xFFFFFFFF
#define GUI_COLOR_WIN 0x00FF00FF

class Gui {
	public:
		Gui(MasterBoard *_board);
		void init();  // init the gui -> called by Gui
		void run();  // run the Gui: handle events, draw, ...
		virtual ~Gui();
	protected:
		MasterBoard *board;
		void event();  // handle events -> called by run
		void draw();  // draw the board -> called by run
		sf::Color getColor(int stone);  // get color corresponding to the player
		sf::Color getRevColor(int stone);  // get the reverse color corresponding to the player
		sf::RenderWindow *win;
};

#endif