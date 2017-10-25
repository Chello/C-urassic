#if 1
#ifndef CSTRING_H
#define CSTRING_H 
#include <cstring>
#endif

#ifndef STDLIB_H
#define stdlibB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
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

#ifndef ITEMTYPES_H
#define ITEMTYPES_H
#include "../Model/ItemTypes.hpp"
#endif

#ifndef ENEMY_H
#define ENEMY_H
#include "../Model/Enemy.hpp"
#endif

#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include "../View/Playground.hpp"
#endif

#endif

#if 1
class Game {
public:
	//Costruttore. Genera gli oggetti e inizializza le prime variabili del gioco.
	Game();
	//Let's Play!
	void start();
	//
	void insertMoves();

private:
	/*Metodo che fa terminare il gioco.
	gameOver: true se si ha perso/terminato la partita, false se si ha vinto*/
	void endGame(bool gameOver);
	//Avanzamento del livello di gioco
	void levelUp();
	//Indica il livello a cui si é
	int 		level;
	//Indica se si sta giocando o se si é in game over
	bool 		isPlaying;
	//Puntatore alla mappa corrente
	Map 		*currentMap;
	//Puntatore al disegnatore del playground corrente
	Playground	*view;
	//Il player di tutto il gioco
	Player 		*player;
	//Nemici
	Enemy 		**enemies;

};
#endif