//FileName:		location.h
//Programmer:	Dan Cliburn
//Date:			9/11/2015
//Purpose:		This file defines the header for the location class

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Location
{
protected:
	bool visited;
	char symbol;
	bool drop;
	bool storage;
	bool back;
	Queue* q = new Queue();
	bool stored;

public:
	Location(char s = ' ');

	void SetVisited(bool v);
	void SetSymbol(char s);

	bool IsVisited();
	char GetSymbol();

	void SetDrop(bool d); // Is there a dropped item?
	bool GetDrop();

	void SetStorage(bool s); // Is it a Storage location? 
	bool GetStorage();

	void SetStored(bool s);  // Does the player choose to store the item?
	bool GetStored();

	void SetBack(bool b);  // To avoid asking the player to retrieve item immediately after they drop it at the Storage location
	bool GetBack();

	virtual void draw();
	virtual int visit(Player& p);

	LinkedList* list = new LinkedList();

	virtual void render();
};

#endif