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

private:
	Map 		*map;
	
};