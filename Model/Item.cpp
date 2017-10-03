#ifndef ITEM_H
#define ITEM_H
#include "../Model/Item.hpp"
#endif

Item::Item() {}

Item::Item(char *obj, int height, int lenght, int amount, ItemTypes type) {
	this->obj = obj;
	this->height = height;
	this->lenght = lenght;
	this->amount = amount;
	this->type = type;
}

