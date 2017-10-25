//Settings.hpp

//Sto definendo tutte le classi che dipendono da altre
class Map;
class Enemy;
//Qua si definiscono alcune impostazioni per l'intero gioco.

//Ad esempio i simboli dei vari elementi del tabellone

#define WALL_SYM '#'
//#define PLAYER_SYM "\u2658"
#define PLAYER_SYM '@'
#define EMPTY_SYM ' '
#define PORTAL_SYM '0'
#define AMMO_SYM '-'
#define LP_SYM '^'

/*La lunghezza massima della stringa*/
#define MAXSTRLEN 50

//Ad ogni modo in ogni elemento (che é un oggetto dentro la cartella Model) c'é giá un'implementazione di default, quindi se non viene definita adesso non importa.

//Qua decido che quando comincia una partita il player ha 100 'punti vita'
#define STARTING_LIFEPOINTS 100

#define STARTING_AMMO 30

//Moltiplicatore dei nemici per la generazone nella mappa
#define MULT_ENEMIES 3

//Moltiplicatore degli item totali nella mappa
#define MULT_ITEM 2