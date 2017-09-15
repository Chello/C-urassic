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

#ifndef MapCharacter_H
#define MapCharacter_H
#include "MapCharacter.hpp"
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
	char 		matrix[HEIGHT][LENGHT];
	/*The number of enemies in the game*/
	int 		numEnemies;
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
	/*
	It moves the player in the directions passed by parameter
	Returns true if the move has done successfully, false otherwise
	*/
	bool movePlayer(Directions dir);
	/*Method that returns the MapCharacter of the player*/
	MapCharacter* getPlayer();

protected:
	/*
	Contains the pointer to the player*/
	MapCharacter 	*player;
	/*The enemies in the game*/
	MapCharacter 	*enemies[];
	/*
	This method makes move the specified object (with relative position) 
	to the direction gave in 'dir'.
	Returns true if the object has moved successfully, false otherwise.*/
	bool moveObject(MapCharacter *mapObj, Directions dir);
	
};