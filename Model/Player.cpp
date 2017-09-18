#ifndef PLAYER_H
#define PLAYER_H
#include "../Model/Player.hpp"
#endif

Player::Player() {
}

Player::Player(char *obj, int height, int lenght, int lifePoints, int ammo) {
	this->obj = obj;
	this->height = height;
	this->lenght = lenght;
	this->lifePoints = lifePoints;
	this->ammo = ammo;
}
