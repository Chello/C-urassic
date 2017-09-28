#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "MapObject.hpp"
#endif

#ifndef PLAYER_SYM
#define PLAYER_SYM '@'
#endif

class Player: public MapObject {
public:
	Player();
	Player(char symbol);
	/*
	This method returns the current lifepoints of the player
	*/
	int getLifePoints();
	/*
	This methods removes the amount of points gave in 'points' 
	*/
	void struck(int points);

protected:
	int lifePoints;
};