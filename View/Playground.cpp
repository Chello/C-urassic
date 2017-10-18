#ifndef PLAYGROUND_H
#define PLAYGROUND_H value
#include "../View/Playground.hpp"
#endif

Playground::Playground() {}

void Playground::loadMap(Map *map) {
	this->map = map;
}



void Playground::refresh() {
	refresh(NULL);
}

void Playground::refresh(char *messageText) {
	int i, j;
    int numStrings = 1;
	Player *player = this->map->getPlayer();

    char** statusString;

    Enemy** enemies = this->map->getEnemies();
	/*First thing to do is generate the strings*/
	/*numStrings contains the number of side strings*/
	if (messageText == NULL) 
		numStrings = 0;
	
		else {
			if (strcmp(messageText, "") == 0) {
				messageText = NULL;
				numStrings = 0;
			}
		 	else numStrings = 1;
		}
	numStrings += 1 //The player status
				+ this->map->numEnemies; //+ the enemies statuses

	//Generazione della matrice delle stringhe (secondo lo standard C++)
	statusString = new char*[numStrings];
    for (i = 0; i < numStrings; i++) {
        statusString[i] = new char[LEFT_BORDER +1];
    }
	/*Iniziamo descrivendo il player*/
	sprintf(statusString[0], "%c: %d LP, %d Ammo", *(player->obj), player->lifePoints, player->ammo);
	addSpaces(statusString[0]);

	//Scrive tutti i dettagli relativi ai nemici
	for (i = 1; i <= this->map->numEnemies; i++) {
		sprintf(statusString[i], "%c: %d Lifepoints ",
			*(enemies[i -1]->obj), enemies[i -1]->lifePoints);
		addSpaces(statusString[i]);
	}

	//Scrive l'eventuale testo passato come parametro
	if (messageText != NULL) {
		addSpaces(messageText);
		strcpy(statusString[numStrings -1], messageText);
	}
	
	//Poi inizio materialmente a scrivere tutto su console
	for (i = 0; i < this->map->height; i++) {
		if (numStrings > 0) {
			cout << statusString[--numStrings];
		} else {
			for (j = 0; j < LEFT_BORDER; j++){
				cout << ' ';
			}
		}
		for (j = 0; j < this->map->lenght; j++) {
			cout << map->matrix[i][j];
		}
		cout << endl;
	}

	//Se ancora non sono esaurite delle righe dei dettagli, esauriscile
	while (numStrings > 0) {
		cout << statusString[--numStrings] << endl;
	}
}

void Playground::addSpaces(char *c) {
	//Calcola lo spazio da dedicare alle informazioni sul lato sinistro della mappa
	int i;
	int spacesLR = (LEFT_BORDER - strlen(c)) /2;;
        
	char cc[LEFT_BORDER];
	char spc[spacesLR+1]; 

	//spacesLR  = (LEFT_BORDER - strlen(c)) /2;
	for (i = 0; i < spacesLR; i++) {
		spc[i] = ' ';
	}

	spc[spacesLR] = '\0';
	strcpy(cc, c);
	sprintf(c, "%s%s%s", spc, cc, spc);
	if (strlen(c) == (LEFT_BORDER -1)) 
		sprintf(c, "%s ", c);

}