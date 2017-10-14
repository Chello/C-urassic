#if 0

#ifndef CSTRING_H
#define CSTRING_H 
#include <cstring>
#endif

#ifndef STDLIB_H
#define STDLIB_H
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

#ifndef ITEM_H
#define ITEM_H
#include "../Model/Item.hpp"
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

#ifndef GAME_H
#define GAME_H
#include "../Control/Game.hpp"
#endif

#if 0
class Game {
public:
	//Costruttore. Genera gli oggetti e inizializza le prime variabili del gioco.
	Game();
	//Let's Play!
	void start();

private:
	//Indica il livello a cui si é
	int 		level;
	//Indica se si sta giocando o se si é in game over
	bool 		isPlaying;
	//Puntatore alla mappa corrente
	Map 		*currentMap;
	//Puntatore al disegnatore del playground corrente
	Playground	*view;

};
#endif

#if 1
Game::Game() {
	this->isPlaying = true;
	this->level = 1;
	//Istanzio una nuova mappa, e gli passo il file del livello 1 (che é contenuto in 'Map_Presets')
	this->currentMap = new Map(4);

	this->view = new Playground();

	//Il Playground ha bisogno della mappa da caricare 
	this->view->loadMap(this->currentMap);
	//Il Playground stampa la mappa
	this->view->refresh();
}
#endif
#if 1
void Game::start() { 
	while (this->isPlaying) {
		char input;
		char messageText[MAXSTRLEN] = "";

		Directions dir = NULL_DIR;

		input = 0;
		cout << "Please enter the next move: ";
		cin >> input;

		switch (input) {
			case 'a':
			case 'A':
				dir = LEFT;
				break;
			case 's':
			case 'S':
				dir = DOWN;
				break;
			case 'd':
			case 'D':
				dir = RIGHT;
				break;
			case 'w':
			case 'W':
				dir = UP;
				break;
			case 'c': break;
				//We don't use 'q' because, while playing, this key could be pressed accidentally
			case 'Q':
				this->isPlaying = false;
				exit(0);
				break;
			default:
				strcpy(messageText, "Invalid key!");
				break;
		}

		if (this->currentMap->movePlayer(dir)) {

		} else {
			strcpy(messageText, "Invalid key!");
		}
		this->view->refresh(messageText);
	}
}
#endif