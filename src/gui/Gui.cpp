#include "gui/Gui.hpp"
#include "Game.hpp"

Gui::Gui(Game &_game) : game(_game) {
	Gui::init();
}

void Gui::init() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	win = new sf::RenderWindow(sf::VideoMode(GUI_WIN_W, GUI_WIN_H), "Gomoku", sf::Style::Default, settings);
}

void Gui::event() {
	sf::Event event;
	while (win->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			quit();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!_clicked){
			sf::Vector2i localPosition = sf::Mouse::getPosition(*win);
			if (localPosition.x > GUI_BOARD_START_X && localPosition.x < GUI_BOARD_START_X + GUI_BOARD_SZ &&
			localPosition.y > 0 && localPosition.y < GUI_BOARD_SZ) {
				int realX = (int)(((float)localPosition.x - GUI_BOARD_START_X) / GUI_BOARD_SZ * BOARD_SZ);
				int realY = (int)((float)localPosition.y / GUI_BOARD_SZ * BOARD_SZ);
				game.getPlayerAct().click(realX, realY);
			}
		}
		_clicked = true;
	}
	else
		_clicked = false;
}

void Gui::draw() {
	win->clear();

	// draw background
	sf::RectangleShape bg(sf::Vector2f(GUI_BOARD_SZ, GUI_BOARD_SZ));
	bg.setFillColor(sf::Color(246, 170, 73));
	bg.setPosition(GUI_BOARD_START_X, 0);
	win->draw(bg);

	// draw all the _boards lines
	float step = GUI_BOARD_SZ / BOARD_SZ;
	sf::RectangleShape line(sf::Vector2f(GUI_BOARD_SZ - step, step / 10));
	line.setFillColor(sf::Color(0, 0, 0));
	for (int y=0; y < BOARD_SZ; y++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) - step / 10, (step*0.5) + y*step);
		win->draw(line);
	}
	line.rotate(90);
	for (int x=0; x < BOARD_SZ; x++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) + x*step, step / 2);
		win->draw(line);
	}
	sf::CircleShape point(step/5);
	point.setFillColor(sf::Color(0, 0, 0));
	for (int x=(int)(BOARD_SZ/2)%6; x < BOARD_SZ; x+=6) {
		for (int y=(int)(BOARD_SZ/2)%6; y < BOARD_SZ; y+=6) {
			float xwin = GUI_BOARD_START_X + step*0.5 - step/5 + step * x;
			float ywin = step*0.5 - step/7.5 + step * y;
			point.setPosition(xwin, ywin);
			win->draw(point);
		}
	}

	// draw stones
	sf::CircleShape stone(step/3);
	sf::CircleShape marker(step/6);
	stone.setOutlineThickness(step/12);
	for (int x=0; x < BOARD_SZ; x++) {
		for (int y=0; y < BOARD_SZ; y++) {
			if (!game.getBoard().isEmpty(x, y)) {
				float xwin = GUI_BOARD_START_X + step*0.5 - step/3 + step * x;
				float ywin = step*0.5 - step/3 + step * y;
				stone.setFillColor(getColor(game.getBoard().get(x, y)));
				// set outline color
				if (game.getBoard().getIsWin(x, y))
					stone.setOutlineColor(sf::Color(GUI_COLOR_WIN));
				else if (game.getBoard().isLastStone(x, y))
					stone.setOutlineColor(sf::Color(GUI_COLOR_LAST_STONE));
				else
					stone.setOutlineColor(getRevColor(game.getBoard().get(x, y)));
				stone.setPosition(xwin, ywin);
				win->draw(stone);
			}
			if (game.getBoard().getMarkerColor(x, y) != -1) {
				float xwin = GUI_BOARD_START_X + step*0.5 - step/6 + step * x;
				float ywin = step*0.5 - step/6 + step * y;
				marker.setFillColor(sf::Color(game.getBoard().getMarkerColor(x, y)));
				marker.setPosition(xwin, ywin);
				win->draw(marker);
			}
		}
	}
	win->display();
}

sf::Color Gui::getColor(int stone) const {
	if (stone == 1)
		return sf::Color(GUI_COLOR_1);
	else if (stone == 2)
		return sf::Color(GUI_COLOR_2);
	return sf::Color::Red;
}

sf::Color Gui::getRevColor(int stone) const {
	if (stone == 1)
		return sf::Color(GUI_COLOR_2);
	else if (stone == 2)
		return sf::Color(GUI_COLOR_1);
	return sf::Color::Red;
}

void Gui::run() {
	sf::Clock clock;
	while (win->isOpen()) {
		Gui::event();
		Gui::draw();

		// wait to have a clean rate in the loop
		sf::Time elapsed = clock.restart();
		sf::Time slp = sf::milliseconds(GUI_TIME_LOOP) - elapsed;
		sf::sleep(slp);
	}
}

Gui::~Gui() {
}

void Gui::quit() {
	game.quit();
	win->close();
}