//Questa classe è inserita nel control e ha lo scopo di gestire la partita a seconda dei turni
//Il main si occuperà solamete di lanciare la partita e di far terminare l'esecuzione

/*
Import necessari, tutte le classi del model
*/

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

#ifndef DIRECTIONS_H
#define DIRECTIONS_H
#include "../Model/Directions.hpp"
#endif

#ifndef SETTINGS_H
#define SETTINGS_H
#include "../Control/Settings.hpp"
#endif

#ifndef PLAYER_H
#define PLAYER_H
#include "../Model/Player.hpp"
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

#ifndef ITEMTYPES_H
#define ITEMTYPES_H
#include "../Model/ItemTypes.hpp"
#endif

#ifndef ITEM_H
#define ITEM_H
#include "../Model/Item.hpp"
#endif

#ifndef ENEMY_H
#define ENEMY_H
#include "../Model/Enemy.hpp"
#endif

class Game {
public:
	Game();
	

private:
};
	
#if 0
#endif