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
		bool haveToMove = true; //Indica se bisogna fare una mossa (vero) oppure se bisogna sparare (falso)

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
           		case 'j':
				case 'J':
					this->player->shoot(this->currentMap,'j');
					haveToMove = false;
					break;
				case 'i':
				case 'I':
					this->player->shoot(this->currentMap,'i');
					haveToMove = false;
					break;
				case 'l':
				case 'L':
					this->player->shoot(this->currentMap,'l');
					haveToMove = false;
					break;
				case 'k':
				case 'K':
					this->player->shoot(this->currentMap,'k');
					haveToMove = false;	
					break;
				default:
					strcpy(messageText, "Invalid key!");
					break;
			}  // chiude switch

			if (haveToMove) {
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
						strcpy(messageText, "You lose!");	
						this->view->refresh(messageText);			
						this->endGame(true);
						break;
				}
			}

			count++;
			dir = NULL_DIR;
		} // chiude secondo while
		this->view->refresh(messageText);
		//turno dei nemici
		this->currentMap->IA(this->currentMap, this->enemies, 0, 0);
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