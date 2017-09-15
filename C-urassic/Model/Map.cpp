#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

Map::Map(const char *presetFile) {
	FILE *fileIn;
	char readLine[LENGHT+1];
	int i, j;
	numEnemies = 0;
	fileIn = fopen(presetFile, "r");
	if (fileIn == NULL) perror("err");
	//Now start loading the matrix
	//This must contain in 'readLine' the current line for saving it
	for(i = 0; fgets(readLine, LENGHT + LEN_OFFSET, fileIn) != NULL; i++) {
		for (j = 0; j < LENGHT; j++) {
			matrix[i][j] = readLine[j];
			if (readLine[j] == PLAYER_SYM) {
				this->player = new MapCharacter();
				this->player->height = i;
				this->player->lenght = j;
				this->player->obj = &matrix[i][j];
				this->player->lifePoints = STARTING_LIFEPOINTS;
			}
		}
	}
	//fclose(fileIn);
}

bool Map::movePlayer(Directions dir) {
	return moveObject(this->player, dir);
}

bool Map::moveObject(MapCharacter *mapObj, Directions dir) {
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

MapCharacter* Map::getPlayer() {
	return player;
}