#include <iostream>
#include <thread>
#include "Game.hpp"

Game *game;

void runThread() {
	game->run();
}

int main(void) {
	game = new Game();
	game->board->set(5, 8, 1);
	std::thread gameThread(runThread);
	game->gui->run();
	gameThread.join();
	return 0;
}
