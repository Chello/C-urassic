//Settings.hpp

//Sto definendo tutte le classi che dipendono da altre
class Map;
class Enemy;
//class Player;

//Qua si definiscono alcune impostazioni per l'intero gioco.

//Ad esempio i simboli dei vari elementi del tabellone

#define WALL_SYM '#'
//#define PLAYER_SYM "\u2658"
#define PLAYER_SYM '@'
#define EMPTY_SYM ' '
#define PORTAL_SYM '0'
#define AMMO_SYM '='
#define LP_SYM '^'

/*La lunghezza massima della stringa*/
#define MAXSTRLEN 50

//Ad ogni modo in ogni elemento (che é un oggetto dentro la cartella Model) c'é giá un'implementazione di default, quindi se non viene definita adesso non importa.

//Qua decido che quando comincia una partita il player ha 100 'punti vita'
#define STARTING_LIFEPOINTS 100

#define STARTING_AMMO 10

//Moltiplicatore dei nemici per la generazone nella mappa
#define MULT_ENEMIES 4

//Moltiplicatore degli item per ogni stanza della mappa
#define MULT_ITEM 2

//Massimo numero di mosse ammissibili in input
#define MAX_INPUT_MOVE 3

//Massimo numero di mosse ammissibili da un nemico tramite l'intelligenza artificiale
#define MAX_ENEMY_MOVE 1

//Ammo che si aggiungono allo scontro con un AMMO_SYM
#define ADD_AMMO 5

//LP che si aggiungono allo scontro con un LP_SYM
#define ADD_LP 50

//LP che vengono tolti ad un nemico se colpito dallo sparo
#define SHOOT_DAMAGE 50

//Punti vita che i nemici tolgono al player
#define ENEMY_DAMAGE 50

/*Moltiplicatore di probabilitá che una mossa sia casuale oppure no.
La probabilitá che un nemico esegua l'azione secondo l'intelligenza dipende da:
MULT_RANDOM_ENEMY_MOVE * numero del livello attuale.
*/
#define MULT_RANDOM_ENEMY_MOVE 15

//Decommentare la define del debug per attivare stringhe verbose di ció che accade
//#define DEBUG