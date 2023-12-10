#pragma once
#ifndef BOMB_H
#define BOMB_H
#include <iostream>
#include <ctime>
#include "Riddle.h"

using namespace std;

class Bomb : public Location {
public:
	Bomb(char s = 'B');
	void draw();
	int visit(Player& p);
	Item* bomb = new Item("bomb");
	void render();
};
#endif