
#include "Game.h"

Game::Game()
{
	rows = 0;
	cols = 0;
	playerRow = 0;
	playerCol = 0;
	world = nullptr;
}

void Game::SetupGame()
{	
	ifstream fcin;
	fcin.open("game.txt");
	string place;

	if (fcin.is_open()) {
		fcin >> rows >> cols;
		world = new Location * *[rows];
		for (int i = 0; i < rows; i++) {
			world[i] = new Location * [cols];
			for (int j = 0; j < cols; j++) {
				world[i][j] = new Location();
			}
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				fcin >> place;
				if (place == "crystal") {
					delete[] world[i][j];
					world[i][j] = new Crystal();
				}
				else if (place == "monster") {
					delete[] world[i][j];
					world[i][j] = new Monster();
				}
				else if (place == "bomb") {
					delete[] world[i][j];
					world[i][j] = new Bomb();
				}
				else if (place == "riddle") {
					delete[] world[i][j];
					world[i][j] = new Riddle();
				}
				else if (place == "player") {
					playerRow = i;
					playerCol = j;
					world[i][j]->SetVisited(true);
				}
				else if (place == "special") {
					delete[] world[i][j];
					world[i][j] = new Special(p);
				}
				else if (place == "storage") {
					delete[] world[i][j];
					world[i][j] = new Storage();
				}
			}
		}

	}

}

void Game::DrawGame()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == playerRow && j == playerCol) {
				cout << 'p';
				if (i != dropRow && j != dropCol) {   // if the player is not at the drop location, then call visit(p)
					world[i][j]->visit(p);
				}
				else {     // if the player is at the drop location, then set the drop location to (-1,-1) for the next step
					dropRow = -1;
					dropCol = -1;
				}
			}
			else world[i][j]->draw();
		}
		cout << endl;
	}
	
}

void Game::TranslateDirection(string direction, int& rowChange, int& colChange)
{
	{
		if (direction == "u"|| direction == "U") {
			rowChange = -1;
			colChange = 0;
		}
		else if (direction == "d" || direction == "D") {
			rowChange = 1;
			colChange = 0;
		}
		else if (direction == "l" || direction == "L") {
			rowChange = 0;
			colChange = -1;
		}
		else if (direction == "r" || direction == "R") {
			rowChange = 0;
			colChange = 1;
		}
		else {
			rowChange = 0;
			colChange = 0;
		}
	}
}

bool Game::LegalMove(int rowChange, int colChange)
{
	if ((playerRow + rowChange) >= 0 && (playerRow + rowChange) < rows && (playerCol + colChange) >= 0 && (playerCol + colChange) < cols) return true;
	else return false;
}



void Game::PlayGame()
{
	int rowChange, colChange;
	cout << "To begin the game, please let us know something about you" << endl;
	cout << "What's your name? ";
	string name;
	getline(cin, name);
	p.SetName(name);
	int age;
	cout << "How old are you? ";
	cin >> age;
	p.SetAge(age);
	cout << "WELCOME, " << p.GetName() << "! LET'S PLAY ITEMS DISCOVERER GAME!!!" << endl << endl;
	cout << "To this game, you're going to find out at least ONE item from each of THREE different type: Crystal, Clover and Riddle;" << endl;
	cout << "and all SPECIAl items which can be Candy or Chocolate. For special items, a new feature called Queue was created to " << endl;
	cout << "store those that were randomly located in the world. Also, there is a map that store the number of special items left " << endl;
	cout << "for the player to find; the player can choose to see it by option (h)ow many special items left? in the menu." << endl;
	cout << endl;
	char ans = 'N';
	while (ans != 'Y' && ans != 'y') {
		cout << "Are you ready to play?(Y/N) ";
		cin >> ans;
	}
	system("CLS");   // instruction before playing game

	SetupGame();
	while (!CheckWin()) {
		DrawGame();
		string options[] = { "up", "down", "left", "right", "show my inventory", "how many special items left?", "put down my crystal", "quit"};
		string option = GetStringOption("Which way would you like to go?", options, 8);
		if (option == "q") exit(0); // if quit
		TranslateDirection(option, rowChange, colChange);
		if (LegalMove(rowChange, colChange)) {
			playerRow = playerRow + rowChange;
			playerCol = playerCol + colChange;
			system("CLS");
			if (option == "s") { // if show my inventory
				cout << p.normalPrint(); // the program will print out the number of each item in bag
				dropRow = playerRow;
				dropCol = playerCol; // in case the player chooses to see at the location he/she drops the Crystal
			}
			else if (option == "p") { // if put down the Crystal
				if (p.inventory->Find("crystal") == NULL) { // unable if no crystal in bag
					cout << "You don't have any crystal to put down." << endl;
				}
				else {
					delete[] world[playerRow][playerCol];
					world[playerRow][playerCol] = new Crystal(); // set his/her current back to Crystal
					world[playerRow][playerCol]->SetDrop(true);  // set to show the symbol of Crystal
					Item* ptr = p.inventory->Remove("crystal"); // to remove crystal in bag then the number of crystal will decrease 1
					delete ptr;
					dropRow = playerRow;
					dropCol = playerCol;  // in case the player chooses to see at the location he/she drops the Crystal

				}
			}
			else if (option == "h") {
				cout << p.specialPrint();
				dropRow = playerRow;
				dropCol = playerCol;  // in case the player chooses to see at the location he/she drops the Crystal
			}
			else {
				if (playerRow != dropRow && playerCol != dropCol) {  // if the player is not at the drop location, then call visit(p) at this
					world[playerRow][playerCol]->visit(p);
				}
			}
		}
		else {
			system("CLS");
			cout << "Invalid move" << endl;
			dropRow = playerRow;
			dropCol = playerCol;     // in case the player chooses invalid move at the location he / she drops the Crystal
		}
		CheckWin();
	}
	DrawGame();
	cout << "CONGRATULATION, " << p.GetName() << "! You have got all three different types of essential items." << endl << "You win!!!" << endl;
}

bool Game::CheckWin()
{	
	if (p.inventory->Find("crystal") != NULL && p.inventory->Find("clover") != NULL && p.inventory->Find("key") != NULL && p.checkSpecial()) return true;
	// return true if there are at least 3 different types of items in bag and no Special items left to find
	else return false;
}
