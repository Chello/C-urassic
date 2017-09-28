#ifndef PLAYER_H
#define PLAYER_H
#include "Player.hpp"
#endif

#define STARTING_LIFEPOINTS 100

Player::Player(): MapObject(PLAYER_SYM) {
	lifePoints = STARTING_LIFEPOINTS;
}

Player::Player(char symbol): MapObject(symbol) {
	lifePoints = STARTING_LIFEPOINTS;
}

int Player::getLifePoints() {
	return lifePoints;
}

void Player::struck(int points) {
	lifePoints-=points;
}