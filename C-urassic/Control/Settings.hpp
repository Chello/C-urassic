//Settings.hpp
//Qua si definiscono alcune impostazioni per l'intero gioco.

//Ad esempio i simboli dei vari elementi del tabellone

#define WALL_SYM '#'
#define PLAYER_SYM '@'
#define EMPTY_SYM ' '

/*The max string lenght*/
#define MAXSTRLEN 50

//Ad ogni modo in ogni elemento (che é un oggetto dentro la cartella Model) c'é giá un'implementazione di default, quindi se non viene definita adesso non importa.

//Qua decido che quando comincia una partita il player ha 100 'punti vita'
#define STARTING_LIFEPOINTS 100

/*
If the tag 'AUTOREFRESH' is defined, after every move the playground is refreshed to screen
*/
//#define AUTOREFRESH