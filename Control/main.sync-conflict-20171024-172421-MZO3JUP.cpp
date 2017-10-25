//Utilizzo la notazione #ifndef...#define...#endif cosí posso definire le varie dipendenze di ogni file internamente utilizzando appunto quel costrutto, senza che venga ridefinito.
#ifndef GAME_H
#define GAME_H
#include "../Control/Game.hpp"
#endif

//Qua dentro ci sono tutte le varie impostazioni del gioco.
#ifndef SETTINGS_H
#define SETTINGS_H
#include "Settings.hpp"
#endif

using namespace std;

int main(int argc, char const *argv[]) {
	srand(time(NULL));
	Game *g = new Game();
	g->start();

	return 0;
}