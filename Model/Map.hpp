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

#ifndef PLAYER_H
#define PLAYER_H
#include "Player.hpp"
#endif

#ifndef CTIME_H
#define CTIME_H
#include <ctime>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

#ifndef ITEMTYPES_H
#define ITEMTYPES_H
#include "ItemTypes.hpp"
#endif

#ifndef ITEM_H
#define ITEM_H
#include "Item.hpp"
#endif

#ifndef ENEMY_H
#define ENEMY_H
#include "Enemy.hpp"
#endif

//Dimensioni massime che la mappa puó assumere.
#ifndef SIZES
#define SIZES
#define HEIGHT 200
#define LENGHT 350
//Definisce la distanza percentuale di realizzazione muri a distanza.
#define DIST_WALL 35
//Definisce le massime e le minime dimensioni di una stanza
#define MAX_ROOM_SIZE 6
#define MIN_ROOM_SIZE 6
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
	//Real maximum sizes of the map, are always <= HEIGHT & LENGHT
	int height, lenght;

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
	Player* getPlayer();
	/*Aumenta di livello e rigenera la mappa secondo il nuovo livello*/
	void levelUp();
	/*Ritorna l'array dei nemici*/
	Enemy** getEnemies();
protected:
	/*
	Contains the pointer to the player*/
	Player 	*player;
	/*The enemies in the game*/
	Enemy 	*enemies[];
	/*Il portale*/
	Item 	*portal;

	/*Il livello attuale della mappa*/
	int 		level;
	/*
	This method makes move the specified object (with relative position) 
	to the direction gave in 'dir'.
	Returns true if the object has moved successfully, false otherwise.*/
	bool moveObject(Player *mapObj, Directions dir);
	/*
	This method cleans the whole matrix map.
	It signs 0 evrywhere. */
	void cleanMatrix();
	/*Metodo che genera la mappa a seconda del livello a cui si é*/
	void generateMap();
	/*Inserisce nella map il preset indicato dal file.
	Imposta anche l'altezza e la larghezza della map, usando quella del preset*/
	void getPreset(FILE *preset);
	/*Inizializza la classe insieme al resto*/
	void init();
	/*Disegna una stanza, dandogli le dimensioni e la posizione nella matrice.
		int xSize 	la dimensione del lato x
		int ySize 	la dimensione del lato y
		int xS 		la posizione x di inizio del disegno
		int yS 		la posizione y di inizio del disegno
		Directions holeSide la posizione del buco tra le due stanze in che lato si deve formare*/
	void drawRoom(int xSize, int ySize, int xS, int yS, Directions holeSide);
};
