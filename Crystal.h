#pragma once
#include <iostream>
#include "Location.h"

using namespace std;

class Crystal : public Location {
public:
	Crystal(char s = 'C');
	void SetTaken(bool t);
	bool IsTaken();
	void draw();
	int visit(Player& p);
	Item* crystal = new Item("crystal");
	void render();
private:
	bool taken;
};
