/*########################################################################
######## BOZZA DI COMMMENTI! VANNO RISCRITTI IN INGLESE TUTTI!! ##########
########################################################################*/

//Utilizzo la notazione #ifndef...#define...#endif cosí posso definire le varie dipendenze di ogni file internamente utilizzando appunto quel costrutto, senza che venga ridefinito.
#ifndef PLAYGROUND_H
#define PLAYGROUND_H value
#include "../View/Playground.hpp"
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
#include "Settings.hpp"


int main(int argc, char const *argv[]) {
	//Istanzio una nuova mappa, e gli passo il file del livello 1 (che é contenuto in 'Map_Presets')
	Map 		*provaMap = new Map("/home/chello/Unibo/Programmazione_Lanevse/C-urassic/Map_Presets/level1.map");

	Playground 	*provaView = new Playground();

	//Il Playground ha bisogno della mappa da caricare 
	provaView->loadMap(provaMap);
	//Il Playground stampa la mappa
	provaView->refresh();

	return 0;
}