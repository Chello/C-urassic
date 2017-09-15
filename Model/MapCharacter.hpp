typedef struct MapCharacter {
	/*Referenced MapObject*/
	char *obj;
	/*Absolute position in the map*/
	int height, lenght;
	/*Lifepoints*/
	int lifePoints;
} MapCharacter;