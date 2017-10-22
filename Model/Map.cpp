#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

Map::Map(int level, Player *player) {
	this->init();
	this->player = player;
	this->level = level;
	this->generateMap();
}

void Map::init(){
	this->cleanMatrix();
}

Map::Map(const char *presetFile) {
	FILE *fileIn;
	this->init();
	fileIn = fopen(presetFile, "r");
	if (fileIn == NULL) perror("Preset file error");
	//this->getPreset(fileIn);

    this->generateMap(); 
}

Map::~Map() {
	int i;
	/*Distruzione di enemies*/
	for (i = 0; i < this->numEnemies; i++){
		delete this->enemies[i];
	}
	/*Distruzione di Portal*/
	delete this->portal;
	/*Distruzione di Items*/
	for (i = 0; i < this->numItems; i++) {
		delete this->items[i];
	}
}

void Map::getPreset(FILE *preset) {
	bool hasLineEnded;
	char readLine[LENGHT+1];
	int i, j;
	//Now start loading the preset
	//This must contain in 'readLine' the current line for saving it
	for(i = 0; fgets(readLine, LENGHT + LEN_OFFSET, preset) != NULL; i++) {
		hasLineEnded = false;
		for (j = 0; j < LENGHT && !hasLineEnded; j++) {
			//If the string ends with a newline or a backslash character...
			if (readLine[j] == '\n' || readLine[j] == 92) 
				//so the matrix pattern has ended
				hasLineEnded = true;

			else matrix[i][j] = readLine[j];
			if (readLine[j] == PLAYER_SYM) {
				this->player = new Player(&matrix[i][j], i, j, STARTING_LIFEPOINTS, 0);
				this->player->height = i;
				this->player->lenght = j;
				this->player->obj = &matrix[i][j];
				this->player->lifePoints = STARTING_LIFEPOINTS;
			}
		}
	}

	//Update the real map sizes
	this->height = i;
	this->lenght = j -1; //Calo di 1 perché bisogna considerare anche il carattere di fine preset
	//fclose(fileIn);


}

void Map::generateMap() {
	int numRooms = this->level;
	int i;

	int xSize;
	int ySize;

	int partialNumEnemies = 0;
	int partialNumItems = 0;

	Directions dir = NULL_DIR;

	int x = 0, y = 0;

	this->lenght = 0;
	this->height = 0;

	xSize = rand() % ((MAX_ROOM_SIZE + numRooms) - MIN_ROOM_SIZE + numRooms) /*Lo scarto*/ + MIN_ROOM_SIZE + numRooms; /*+ il minimo*/

	ySize = rand() % ((MAX_ROOM_SIZE + numRooms) - MIN_ROOM_SIZE + numRooms) /*Lo scarto*/ + MIN_ROOM_SIZE + numRooms; /*+ il minimo*/

	this->numEnemies = numRooms * MULT_ENEMIES;
	this->numItems = MULT_ITEM * level;

	this->enemies = new Enemy*[this->numEnemies];
	this->items = new Item*[this->numItems];
	/*############## GENERAZIONE MAPPA ##############*/
	for (i = 0; i < numRooms; i++) {
		int j;
		//Posizioni dove sto andando a disegnare
		if (x + xSize > this->lenght) this->lenght = x + xSize +1;
		if (y + ySize > this->height) this->height = y + ySize +1;

		this->drawRoom(xSize, ySize, x, y, dir);

		/*############## POSIZIONAMENTO PLAYER ##############*/
		if (i == 0) {
			this->matrix[this->height -2][1] = PLAYER_SYM;
			/*this->player = new Player(
				&matrix[this->height -2][1], 
				this->height -2, 
				1, 
				STARTING_LIFEPOINTS, 
				STARTING_AMMO);*/
			this->player->height = this->height -2;
			this->player->lenght = 1;
			this->player->obj = &matrix[this->height -2][1];
		}
		/*############## GENERAZIONE NEMICI ##############*/
		for (j = 0; j < MULT_ENEMIES ; j++){
			int xEnemy = 1 + x + rand() % (xSize -2);
			int yEnemy = 1 + y + rand() % (ySize -2);
			if (this->matrix[yEnemy][xEnemy] == EMPTY_SYM){
				/*Crealo!*/
				this->matrix[yEnemy][xEnemy] = partialNumEnemies +'@' +1;
				this->enemies[partialNumEnemies] = new Enemy(
					&this->matrix[yEnemy][xEnemy], 
					yEnemy,
					xEnemy,
					STARTING_LIFEPOINTS, 
					STARTING_AMMO);
				partialNumEnemies++;
			} else j--;
		}

		/*############## GENERAZIONE ITEMS ##############*/
		for (j = 0; j < this->numItems / numRooms; j++) {
			int xItem = 1 + x + rand() % (xSize -2);
			int yItem = 1 + y + rand() % (ySize -2);

			if (this->matrix[yItem][xItem] == EMPTY_SYM) {
				//É un LP oppure un AMMO?
				if (rand() % 2) { //Se é un AMMO
					this->matrix[yItem][xItem] = AMMO_SYM;
					this->items[partialNumItems] = new Item(
						&this->matrix[yItem][xItem], 
						yItem, 
						xItem, 
						STARTING_AMMO, 
						AMMO);
					partialNumItems++;
				} else { //Se é un LP
					this->matrix[yItem][xItem] = LP_SYM;
					this->items[partialNumItems] = new Item(
						&this->matrix[yItem][xItem], 
						yItem, 
						xItem, 
						0, 
						LIFEPOINTS);
					partialNumItems++;
				}
			} else j--;
		}

		//Determino dove devo stampare la prossima stanza
		if (i < 2) {//Le prime falle tutte una a dx dell'altra
			x += xSize;
			dir = LEFT;
		} else if (i == 2) {
			y += ySize;
			dir = UP;
		} else if (i > 2 && i < 5) {
			x -= xSize;
			dir = RIGHT;
		} else if (i == 5) {
			y += ySize;
			dir = UP;
		}


	}

	/*############## GENERAZIONE PORTALE ##############*/
	int xPortal, yPortal;

	if (i < 4) {
		xPortal = this->lenght -2;
		yPortal = 1;
	} else if (i == 4) {
		xPortal = this->lenght -2;
		yPortal = this->height -2;
	} else if (i > 4) {
		xPortal = this->lenght - ((xSize) * (i - 3));
		yPortal = this->height -2;
	}

	this->matrix[yPortal][xPortal] = PORTAL_SYM;
	this->portal = new Item(
		&this->matrix[yPortal][xPortal], 
		yPortal, 
		xPortal,
		0,
		PORTAL);


}

void Map::drawRoom(int xSize, int ySize, int xS, int yS, Directions holeSide) {
	int x = 0, y = 0;
	int i; 
	/*La variabile holeSize determina la grandezza del buco che si deve realizzare nella direzione indicata come parametro
	La variabile offset indica la distanza dal margine di incomincio.*/
	int holeSize = 0;
	int offset = 0;

	if (holeSide == UP){
		//Calcolo la dimensione randomicamente del muro
		holeSize = rand() % ((int) ((double)this->lenght /100 *DIST_WALL) -1) +1;
		//Ci aggiungo un offset per non farlo appiccicato a terra
		offset = rand() % (xSize - holeSize) +1;
		holeSize += offset;
	}

	//Per la dimensione del muro
	for (i = 0; i < xSize; i++) {
		//Se ci sto ancora dentro
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			//Disegno un muro
			this->matrix[yS][xS] = WALL_SYM;
		//Altrimenti disegno il vuoto
		else this->matrix[yS][xS] = EMPTY_SYM;
		xS++;
		holeSize--; offset--;
	}

	if (holeSide == RIGHT){
		//Calcolo la dimensione randomicamente del muro
		holeSize = rand() % ((int) ((double)this->height /100 *DIST_WALL) -1) +1;
		//Ci aggiungo un offset per non farlo appiccicato a terra
		offset = rand() % (ySize - holeSize) +1;
		holeSize += offset;
	}

	//Per la dimensione del muro
	for (i = 0; i < ySize; i++) {
		//Se ci sto ancora dentro
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			//Disegno un muro
			this->matrix[yS][xS] = WALL_SYM;
		//Altrimenti disegno il vuoto
		else this->matrix[yS][xS] = EMPTY_SYM;
		yS++;
		holeSize--; offset--;
	}

	if (holeSide == DOWN){
		//Calcolo la dimensione randomicamente del muro
		holeSize = rand() % ((int) ((double)this->lenght /100 *DIST_WALL) -1) +1;
		//Ci aggiungo un offset per non farlo appiccicato a terra
		offset = rand() % (xSize - holeSize) +1;
		holeSize += offset;
	}

	//Per la dimensione del muro
	for (i = 0; i < xSize; i++) {
		//Se ci sto ancora dentro
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			//Disegno un muro
			this->matrix[yS][xS] = WALL_SYM;
		//Altrimenti disegno il vuoto
		else this->matrix[yS][xS] = EMPTY_SYM;
		xS--;
		holeSize--; offset--;
	}

	if (holeSide == LEFT){
		//Calcolo la dimensione randomicamente del muro
		holeSize = rand() % ((int) ((double)this->height /100 *DIST_WALL) -1) +1;
		//Ci aggiungo un offset per non farlo appiccicato a terra
		offset = rand() % (ySize - holeSize) +1;
		holeSize += offset;
	}

	//Per la dimensione del muro
	for (i = 0; i < ySize; i++) {
		//Se ci sto ancora dentro
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			//Disegno un muro
			this->matrix[yS][xS] = WALL_SYM;
		//Altrimenti disegno il vuoto
		else this->matrix[yS][xS] = EMPTY_SYM;
		yS--;
		holeSize--; offset--;
	}
}

#if 0
Deprecato
void Map::generateMap() {
	int numRooms = this->level /2 +1;
	int i, j = 0, holeSizes;

	//this->numEnemies = this->level * MULT_ENEMIES;
	//Viene seguita una logica di rotazione assiale per la realizzazione di muri.
	int axisRotation;

	//################ GENERAZIONE DEI MURI ################
	srand(time(NULL)); 

	axisRotation = rand() %4;
	
	for (i = 1; i < numRooms; i++) {
		//Disegna un muro
		//Calcola la posizione x di partenza
		//Bisogna lasciare uno spazio tra i muri di almeno il 15% del resto della mappa
		int offset;
		//variabili che terranno le posizioni x ed y del disegno da ora in poi.
		//La scrittura di un muro inizia da un estremo della mappa.
		int x, y;
		/*Sono utili per il cambio di direzione del muro (alto-basso vs sx-dx) *
		int a, b;
		/*Variabile che mi segna se sto disegnando il muro
				da sx vs dx / dall'alto vs il basso (true)
				da dx vs sx / dal basso vs l'alto (false).
			Che tradotto significa se mi sto allontanando dall'asse (true) oppure se mi ci sto avvicinando (false) *
		bool layerMark;
		/*Variabile che viene considerata per disegnare 
			in verticale (true)
			oppure in orizzontale (false) *
		bool invertCoordinates;

		//x = rand() % (this->lenght - (offset *2));

		switch (axisRotation) {
			case 0:
				//Inizia dall'alto verso il basso 
				offset = (int) ((double)this->lenght /100 *DIST_WALL);

				y = 1; //Non inizio da 0 perché ovviamente in quella posizione cé giá il muro!
				x = rand() % (this->lenght - (offset *2)) + offset;//Dico da dove parto

				layerMark = true;
				invertCoordinates = true;
				break;
			case 1:
				//Inizia dal basso verso l'alto
				offset = (int) ((double)this->lenght /100 *DIST_WALL);

				y = this->height -2; //Non inizio da lenght perché ovviamente in quella posizione cé giá il muro!
				x = rand() % (this->lenght - (offset *2)) + offset;//Dico da dove parto

				layerMark = false;
				invertCoordinates = true;
				break;
			case 2:
				//inizia da sx verso dx
				offset = (int) ((double)this->height /100 *DIST_WALL);

				y = rand() % (this->height - (offset *2)) + offset;
				x = 1; //Non inizio da 0 perché ovviamente in quella posizione cé giá il muro!

				layerMark = true;
				invertCoordinates = false;
				break;
			case 3:
				//Inizia da dx verso sx
				offset = (int) ((double)this->height /100 *DIST_WALL);	

				y = rand() % (this->height - (offset *2)) + offset;
				x = this->lenght -2; //Non inizio da height perché ovviamente in quella posizione cé giá il muro!

				layerMark = false;
				invertCoordinates = false;
				break;
			default: break;
		}

		holeSizes = (rand() % offset) /2 + 1;
		j = 0;

		while (this->matrix[y][x] != WALL_SYM) {
			if (j < holeSizes) 
				j++;
			else this->matrix[y][x] = WALL_SYM;
			if (layerMark) { //Se mi sto allontanando dall'asse ...
				if (invertCoordinates) //Se sto andando in verticale...
					y++; //Aumento nell'asse y
				else x++; //Altrimenti incremento nell'asse x
			}
			else { //Se invece mi sto avvicinando all'asse...
				if (invertCoordinates) //Se sto andando in verticale
					y--; //Decremento nell'asse y
				else x--; //Altrimenti Decremento nell'asse x
			}
		}

		axisRotation++;
		if (axisRotation == 4) axisRotation = 0;
	}
}*/
#endif

char Map::movePlayer(Directions dir) {
	return moveObject(this->player, dir);
}

void Map::cleanMatrix() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < LENGHT; j++) {
			this->matrix[i][j] = EMPTY_SYM;
		}
	}
}

char Map::moveObject(Player *mapObj, Directions dir) {
	int *l, *h;
	char toSub;
	l = &(mapObj->lenght);
	h = &(mapObj->height);
	switch (dir){
		case UP:
			toSub = matrix[(*h)-1][(*l)];
			if (this->canMove(toSub)) {

				matrix[(*h)-1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)--;
				mapObj->obj = &matrix[(*h)][(*l)];
			}
		break;
		case DOWN:
			toSub = matrix[(*h) +1][(*l)];
			if (this->canMove(toSub)) {

				matrix[(*h) +1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)++;
				mapObj->obj = &matrix[(*h)][(*l)];
			}
			break;
		case LEFT:
			toSub = matrix[(*h)][(*l) -1];
			if (this->canMove(toSub)) {

				matrix[(*h)][(*l) -1] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*l)--;
				mapObj->obj = &matrix[(*h)][(*l)];
			}
			break;
		case RIGHT:
			toSub = matrix[(*h)][(*l) +1];
			if (this->canMove(toSub)) {

				matrix[(*h)][(*l) +1] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*l)++;
				mapObj->obj = &matrix[(*h)][(*l)];
			}
			break;
		default: return '\0';
	}
	return toSub;
}

bool Map::canMove(char c) {
	switch (c) {
			case EMPTY_SYM:
			case AMMO_SYM:
			case LP_SYM:
				return true;
			case WALL_SYM:
			case PORTAL_SYM: 
			default:
				return false;
	}
}

Player* Map::getPlayer() {
	return player;
}

Enemy** Map::getEnemies() {
	return this->enemies;
}

char Map::IA() {
	//prende la posizione del player
	int i;
	int j;
	int Px = getPlayer()->lenght;
	int Py = getPlayer()->height;
	//Per il numero dei nemici...
	for (j = 0; j < numEnemies; j++) {
		//prende la posizione di E #i
		int x = this->enemies[j]->lenght;
		int y = this->enemies[j]->height;
		for (i = 0; i < MAX_ENEMY_MOVE; i++) {
			//Se il nemico é ancora in vita...
			if (this->enemies[j]->lifePoints > 0){
				int xory;
				char result;
				//Se sono nella stessa riga delle x del player...
				if (x == Px) 
					xory = 1; //mi devo muovere nelle y
				else if (y == Px)//Se sono nella stessa colonna delle y del player
					xory = 0; //Mi devo muovere nelle x
				//random per scegliere se muoversi sulle x oppure sulle y (0 = X, 1 = Y)
				else xory = rand() % 2;
				if (xory == 0) {
					if (x < Px) {
						result = moveObject(this->enemies[j], RIGHT);
						//se non ci sono ostacoli il nemico si muove verso destra
						if (result == PLAYER_SYM)
							return *(this->enemies[j]->obj); 
						//se non ci sono ostacoli il nemico si muove verso sinistra 
						else if (result != EMPTY_SYM) {
							if (moveObject(this->enemies[j], LEFT) == PLAYER_SYM)
								return *(this->enemies[j]->obj);
						}
					} else {
						result = moveObject(this->enemies[j], LEFT);
						//se non ci sono ostacoli il nemico si muove verso destra
						if (result == PLAYER_SYM)
							return *(this->enemies[j]->obj); 
						//se non ci sono ostacoli il nemico si muove verso sinistra 
						else if (result != EMPTY_SYM) {
							if (moveObject(this->enemies[j], RIGHT) == PLAYER_SYM)
								return *(this->enemies[j]->obj);
						}
					}
				} else {
					if (y < Py) {
						result = moveObject(this->enemies[j], DOWN);
						//se non ci sono ostacoli il nemico si muove verso destra
						if (result == PLAYER_SYM)
							return *(this->enemies[j]->obj); 
						//se non ci sono ostacoli il nemico si muove verso sinistra 
						else if (result != EMPTY_SYM) {
							if (moveObject(this->enemies[j], UP) == PLAYER_SYM)
								return *(this->enemies[j]->obj);
						}
					}
					else {
						result = moveObject(this->enemies[j], UP);
						//se non ci sono ostacoli il nemico si muove verso destra
						if (result == PLAYER_SYM)
							return *(this->enemies[j]->obj); 
						//se non ci sono ostacoli il nemico si muove verso sinistra 
						else if (result != EMPTY_SYM) {
							if (moveObject(this->enemies[j], DOWN) == PLAYER_SYM)
								return *(this->enemies[j]->obj);
						}
					}
				}
			}
		}
	}
	return '\0';
}

Enemy* Map::getEnemyByName(char name) {
	int i;
	for (i = 0; i < this->numEnemies; i++){
		if (*(this->enemies[i]->obj) == name)
			return this->enemies[i];
	}
	return NULL;
}