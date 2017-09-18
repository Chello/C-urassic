#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

Map::Map(const char *presetFile) {
	FILE *fileIn;
	char readLine[LENGHT+1];
	int i, j;
	bool hasLineEnded;
	numEnemies = 0;
	this->cleanMatrix();
	fileIn = fopen(presetFile, "r");
	if (fileIn == NULL) perror("Preset file error");
	//Now start loading the preset
	//This must contain in 'readLine' the current line for saving it
	for(i = 0; fgets(readLine, LENGHT + LEN_OFFSET, fileIn) != NULL; i++) {
		hasLineEnded = false;
		for (j = 0; j < LENGHT && !hasLineEnded; j++) {
			//If the string ends with a newline or a backslash character...
			if (readLine[j] == '\n' || readLine[j] == 92) 
				//so the matrix pattern has ended
				hasLineEnded = true;

			else matrix[i][j] = readLine[j];
			if (readLine[j] == PLAYER_SYM) {
				this->player = new Player();
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