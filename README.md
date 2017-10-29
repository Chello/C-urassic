Gioco C-urassic Park
Realizzato da Francesco Bassanelli, Simone Mignani, Francesco Pezzulli e Federico Rachelli.

Per iniziare a giocare compilare il gioco eseguendo i comandi

make clean
make

Successivamente eseguirlo con

./C-urassic

Lo scopo del gioco é giungere e superare il sesto livello.
Si inzia dal primo livello.
Il player deve raggiungere il portale di ogni livello per passare al successivo.
Il player si muove con la disposizione 'AWSD'.

Nella mappa sono presente un numero di nemici proporzionale al livello in cui si sta giocando. 
Lo scopo dei nemici é 'scontrarsi' con il player, decrementandogli i lifepoints.
All'avanzare del livello i nemici aumentano ed aumenta la loro intelligenza, permettendogli di fare mosse piú oppure meno favorevoli.

Il player si puó difendere dalle mosse dei nemici sparando (con la disposizione 'JIKL').
Un nemico con vita minore o uguale a 0 muore, scomparendo dalla mappa

Lo stato dei nemici, come quello del player, si puó vedere nel lato sinistro della mappa.

Il player ha un numero limitato di munizioni e di lifepoints, che puó comunque incrementare attraverso potenziamenti sparsi per la mapppa.


Tutte le configurazioni parametriche del gioco sono disponibili e modificabili all'interno del file 'Settings.hpp'. 


Enjoy!