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
#include "Directions.hpp"
#endif

#ifndef SETTINGS_H
#define SETTINGS_H
#include "../Control/Settings.hpp"
#endif

using namespace std;

class Player {
public:
	/*Referenced MapObject*/
	char *obj;
	/*Absolute position in the map*/
	int height, lenght;
	/*Lifepoints*/
	int lifePoints;
};