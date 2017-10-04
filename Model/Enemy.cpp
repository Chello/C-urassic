#ifndef ENEMY_H
#define ENEMY_H
#include "Enemy.hpp"
#endif

Enemy::Enemy(char *obj, int height, int lenght, int lifePoints, int ammo) :
	Player(obj, height, lenght, lifePoints, ammo) {}