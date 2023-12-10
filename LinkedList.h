#pragma once
#include "Item.h"

class LinkedList {
public:
	LinkedList();
	~LinkedList();
	Item* GetFirstElement(); // return the first element in the list
	void Insert(Item* p); // This would result in the item being placed at the end of the list
	Item* Find(string key); // Find the first element that has the key as its name
	Item* Remove(string key); // Remove the first element that has the key as its name from the list
	int count(string key); // Count the number of key item
private:
	Item* head;  
	Item* tail;
};