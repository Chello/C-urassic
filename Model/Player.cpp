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

void Player::shoot(Map *currentMap, char s){
	int y = this->height;
	int x = this->lenght;
	do {
		switch(s){
			case 'j':
			case 'J':
				x--;
				break;
			case 'i':
			case 'I':
				y--;
				break;
			case 'l':
			case 'L':
				x++;
				break;
			case 'k':
			case 'K':
				y++;
				break;
			default:break;	
		} 
	} while(currentMap->matrix[y][x] == EMPTY_SYM);

	switch(currentMap->matrix[y][x]){
		case WALL_SYM:
		case PORTAL_SYM:
			break;
		case AMMO_SYM:
		case LP_SYM:
			currentMap->matrix[y][x] = EMPTY_SYM;
			break;	
		default: 
			Enemy *e = currentMap->getEnemyByName(currentMap->matrix[y][x]);	
			e->lifePoints -= SHOOT_DAMAGE ;
			if(e->lifePoints <= 0){
				delete e;
				currentMap->matrix[y][x] == EMPTY_SYM;
			}
			break;
	}
}





	