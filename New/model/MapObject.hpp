/*
This object is useful for indicate the objects in the map such as the walls, players, enemies, ecc...
*/

#ifndef EMPTY_SYM
#define EMPTY_SYM ' '
#endif

class MapObject {
public:
	/*
	Class constructor. Defines an empty object of the playground.*/
	MapObject();
	/*
	Class constructor, it requires the symbol (char) used for represent it
	*/
	MapObject(char symbol);
	char getSymbol();
protected:
	char 	symbol;
};