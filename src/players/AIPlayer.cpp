#include "players/AIPlayer.hpp"
#include "Game.hpp"

AIPlayer::AIPlayer(Game &game, int color) : Player(game, color) {
}

AIPlayer::~AIPlayer() {
}

void AIPlayer::move() {
	int x = std::rand() % BOARD_SZ;
	int y = std::rand() % BOARD_SZ;
	game.getBoard().set(x, y, game.getPlayerActId());
}

std::string AIPlayer::getType() const { return "AI"; }