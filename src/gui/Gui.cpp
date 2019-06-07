#include "gui/Gui.hpp"
#include "Game.hpp"

Gui::Gui(Game &game) :
	game(game),
	_typeGui(GUI_TYPE_MENU)
{
	Gui::init();
}

void Gui::init() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	_win = new sf::RenderWindow(sf::VideoMode(GUI_WIN_W, GUI_WIN_H), "Gomoku", sf::Style::Default, settings);
	if (!_font.loadFromFile(GUI_DEFAULT_FONT))
		exit(EXIT_FAILURE);
}

void Gui::eventMenu() {
	sf::Event event;
	while (_win->pollEvent(event)) {
		if (event.type == sf::Event::Closed
		|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			quit();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
			game.startGame();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
			game.nextPlayer();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
			game.gameInfo.playerAI[game.getPlayerActId()] = !game.gameInfo.playerAI[game.getPlayerActId()];
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
			game.gameInfo.difficulty += 1;
			if (game.gameInfo.difficulty >= NB_DIFICULTY_LEVEL)
				game.gameInfo.difficulty = 0;
		}
	}
}

void Gui::eventGame() {
	sf::Event event;
	while (_win->pollEvent(event)) {
		if (event.type == sf::Event::Closed
		|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			quit();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
			game.startMenu();
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!_clicked){
			sf::Vector2i localPosition = sf::Mouse::getPosition(*_win);
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

void Gui::event() {
	if (getGuiType() == GUI_TYPE_MENU)
		eventMenu();
	else if (getGuiType() == GUI_TYPE_GAME)
		eventGame();
}

void Gui::drawMenu() {
	// draw left band
	sf::RectangleShape rect(sf::Vector2f((GUI_WIN_W - GUI_BOARD_SZ) * 0.8, GUI_WIN_H * 0.4));
	double textSize = GUI_WIN_H * 0.01;
	rect.setOutlineThickness(textSize);
	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(GUI_TEXT_SIZE);
	for (int i=1; i <= 2; i++) {
		// draw player rectangle
		int xwin = (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		int ywin = GUI_WIN_H * 0.05 + (GUI_WIN_H/2) * (i-1);
		rect.setFillColor(getColor(i));
		if (game.getPlayerActId() == i)
			rect.setOutlineColor(sf::Color(GUI_COLOR_PLAYER_ACT));
		else
			rect.setOutlineColor(getRevColor(i));
		rect.setPosition(xwin, ywin);
		_win->draw(rect);

		// player info
		// Player #
		// Capture: x/10
		// x.xs -> exec time
		xwin += (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		ywin += (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		text.setFillColor(getRevColor(i));
		std::string txt;
		// AI or Player
		if (game.gameInfo.playerAI[i])
			txt = "[A] AI";
		else
			txt = "[A] Real player";
		text.setString(txt);
		text.setPosition(xwin, ywin);
		_win->draw(text);
		ywin += GUI_LINE_SPACE;
	}
	// draw player rectangle
	int xwin = (GUI_WIN_W - GUI_BOARD_SZ) * 1.2;
	int ywin = (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
	text.setFillColor(sf::Color(GUI_COLOR_TEXT_MENU));
	std::string txt;
	// start game
	txt = "[Return] to start game";
	text.setString(txt);
	text.setPosition(xwin, ywin);
	_win->draw(text);
	ywin += GUI_LINE_SPACE;
	// change selected player
	txt = "[Space] to change selected player";
	text.setString(txt);
	text.setPosition(xwin, ywin);
	_win->draw(text);
	ywin += GUI_LINE_SPACE;
	// change selected player
	txt = "[D] difficulty: " + std::to_string(game.gameInfo.difficulty) +
		  " (from 0 to " + std::to_string(NB_DIFICULTY_LEVEL-1) + ")";
	text.setString(txt);
	text.setPosition(xwin, ywin);
	_win->draw(text);
	ywin += GUI_LINE_SPACE;
}

void Gui::drawGame() {
	// draw left band
	sf::RectangleShape playerRect(sf::Vector2f((GUI_WIN_W - GUI_BOARD_SZ) * 0.8, GUI_WIN_H * 0.4));
	playerRect.setOutlineThickness(GUI_WIN_H * 0.01);
	sf::Text playerText;
	playerText.setFont(_font);
	playerText.setCharacterSize(GUI_TEXT_SIZE);
	for (int i=1; i <= 2; i++) {
		// draw player rectangle
		int xwin = (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		int ywin = GUI_WIN_H * 0.05 + (GUI_WIN_H/2) * (i-1);
		playerRect.setFillColor(getColor(i));
		if (game.getPlayerActId() == i)
			playerRect.setOutlineColor(sf::Color(GUI_COLOR_PLAYER_ACT));
		else
			playerRect.setOutlineColor(getRevColor(i));
		playerRect.setPosition(xwin, ywin);
		_win->draw(playerRect);

		// player info
		// Player #
		// Capture: x/10
		// x.xs -> exec time
		xwin += (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		ywin += (GUI_WIN_W - GUI_BOARD_SZ) * 0.1;
		playerText.setFillColor(getRevColor(i));
		// player type
		playerText.setString(game.getPlayer(i).getType());
		playerText.setPosition(xwin, ywin);
		_win->draw(playerText);
		ywin += GUI_LINE_SPACE;
		// player #
		playerText.setString("Player " + std::to_string(i));
		playerText.setPosition(xwin, ywin);
		_win->draw(playerText);
		ywin += GUI_LINE_SPACE;
		// captured
		playerText.setString("Captured: " + std::to_string(game.getPlayer(i).getNbDestroyedStones()) +
							 "/" + std::to_string(NB_DESTROYED_VICTORY));
		playerText.setPosition(xwin, ywin);
		_win->draw(playerText);
		ywin += GUI_LINE_SPACE;
		// exec time
		char *str;
		asprintf(&str, "%.2lfs", game.getPlayer(i).getTimeLastMove());
		playerText.setString(str);
		playerText.setPosition(xwin, ywin);
		_win->draw(playerText);
		ywin += GUI_LINE_SPACE;
	}

	// draw background
	sf::RectangleShape bg(sf::Vector2f(GUI_BOARD_SZ, GUI_BOARD_SZ));
	bg.setFillColor(sf::Color(GUI_COLOR_BOARD_BG));
	bg.setPosition(GUI_BOARD_START_X, 0);
	_win->draw(bg);

	// draw all the _boards lines
	float step = GUI_BOARD_SZ / BOARD_SZ;
	sf::RectangleShape line(sf::Vector2f(GUI_BOARD_SZ - step, step / 10));
	line.setFillColor(sf::Color(0, 0, 0));
	for (int y=0; y < BOARD_SZ; y++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) - step / 10, (step*0.5) + y*step);
		_win->draw(line);
	}
	line.rotate(90);
	for (int x=0; x < BOARD_SZ; x++) {
		line.setPosition(GUI_BOARD_START_X + (step*0.5) + x*step, step / 2);
		_win->draw(line);
	}
	sf::CircleShape point(step/5);
	point.setFillColor(sf::Color(0, 0, 0));
	for (int x=(int)(BOARD_SZ/2)%6; x < BOARD_SZ; x+=6) {
		for (int y=(int)(BOARD_SZ/2)%6; y < BOARD_SZ; y+=6) {
			float xwin = GUI_BOARD_START_X + step*0.5 - step/5 + step * x;
			float ywin = step*0.5 - step/7.5 + step * y;
			point.setPosition(xwin, ywin);
			_win->draw(point);
		}
	}

	// draw stones
	sf::CircleShape stone(step/3);
	sf::CircleShape marker(step/6);
	sf::Text text;
	sf::Text text2;
	text.setFont(_font);
	text.setCharacterSize(step*0.8);
	text2.setFont(_font);
	text2.setCharacterSize(step*0.8);
	text2.setStyle(sf::Text::Bold);
	stone.setOutlineThickness(step/14);
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
				_win->draw(stone);
			}
			if (game.getBoard().getMarkerColor(x, y) != -1) {
				float xwin = GUI_BOARD_START_X + step*0.5 - step/6 + step * x;
				float ywin = step*0.5 - step/6 + step * y;
				marker.setFillColor(sf::Color(game.getBoard().getMarkerColor(x, y)));
				marker.setPosition(xwin, ywin);
				_win->draw(marker);
			}
			if (game.getBoard().getMarkerTxt(x, y).txt != "") {
				float xwin = GUI_BOARD_START_X + step * x + step*0.2;
				float ywin = step * y;
				text2.setFillColor(sf::Color(getComplementaryColor(game.getBoard().getMarkerTxt(x, y).color)));
				text2.setString(game.getBoard().getMarkerTxt(x, y).txt);
				text2.setPosition(xwin, ywin);
				text.setFillColor(sf::Color(game.getBoard().getMarkerTxt(x, y).color));
				text.setString(game.getBoard().getMarkerTxt(x, y).txt);
				text.setPosition(xwin, ywin);
				_win->draw(text2);
				_win->draw(text);
			}
		}
	}
}

void Gui::draw() {
	_win->clear(sf::Color(GUI_COLOR_BG));
	if (getGuiType() == GUI_TYPE_MENU)
		drawMenu();
	else if (getGuiType() == GUI_TYPE_GAME)
		drawGame();
	_win->display();
}

int Gui::getComplementaryColor(int color) const {
	int r = 255 - ((color & 0xFF000000) >> 24);
	int g = 255 - ((color & 0x00FF0000) >> 16);
	int b = 255 - ((color & 0x0000FF00) >> 8);
	int a = (color & 0x000000FF);
	return (r << 24) | (g << 16) | (b << 8) | a;
}

sf::Color Gui::getColor(int stone) const {
	return sf::Color(game.getPlayer(stone).getColor());
}
sf::Color Gui::getRevColor(int stone) const {
	return sf::Color(getComplementaryColor(game.getPlayer(stone).getColor()));
}
typeGui Gui::getGuiType() const { return _typeGui; };
void Gui::setGuiType(typeGui newType) {
	_typeGui = newType;
}

void Gui::run() {
	sf::Clock clock;
	while (_win->isOpen()) {
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
	_win->close();
}