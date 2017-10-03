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

using namespace std;

class Player {
public:
	/*Class constructor.
	It could require nothing for simple creation of a player.
	Could also require all the player attributes (char *obj, int heigh, lenght, lifepoints and ammo) 
	*/
	Player();
	Player(char *obj, int height, int lenght, int lifePoints, int ammo);
	/*Il riferimento all'oggetto della mappa*/
	char *obj;
	/*Posizone assoluta nella mappa*/
	int height, lenght;
	/*Punti vita*/
	int lifePoints;
	/*Ammo for the player*/
	int ammo;
};