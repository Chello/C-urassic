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
	this->getPreset(fileIn);

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
	this->lenght = j;
	//fclose(fileIn);
}

void Map::generateMap() {
	int numRooms = this->level %2 +1;
	int i;

	//this->numEnemies = this->level * MULT_ENEMIES;
	
	//Genera la mappa
	for (i = 1; i < numRooms; i++){
		//Disegna un muro
		//Calcola la posizione x di partenza
		//Bisogna lasciare uno spazio tra i muri di almeno il 15% del resto della mappa
		double offsetD = (double)this->lenght /100 *15;
		int offset = (int) offsetD;
		//variabile che terrá la posizione y del disegno da ora in poi. Inizia dall'estremo, randomicamente, alto o basso.
		int x, y;
		x = rand() % (this->lenght - (offset *2));
		//Variabile che mi segna se sto disegnando il muro a scendere oppure no
		bool topDown;
		if ((rand() % 2) == 0) {
			y = 0;
			topDown = true;
		}
		else {
			y = this->lenght;
			topDown = false;
		}
		//Finché non trovo un muro disegno!
		while (this->matrix[y][x] != WALL_SYM) {
			printf("loool\n");
			this->matrix[y][x] = WALL_SYM;
			if (topDown) y--;
			else y++;
		}
	}
}

bool Map::movePlayer(Directions dir) {
	return moveObject(this->player, dir);
}

void Map::cleanMatrix() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < LENGHT; j++) {
			this->matrix[i][j] = 0;
		}
	}
}

bool Map::moveObject(Player *mapObj, Directions dir) {
	int *l, *h;
	l = &(mapObj->lenght);
	h = &(mapObj->height);
	switch (dir){
		case MOVE_UP:
			if (matrix[(*h)-1][(*l)] == EMPTY_SYM) {

				matrix[(*h)-1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)--;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
		break;
		case MOVE_DOWN:
			if (matrix[(*h) +1][(*l)] == EMPTY_SYM) {

				matrix[(*h) +1][(*l)] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*h)++;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
			break;
		case MOVE_LEFT:
			if (matrix[(*h)][(*l) -1] == EMPTY_SYM) {

				matrix[(*h)][(*l) -1] = *mapObj->obj;
				matrix[(*h)][(*l)] = EMPTY_SYM;

				(*l)--;
				mapObj->obj = &matrix[(*h)][(*l)];
				return true;
			}
			break;
		case MOVE_RIGHT:
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