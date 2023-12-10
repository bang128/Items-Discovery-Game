#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "Location.h"

using namespace std;

class Riddle : public Location {
public:
	Riddle(char s = 'R');
	void draw();
	int visit(Player& p);
	bool play(string question, const char a[], const char b[]);
	Item* riddle = new Item("riddle");
	Item* key = new Item("key");
	void render();
};

