#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef CSTRING_H
#define CSTRING_H 
#include <cstring>
#endif

#ifndef SETTINGS_H
#define SETTINGS_H
#include "../Control/Settings.hpp"
#endif

#ifndef PLAYER_H
#define PLAYER_H 
#include "Player.hpp"
#endif

#if 1
#ifndef MAP_H
#define MAP_H
#include "Map.hpp"
#endif
#endif

using namespace std;

class Enemy: public Player {
public:
	Enemy(char *obj, int height, int lenght, int lifePoints, int ammo);
	//~Enemy();
	void IA(Map *map);
};