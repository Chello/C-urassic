#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef CSTRING_H
#define CSTRING_H 
#include <cstring>
#endif

#ifndef SETTINGS_H
#define SETTINGS_H
#include "../Control/Settings.hpp"
#endif

#ifndef ITEMTYPES_H
#define ITEMTYPES_H
#include "ItemTypes.hpp"
#endif

using namespace std;

class Item {
public:
	Item();
	Item(char *obj, int height, int lenght, int amount, ItemTypes type);
	//~Item();
	/*Il riferimento all'oggetto della mappa*/
	char *obj;
	/*Posizone assoluta nella mappa*/
	int height, lenght;
	/*Ammontare della caratteristica dell'item*/
	int amount;	
	/*Il tipo di item che assume*/
	ItemTypes type;
};