#include <iostream>
#include "Location.h"
#include "videoGame.h"


Location::Location(char s) {
	symbol = s;
	visited = false;
	drop = false;
	storage = false;
	stored = false;
	back = false;
	list = new LinkedList(); //dynamically allocated a new linked list
}
void Location::SetVisited(bool v) {
	visited = v;
}
void Location::SetSymbol(char s) {
	symbol = s;
}
void Location::SetDrop(bool d)
{
	drop = d;
}
bool Location::IsVisited() {
	return visited;
}
char Location::GetSymbol() {
	return symbol;
}

bool Location::GetDrop()
{
	return drop;
}

void Location::SetStorage(bool s)
{
	storage = s;
}

bool Location::GetStorage()
{
	return storage;
}

void Location::SetStored(bool s)
{
	stored = s;
}

bool Location::GetStored()
{
	return stored;
}

void Location::SetBack(bool b)
{
	back = b;
}

bool Location::GetBack()
{
	return back;
}

void Location::draw()
{
		if (visited) cout << symbol;
		else cout << '.';
}

int Location::visit(Player& p)
{
	visited = true;
	
	return 1;
}

void Location::render()
{
	if (visited == true && symbol != ' ') //We have been to this spot and it is not a default location
	{
		//We are using the "symbol" as the texture ID.  Since 
		//"symbol" is a char, it must be casted to an int
		Videogame::renderBitMap((int)(symbol));
	}
}
