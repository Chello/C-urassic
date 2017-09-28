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

#ifndef WALL_H
#define WALL_H
#include "Wall.hpp"
#endif

#ifndef PLAYER_H
#define PLAYER_H 
#include "Player.hpp"
#endif

#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "MapObject.hpp"
#endif

#ifndef SIZES
#define SIZES
#define HEIGHT 30
#define LENGHT 60
#endif

//The offset to be added to the LENGHT parameter.
//Useful, when inserting a new map, for considering "\n" and "\0"
#define LEN_OFFSET 2

using namespace std;

class Map {
public:
	/*
	Attribute containing the plain matrix of the map loaded
	*/
	MapObject 		*matrix[HEIGHT][LENGHT];
	/*
	Class constructor. It starts at level 1
	*/
	Map();
	/*
	Class constructor
	It loads the passed filemap. The filemap shoud have a size of 30x60 
	Some of the levels/presets are saved into 
	*/
	Map(const char *presetFile);

private:
};