#include "gui/Gui.hpp"

Gui::Gui(Board *_board) {
	board = _board;
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
			win->close();
	}
}

void Gui::draw() {
	sf::RenderTexture renderTexture;

	if (!renderTexture.create(GUI_WIN_W, GUI_WIN_H))
		exit(EXIT_FAILURE);
	renderTexture.clear();

	// draw background
	sf::RectangleShape bg(sf::Vector2f(GUI_BOARD_SZ, GUI_BOARD_SZ));
	bg.setFillColor(sf::Color(246, 170, 73));
	bg.setPosition(GUI_BOARD_START_X, 0);
	renderTexture.draw(bg);

	// draw all the boards lines
	float step = GUI_BOARD_SZ / BOARD_SZ;
	sf::RectangleShape line(sf::Vector2f(GUI_BOARD_SZ - step + step / 10, step / 10));
	line.setFillColor(sf::Color(0, 0, 0));
	for (int y=0; y < BOARD_SZ; y++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) - step / 10, (step*0.5) + y*step);
		renderTexture.draw(line);
	}
	line.rotate(90);
	for (int x=0; x < BOARD_SZ; x++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) + x*step, step / 2);
		renderTexture.draw(line);
	}
	sf::CircleShape point(step/5);
	point.setFillColor(sf::Color(0, 0, 0));
	for (int x=(int)(BOARD_SZ/2)%6; x < BOARD_SZ; x+=6) {
		for (int y=(int)(BOARD_SZ/2)%6; y < BOARD_SZ; y+=6) {
			float xwin = GUI_BOARD_START_X + step*0.5 - step/5 + step * x;
			float ywin = step*0.5 - step/7.5 + step * y;
			point.setPosition(xwin, ywin);
			renderTexture.draw(point);
		}
	}

	// draw stones
	sf::CircleShape stone(step/3);
	for (int x=0; x < BOARD_SZ; x++) {
		for (int y=0; y < BOARD_SZ; y++) {
			if (1) {
				float xwin = GUI_BOARD_START_X + step*0.5 - step/3 + step * x;
				float ywin = step*0.5 - step/3 + step * y;
				stone.setFillColor(getColor(1));
				stone.setPosition(xwin, ywin);
				renderTexture.draw(stone);
			}
		}
	}

	renderTexture.display();
	const sf::Texture& texture = renderTexture.getTexture();
	sf::Sprite sprite(texture);
	win->draw(sprite);
	win->display();
}

sf::Color Gui::getColor(int stone) {
	if (stone == 1)
		return sf::Color(GUI_COLOR_1);
	else if (stone == 2)
		return sf::Color(GUI_COLOR_2);
}

sf::Color Gui::getRevColor(int stone) {
	if (stone == 1)
		return sf::Color(GUI_COLOR_2);
	else if (stone == 2)
		return sf::Color(GUI_COLOR_1);
}

void Gui::run() {
	while (win->isOpen()) {
		Gui::event();
		Gui::draw();
	}
}

Gui::~Gui() {
}