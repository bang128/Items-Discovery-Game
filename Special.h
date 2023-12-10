#pragma once
#include <ctime>
#include <map>
#include "Location.h"

using namespace std;

class Special : public Location {  // Special items which the player needs to find all to win and cannot be dropped
public:
	Special(Player& p, char s = 's'); // constructor
	void SetTaken(bool t);
	bool IsTaken();
	void draw();
	int visit(Player& p);
	void render();
private:
	Item* special;  // there are 2 kinds of special items: Chocolate and Candy
	bool taken;    // the player can choose to take it or not
};