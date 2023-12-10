#pragma once
#include "Location.h"

// This class is to save the item the player dropped, then the player can retrieve it later

class Storage : public Location {
public:
	Storage(char s = 'S');
	void draw();
	int visit(Player& p);
	void render();
private:
	Item* store;  // the item the player dropped (it is based on which item the player chooses to drop, could be Crystal, Clover or Key)
};
