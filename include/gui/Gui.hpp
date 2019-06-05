#ifndef GUI_HPP
#define GUI_HPP

#include "Define.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Gui {
	public:
		Gui(Board *_board);
		void init();  // init the gui -> called by Gui
		void run();  // run the Gui: handle events, draw, ...
		virtual ~Gui();
	protected:
		Board *board;
		void event();  // handle events -> called by run
		void draw();  // draw the board -> called by run
		sf::Color getColor(int stone);  // get color corresponding to the player
		sf::Color getRevColor(int stone);  // get the reverse color corresponding to the player
		sf::RenderWindow *win;
};

#endif