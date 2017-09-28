#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "MapObject.hpp"
#endif

MapObject::MapObject(char symbol){
	this->symbol = symbol;
}

char MapObject::getSymbol() {
	return this->symbol;
}

MapObject::MapObject(){
	this->symbol = EMPTY_SYM;
}