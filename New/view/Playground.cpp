#ifndef PLAYGROUND_H
#define PLAYGROUND_H value
#include "../View/Playground.hpp"
#endif

Playground::Playground() {

}

void Playground::loadMap(Map *map) {
	this->map = map;
}

void Playground::refresh() {
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < LENGHT; j++) {
			cout << map->matrix[i][j]->getSymbol();
		}
		cout << endl;
	}
}