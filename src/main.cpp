#include <iostream>
#include <pthread.h>
#include "Game.hpp"
#include "utils/Stats.hpp"

void *runThread(void *gameV) {
	Game	*game = reinterpret_cast<Game *>(gameV);

	game->run();
	pthread_exit(NULL);
}

int main(void) {
	Game game;

	std::srand(std::time(nullptr));  // init random

	pthread_t threadT;
	if (pthread_create(&threadT, NULL, runThread, reinterpret_cast<void*>(&game))) {
		std::cerr << "Fail to create thread for game" << std::endl;
		return 1;
	}

	game.getGui().run();
	pthread_cancel(threadT);
	Stats::printStats();
	return 0;
}
