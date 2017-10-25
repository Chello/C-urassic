#ifndef GAME_H
#define GAME_H
#include "../Control/Game.hpp"
#endif

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