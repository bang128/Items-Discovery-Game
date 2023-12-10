#include <string>
#include <sstream>
#include <iostream>
#include "Player.h"
using namespace std;

Player::Player() {
	name = "Nobody";
	age = 0;
	inventory = new LinkedList();
	SpecialItems.emplace("chocolate", 0); 
	SpecialItems.emplace("candy", 0);
}

Player::Player(string playerName, int playerAge) {
	name = playerName;
	age = playerAge;
	SpecialItems.emplace("chocolate", 0);
	SpecialItems.emplace("candy", 0);
}
void Player::SetName(string playerName) {
	name = playerName;
}
void Player::SetAge(int playerAge) {
	age = playerAge;
}
string Player::GetName() {
	return name;
}
int Player::GetAge() {
	return age;
}
string Player::ToString() {
	ostringstream infoOSS;
	infoOSS << "Name: " << name << ", Age: " << age;
	string infoStr;
	infoStr = infoOSS.str();
	return infoStr;

}
string Player::specialPrint()
{
	ostringstream out;
	out << "Special items to find: " << endl;

	for (map<string, int>::iterator it = SpecialItems.begin(); it != SpecialItems.end(); ++it) {
		out << it->first << ": " << it->second << " ";
	}
	out << endl;
	return out.str();
}
string Player::normalPrint()
{
	ostringstream out;
	out << "Your bag has " << inventory->count("crystal") << " crystals, " << inventory->count("clover") << " clovers, " << inventory->count("key") << " keys." << endl;
	return out.str();
}
bool Player::checkSpecial() {
	if (SpecialItems.at("chocolate") == 0 && SpecialItems.at("candy") == 0) return true;
	else return false;
}
bool Player::find(string s) {
	if (inventory->count(s) > 0) return true;
	else return false;
}
void CreateNewPlayer(Player players[], int index) {
	cout << "Enter the player's name: ";
	string name;
	cin >> name;
	players[index].SetName(name);
	cout << "Enter the player's age: ";
	int age;
	cin >> age;
	players[index].SetAge(age);
}

void CreateNewPlayerOption(Player players[], int numPlayers) {
	cout << "Give me the number of a player:" << endl;
	int index;
	cin >> index;
	if (index < numPlayers) {
		CreateNewPlayer(players, index);
	}
}
void ModifyPlayer(Player players[], int numPlayers, string playerName) {
	int found = -1;
	for (int i = 0; i < numPlayers; i++) {
		if (players[i].GetName() == playerName) {
			found = i;
			break;
		}
	}
	if (found != -1) {
		cout << "What would you like to modify?" << endl;
		cout << "1) Name" << endl;
		cout << "2) Age" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			cout << "What is the new name you'd like? ";
			string newName;
			cin >> newName;
			players[found].SetName(newName);
		}
		else if (choice == 2) {
			cout << "Enter a new age: ";
			int newAge;
			cin >> newAge;
			players[found].SetAge(newAge);
		}
		else cout << "Invalid choice" << endl;	
	}
	else {
		cout << "Oops: Player Name " << playerName << " not found" << endl;
	}
}
void ModifyPlayerOption(Player players[], int numPlayers) {
	string playerName;
	cout << "Enter the player's name: ";
	cin >> playerName;
	ModifyPlayer(players, numPlayers, playerName);
}
void PrintAllPlayers(Player players[], int numPlayers) {
	cout << "Printing All the Players" << endl;
	for (int i = 0; i < numPlayers; i++) {
		cout << "[" << i << "] ";
		cout << players[i].ToString() << endl;
	}
}

string GetStringOption(string message, string options[], int numOptions) {
	string choice;
	string ch[100];
	int i;
	while (true) {
		cout << message << endl;
		for (i = 0; i < numOptions; i++) {
			string str1 = options[i].substr(0, 1);
			string str2 = options[i].substr(1, options[i].size() - 1);
			cout << "(" << str1 << ")" << str2 << endl;
			ch[i] = str1;
		}
		cin >> choice;
		for (i = 0; i < numOptions; i++) {
			if (ch[i] == choice) return ch[i];
		}
		cout << "I'm sorry, but that option is not valid, please try again. " << endl;
		cin.ignore(10000, '\n');
		cin.clear();
	}
}


