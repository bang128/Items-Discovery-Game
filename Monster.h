#pragma once
#include <iostream>
#include <ctime>
#include "Crystal.h"

using namespace std;

class Monster : public Location {
public:
	Monster(char s = 'M');
	void draw();
	int visit(Player& p);
	Item* clover = new Item("clover");
	Item* monster = new Item("monster");
	void render();
};