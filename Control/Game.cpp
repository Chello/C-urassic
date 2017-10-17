#ifndef GAME_H
#define GAME_H
#include "../Control/Game.hpp"
#endif

void Game::endGame(bool gameOver) {
	if (gameOver) 
		cout << "Game Over!\n";
	else cout << "You winner!\n";
	exit(0);
}

void Game::levelUp() {
	this->level++;
	if (this->level > 6)
		this->endGame(false);
	delete this->currentMap;
	this->currentMap = new Map(this->level, (this->player));
}

void Game::insertMoves(){
	char moves[MAXSTRLEN];   //Importare settings.hpp per il define
	
	while (isPlaying) {
		char messageText[MAXSTRLEN] = "";
		Directions dir = NULL_DIR;
		int i;
		int count = 0;  // utilizzata nel while che chiede in input le mosse
		bool mosse = true;
		/*Reset dell'array di mosse "moves"*/
		for (i = 0; i < MAXSTRLEN; i++) 
			moves[i] = '\0';
		
		cout << "Please enter the next three moves: ";
		cin >> moves;

		if (moves[0] == 'q' || moves[0] == 'Q'){  // se la prima "mossa" inserita e q il gioco termina senza chiedere le altre due mosse
			    this->isPlaying = false;
				mosse = false;
				this->endGame(true);
		}

		for (i = 0; i < MAX_INPUT_MOVE; i++) {
			if (moves[i] == '\0')
				mosse = false;
		}
		cout << moves[MAX_INPUT_MOVE+1];
		if (moves[MAX_INPUT_MOVE] != '\0') {
			mosse = false;
		} 
		if (!mosse) 
			strcpy(messageText, "ERRORE: Solo tre mosse!");

		while(count < MAX_INPUT_MOVE && mosse == true){
			switch (moves[count]) {
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
				default:
					strcpy(messageText, "Invalid key!");
					break;
			}  // chiude switch
			#if 0
			if (this->currentMap->movePlayer(dir) == EMPTY_SYM) {
			} else {
				strcpy(messageText, "Invalid key!");
			}
			#endif
			switch (this->currentMap->movePlayer(dir)) {
				case WALL_SYM:
					break;
				case AMMO_SYM:
					this->player->ammo += ADD_AMMO;
					break;
				case LP_SYM:
					this->player->lifePoints += ADD_LP;
					break;
				case PORTAL_SYM:
					this->levelUp();
					mosse = false;
					break;
				case EMPTY_SYM:
					break;
				default: //Se ha preso un nemico...
					this->player->lifePoints = 0;
					this->endGame(true);
					break;
			}

			count++;
			dir = NULL_DIR;
		} // chiude secondo while
		this->view->refresh(messageText);
	} // chiude primo while
}

#if 1
Game::Game() {
	this->isPlaying = true;
	this->level = 1;

	this->player = new Player();
	this->player->ammo = STARTING_AMMO;
	this->player->lifePoints = STARTING_LIFEPOINTS;
	//Istanzio una nuova mappa, e gli passo il file del livello 1 (che é contenuto in 'Map_Presets')
	this->currentMap = new Map(this->level, this->player);

	this->view = new Playground();

	//Il Playground ha bisogno della mappa da caricare 
	this->view->loadMap(this->currentMap);
	//Il Playground stampa la mappa
	this->view->refresh();
}
#endif
#if 0
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
				delete this->currentMap;
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