#pragma once
#include <string>

using namespace std;

class Item {
public:
	Item();
	Item(string n);
	void SetItem(string n);
	string GetItem();
	void SetNext(Item* p);
	Item* GetNext();
	string item; // item name
	Item* next;  // the next item
};