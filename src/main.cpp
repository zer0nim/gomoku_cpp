#include <iostream>
#include <pthread.h>
#include "Game.hpp"

void *runThread(void *gameV) {
	Game	*game = reinterpret_cast<Game *>(gameV);

	game->run();
	pthread_exit(NULL);
}

int main(void) {
	Game game;

	pthread_t threadT;
	if (pthread_create(&threadT, NULL, runThread, reinterpret_cast<void*>(&game))) {
		std::cerr << "Fail to create thread for game" << std::endl;
		return 1;
	}

	game.getGui().run();
	pthread_cancel(threadT);
	return 0;
}
