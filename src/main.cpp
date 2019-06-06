#include <iostream>
#include <thread>
#include "Game.hpp"

Game *game;

void runThread() {
	game->run();
}

int main(void) {
	game = new Game();
	std::thread gameThread(runThread);
	game->gui->run();
	gameThread.join();
	return 0;
}
