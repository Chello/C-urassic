#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "MapObject.hpp"
#endif

#ifndef WALL_SYM
#define WALL_SYM '#'
#endif

class Wall: public MapObject {
public:
	Wall();
	Wall(char symbol);
};