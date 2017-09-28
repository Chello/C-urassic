#ifndef WALL_H
#define WALL_H
#include "Wall.hpp"
#endif

Wall::Wall(): MapObject(WALL_SYM){}

Wall::Wall(char symbol): MapObject(symbol){}