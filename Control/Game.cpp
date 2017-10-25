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
	if (this->level > 6) //Se abbiamo raggiunto il livello 6 e l'abbiamo superato
		this->endGame(false);//Vinci
	delete this->currentMap;
	this->currentMap = new Map(this->level, (this->player));
}

void Game::insertMoves(){
	char moves[MAXSTRLEN];   //Array contenente le mosse in input dell'utente
	
	while (isPlaying) {
		char messageText[MAXSTRLEN] = "";
		Directions dir = NULL_DIR;
		int i;
		int count = 0;  // utilizzata nel while che chiede in input le mosse
		bool mosse = true;
		bool haveToMove; //Indica se bisogna fare una mossa (vero) oppure se bisogna sparare (falso)

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
			strcpy(messageText, "ERRORE: Inserire tre mosse!");

		while(count < MAX_INPUT_MOVE && mosse == true){
			switch (moves[count]) {
				case 'a':
				case 'A':
					dir = LEFT;
					haveToMove = true;
					break;
				case 's':
				case 'S':
					dir = DOWN;
					haveToMove = true;
					break;
				case 'd':
				case 'D':
					dir = RIGHT;
					haveToMove = true;
					break;
				case 'w':
				case 'W':
					dir = UP;
					haveToMove = true;
					break;
           		case 'j':
				case 'J':
					dir = LEFT;
					haveToMove = false;
					break;
				case 'i':
				case 'I':
					dir = UP;
					haveToMove = false;
					break;
				case 'l':
				case 'L':
					dir = RIGHT;
					haveToMove = false;
					break;
				case 'k':
				case 'K':
					dir = DOWN;
					haveToMove = false;	
					break;
				default:
					strcpy(messageText, "Invalid key!");
					mosse = false;
					break;
			}  // chiude switch

			if (haveToMove && mosse) {
				/*#################### CI SI MUOVE ####################*/
				char step = this->currentMap->movePlayer(dir);
				switch (step) {
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
						this->player->lifePoints -= ENEMY_DAMAGE;
						sprintf(messageText, "You step on %c!", step);
						break;
				}
			} if (!haveToMove && mosse) {
				/*#################### SI SPARA ####################*/
				if (!this->player->shoot(this->currentMap, dir))
					strcpy(messageText, "You have not enough ammo!");
			}

			count++;
			dir = NULL_DIR;
		} // chiude secondo while
		//turno dei nemici, se non bisogna passare di livello
		if (mosse) { //Se ancora il gioco é buono
			//Avvia l'intelligenza artificiale dei nemici
			char killer = this->currentMap->IA();
			//Se si ha perso...
			if (killer != '\0') {
				this->player->lifePoints -= ENEMY_DAMAGE;
				//Scrivi il messaggio di perdita in attesa della chiusura del gioco
				sprintf(messageText, "%c has damaged you!", killer);
			}
		}
		//Rinfresco
		this->view->refresh(messageText);
		//Se hai perso fai finire il gioco
		if (this->player->lifePoints <= 0) 
			this->endGame(true);
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
	//Nemici 
	enemies = this->currentMap->getEnemies();

	this->view = new Playground();

	//Il Playground ha bisogno della mappa da caricare 
	this->view->loadMap(this->currentMap);
	//Il Playground stampa la mappa
	this->view->refresh();
}
#endif