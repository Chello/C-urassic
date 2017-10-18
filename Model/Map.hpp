#ifndef CTIME_H
#define CTIME_H
#include <ctime>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

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


#ifndef ITEMTYPES_H
#define ITEMTYPES_H
#include "ItemTypes.hpp"
#endif

#ifndef ITEM_H
#define ITEM_H
#include "Item.hpp"
#endif

#if 1
#ifndef ENEMY_H
#define ENEMY_H
#include "Enemy.hpp"
#endif
#endif

//Dimensioni massime che la mappa puó assumere.
#ifndef SIZES
#define SIZES
#define HEIGHT 200
#define LENGHT 200
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

class Player;

class Map {
public:
	/*La matrice contenenre l'intera mappa*/
	char 		matrix[HEIGHT][LENGHT];
	/*Il numero dei nemici*/
	int 		numEnemies;
	/*Il numero degli items*/
	int 		numItems;
	/*Dimensioni effettive della mappa.
		this->height <= HEIGHT
		this->lenght <= LENGHT
		*/
	int height, lenght;

	/*Costruttore di classe. Inizia dal livello indicatogli come parametro a costruire una mappa*/
	Map(int level, Player *player);
	/****DEPRECATO****
	Class constructor
	It loads the passed filemap. The filemap shoud have a size of 30x60 
	Some of the levels/presets are saved into 
	*/
	Map(const char *presetFile);
	/*	Distruttore. Distrugge tutto.
		Distrugge i seguenti oggetti: enemies, portal, items, player.*/
	~Map();
	/* 	Muove il player.
		Ritorna EMPTY_SYM se il movimento é stato eseguito correttamente, 
		ritorna invece il simpolo dell'oggetto 'pestato' altrimenti.
			Se ha 'pestato' un Item, si piazza al posto dell'oggetto, cancellandolo
			se ha 'pestato' qualcos'altro, non esegue la mossa
	*/
	char movePlayer(Directions dir);
	/*Metodo che ritorna il player*/
	Player* getPlayer();
	/*Aumenta di livello e rigenera la mappa secondo il nuovo livello*/
	void levelUp();
	/* Metodo che fa muovere, secondo la direzione indicata, il Player oppure un Enemy.
	Richiede il player/enemy e la direzione in cui si deve muovere.
	Ritorna EMPTY_SYM se il movimento é stato eseguito correttamente, 
	ritorna invece il simpolo dell'oggetto 'pestato' altrimenti.
			Se ha 'pestato' un Item, si piazza al posto dell'oggetto, cancellandolo
			se ha 'pestato' qualcos'altro, non esegue la mossa*/
	char moveObject(Player *mapObj, Directions dir);
	/*Ritorna l'array dei nemici*/
	Enemy** getEnemies();
	/*Metodo che muove i nemici*/
	void IA(Map *currentMap, Enemy **enemy, int i, int j);
	/*Ritorna un nemico passandogli come parametro il suo nome/rappresentazone in mappa. */
	Enemy* getEnemyByName(char name);
protected:
	/*Puntatore al giocatore*/
	Player 	*player;
	/*I nemici del gioco*/
	Enemy 	**enemies;
	/*Gli items*/
	Item 	**items;
	/*Il portale*/
	Item 	*portal;

	/*Il livello attuale della mappa*/
	int 		level;
	/*
	This method cleans the whole matrix map.
	It signs 0 evrywhere. */
	void cleanMatrix();
	/*	Metodo che genera la mappa a seconda del livello a cui si é.
		Genera ulteriormente le ammo, i nemici, le porte ed il giocatore.*/
	void generateMap();
	/*Inserisce nella map il preset indicato dal file.
	Imposta anche l'altezza e la larghezza della map, usando quella del preset*/
	void getPreset(FILE *preset);
	/*Inizializza la classe insieme al resto*/
	void init();
	/*Controlla se il carattere passato ammette un movimento oppure no.
	Richiede il carattere da controllare.
	Ritorna true se si puó muovere l'oggetto, false altrimenti.*/
	bool canMove(char c);
	/*Disegna una stanza, dandogli le dimensioni e la posizione nella matrice.
		int xSize 	la dimensione del lato x
		int ySize 	la dimensione del lato y
		int xS 		la posizione x di inizio del disegno
		int yS 		la posizione y di inizio del disegno
		Directions holeSide la posizione del buco tra le due stanze in che lato si deve formare*/
	void drawRoom(int xSize, int ySize, int xS, int yS, Directions holeSide);
};
