#include "Item.h"
#include <iostream>

class Queue {
private:
	Item* head;
	Item* tail;
public:
	Queue(); // default constructor
	~Queue(); // destructor
	void Print(); // to print out the queue
	void Enqueue(Item* p); // to add the new element at the front of queue
	Item* Dequeue(); // to delete the first element and return it
	Item* Remove(string key); // to remove the first element that has the key as its name
	bool isempty();  // to check if the queue is empty
};