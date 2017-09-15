#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef MAP_H
#define MAP_H
#include "../Model/Map.hpp"
#endif

#ifndef NAMESPACE_STD_DEF
#define NAMESPACE_STD_DEF
using namespace std;
#endif

#ifndef SIZES
#define SIZES
#define HEIGHT 30
#define LENGHT 60
#endif

/*This is the left border for some messages*/
#define LEFT_BORDER 30

class Playground {
public:
	/*
	Class constructor. It does nothing
	*/
	Playground();
	/*
	Loads the map for the first time. 
	*/
	void loadMap(Map *map);
	/*
	Refresh the map to stdout
	*/
	void refresh();
	/*
	Refresh the map to stdout.
	It also displays the message string passed. 
	If left blank, it will do the same operations of refresh()
	*/
	void refresh(char *messageText);

private:
	/*The link to the map*/
	Map 		*map;
	/*This methods adds spaces to string gave for reach LEFT_BORDER size*/
	void addSpaces(char *c);
};