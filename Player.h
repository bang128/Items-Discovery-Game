#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include <sstream>
#include "LinkedList.h"
#include "Queue.h"
using namespace std;

class Player {
public:
	Player();
	Player(string playerName, int playerAge);
	void SetName(string playerName);
	void SetAge(int playerAge);
	string GetName();
	int GetAge();
	string ToString();
	LinkedList* inventory; // for the player's investory, to get items to bag
	map<string, int> SpecialItems; // to store the number of each Special items left to find
	string specialPrint(); // to print out each special item and its number left to find
	string normalPrint();  // to print out the player's bag
	bool checkSpecial(); // to check if all Special items are found
	bool find(string s);
private:
	string name;
	int age;
};

void CreatNewPlayer(Player players[], int index);
void CreateNewPlayerOption(Player players[], int numPlayers);
void ModifyPlayer(Player players[], int numPlayers, string playerName);
void ModifyPlayerOption(Player players[], int numPlayers);
void PrintAllPlayers(Player players[], int numPlayers);
string GetStringOption(string message, string options[], int numOptions);



