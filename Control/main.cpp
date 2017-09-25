//Utilizzo la notazione #ifndef...#define...#endif cosí posso definire le varie dipendenze di ogni file internamente utilizzando appunto quel costrutto, senza che venga ridefinito.
#ifndef PLAYGROUND_H
#define PLAYGROUND_H value
#include "../View/Playground.hpp"
#endif

#ifndef DIRECTIONS_H
#define DIRECTIONS_H
#include "../Model/Directions.hpp"
#endif

#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

#ifndef NAMESPACE_STD_DEF
#define NAMESPACE_STD_DEF
using namespace std;
#endif

//Le dimensioni del tabellone
#ifndef SIZES
#define SIZES
#define HEIGHT 30
#define LENGHT 60
#endif

//Qua dentro ci sono tutte le varie impostazioni del gioco.
#ifndef SETTINGS_H
#define SETTINGS_H
#include "Settings.hpp"
#endif


int main(int argc, char const *argv[]) {
	bool isPlaying = true;
	//Istanzio una nuova mappa, e gli passo il file del livello 1 (che é contenuto in 'Map_Presets')
	Map 		*provaMap = new Map("C:\\Users\\Federico\\C-urassic\\Map_Presets\\level1.map");

	Playground 	*provaView = new Playground();

	//Il Playground ha bisogno della mappa da caricare 
	provaView->loadMap(provaMap);
	//Il Playground stampa la mappa
	provaView->refresh();
	while (isPlaying) {
		char input = '\0', messageText[MAXSTRLEN] = "";
		Directions dir = MOVE_NULL;
		input = 0;
		cout << "Please enter the next move: ";
		cin >> input;
		cout << input;

		switch (input) {
			case 'a':
			case 'A':
				dir = MOVE_LEFT;
				break;
			case 's':
			case 'S':
				dir = MOVE_DOWN;
				break;
			case 'd':
			case 'D':
				dir = MOVE_RIGHT;
				break;
			case 'w':
			case 'W':
				dir = MOVE_UP;
				break;
			case 'c': break;
				//We don't use 'q' because, while playing, this key could be pressed accidentally
			case 'Q':
				isPlaying = false;
				exit(0);
				break;
			default:
				strcpy(messageText, "Invalid key!");
				break;
		}

		if (provaMap->movePlayer(dir)) {

		} else {
			strcpy(messageText, "Invalid key!");
		}
		provaView->refresh(messageText);
	}


	return 0;
}