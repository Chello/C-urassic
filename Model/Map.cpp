#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

Map::Map() {
	this->init();
}

void Map::init(){
	this->level = 1;
}

Map::Map(const char *presetFile) {
	FILE *fileIn;
	numEnemies = 0;
	this->init();
	this->cleanMatrix();
	fileIn = fopen(presetFile, "r");
	if (fileIn == NULL) perror("Preset file error");
	//this->getPreset(fileIn);

	this->level = 2;
	this->generateMap();
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
	int numRooms = this->level /2 +1;
	int i;

	int xSize;
	int ySize;

	Directions dir = NULL_DIR;

	int x = 0, y = 0;

	this->lenght = 0;
	this->height = 0;

	//this->numEnemies = this->level * MULT_ENEMIES;

	xSize = rand() % ((MAX_ROOM_SIZE + numRooms) - MIN_ROOM_SIZE + numRooms) /*Lo scarto*/ + MIN_ROOM_SIZE + numRooms; /*+ il minimo*/

	ySize = rand() % ((MAX_ROOM_SIZE + numRooms) - MIN_ROOM_SIZE + numRooms) /*Lo scarto*/ + MIN_ROOM_SIZE + numRooms; /*+ il minimo*/

	/*############## GENERAZIONE MAPPA ##############*/
	for (i = 0; i < numRooms; i++) {
		//Posizioni dove sto andando a disegnare
		if (x + xSize > this->lenght) this->lenght = x + xSize +1;
		if (y + ySize > this->height) this->height = y + ySize +1;

		this->drawRoom(xSize, ySize, x, y, dir);

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
	/*############## GENERAZIONE PLAYER ##############*/
	this->matrix[this->height -2][1] = PLAYER_SYM;
	this->player = new Player(&matrix[this->height -2][1], this->height -2, 1, STARTING_LIFEPOINTS, STARTING_AMMO);
	/*############## GENERAZIONE PORTALE ##############*/
	
	/*############## GENERAZIONE NEMICI ##############*/

}


void Map::drawRoom(int xSize, int ySize, int xS, int yS, Directions holeSide) {
	int x = 0, y = 0;
	int i; 
	/*La variabile holeSize determina la grandezza del buco che si deve realizzare nella direzione indicata come parametro
	La variabile offset indica la distanza dal margine di incomincio.*/
	int holeSize = 0;
	int offset = 0;

	if (holeSide == UP){
		holeSize = rand() % ((int) ((double)this->lenght /100 *DIST_WALL) -1) +1;
		offset = rand() % (xSize - holeSize) +1;
		holeSize += offset;
	}

	for (i = 0; i < xSize; i++) {
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			this->matrix[yS][xS] = WALL_SYM;
		else this->matrix[yS][xS] = ' ';
		xS++;
		holeSize--; offset--;
	}

	if (holeSide == RIGHT){
		holeSize = rand() % ((int) ((double)this->height /100 *DIST_WALL) -1) +1;
		offset = rand() % (ySize - holeSize) +1;
		holeSize += offset;
	}

	for (i = 0; i < ySize; i++) {
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			this->matrix[yS][xS] = WALL_SYM;
		else this->matrix[yS][xS] = ' ';
		yS++;
		holeSize--; offset--;
	}

	if (holeSide == DOWN){
		holeSize = rand() % ((int) ((double)this->lenght /100 *DIST_WALL) -1) +1;
		offset = rand() % (xSize - holeSize) +1;
		holeSize += offset;
	}

	for (i = 0; i < xSize; i++) {
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			this->matrix[yS][xS] = WALL_SYM;
		else this->matrix[yS][xS] = ' ';
		xS--;
		holeSize--; offset--;
	}

	if (holeSide == LEFT){
		holeSize = rand() % ((int) ((double)this->height /100 *DIST_WALL) -1) +1;
		offset = rand() % (ySize - holeSize) +1;
		holeSize += offset;
	}

	for (i = 0; i < ySize; i++) {
		if (offset > 0 || (offset <= 0 && holeSize <= 0))
			this->matrix[yS][xS] = WALL_SYM;
		else this->matrix[yS][xS] = ' ';
		yS--;
		holeSize--; offset--;
	}
}
/*
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

bool Map::movePlayer(Directions dir) {
	return moveObject(this->player, dir);
}

void Map::cleanMatrix() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < LENGHT; j++) {
			this->matrix[i][j] = ' ';
		}
	}
}

bool Map::moveObject(Player *mapObj, Directions dir) {
	int *l, *h;
	l = &(mapObj->lenght);
	h = &(mapObj->height);
	switch (dir){
		case UP:
			if (matrix[(*h)-1][(*l)] == EMPTY_SYM) {

				matrix[(*h)-1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)--;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
		break;
		case DOWN:
			if (matrix[(*h) +1][(*l)] == EMPTY_SYM) {

				matrix[(*h) +1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)++;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
			break;
		case LEFT:
			if (matrix[(*h)][(*l) -1] == EMPTY_SYM) {

				matrix[(*h)][(*l) -1] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*l)--;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
			break;
		case RIGHT:
			if (matrix[(*h)][(*l) +1] == EMPTY_SYM) {

				matrix[(*h)][(*l) +1] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*l)++;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
			break;
		default: return false;
	}
	return false;
}

Player* Map::getPlayer() {
	return player;
}