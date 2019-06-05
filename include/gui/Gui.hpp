#ifndef GUI_HPP
#define GUI_HPP

#include "Define.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Gui {
	public:
		Gui();
		void init();
		void run();
		virtual ~Gui();
	protected:
		void event();
		void draw();
		sf::RenderWindow *win;
};

#endif