#ifndef PLAYER_H
#define PLAYER_H
#include "../Model/Player.hpp"
#endif

Player::Player() {
}

Player::Player(char *obj, int height, int lenght, int lifePoints, int ammo) {
	this->obj = obj;
	this->height = height; 
	this->lenght = lenght;
	this->lifePoints = lifePoints;
	this->ammo = ammo;
}

void Player::shoot(Map currentMap, char s){
	int y = this->height;
	int x = this->lenght;
	while(currentMap->matrix[y][x] == EMPTY_SYM){
		switch(s){
			case 'j':
			case 'J':
				x--;
			case 'i':
			case 'I':
				y--;
			case 'l':
			case 'L':
				x++;
			case 'k':
			case 'K':
				y++;			
		}

	}
	switch(currentMap->matrix[y][x]){
		case WALL_SYM:
		case PORTAL_SYM.
			break;
		case AMMO_SYM:
		case LP_SYM:
			currentMap->matrix[y][x] = EMPTY_SYM;
		default: 
			Enemy e = currentMap->getEnemyByName(currentMap->matrix[y][x]);	
			e->lifepoints -= SHOOT_DAMAGE ;
			if(e->lifepoints <= 0){
				delete e;
				currentMap->matrix[y][x] == EMPTY_SYM;
			}
	}
}





	