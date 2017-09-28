#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

Map::Map(const char *presetFile) {
	FILE *fileIn;
	char readLine[LENGHT+1];
	int i, j;
	fileIn = fopen(presetFile, "r");
	if (fileIn == NULL) perror("err");
	//Now start loading the matrix
	//This must contain in 'readLine' the current line for saving it
	for(i = 0; fgets(readLine, LENGHT + LEN_OFFSET, fileIn) != NULL; i++) {
		for (j = 0; j < LENGHT + LEN_OFFSET; j++) {
			if (readLine[j] == WALL_SYM) {
				matrix[i][j] = new Wall();
			} else if (readLine[j] == PLAYER_SYM) {
				matrix[i][j] = new Player();
			} else if (readLine[j] == EMPTY_SYM) {
				matrix[i][j] = new MapObject();
			}
		}
		
	}
	//fclose(fileIn);
}