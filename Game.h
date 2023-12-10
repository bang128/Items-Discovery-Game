#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Crystal.h"
#include "Bomb.h"
#include "Monster.h"
#include "Riddle.h"
#include "Special.h"
#include "Storage.h"

using namespace std;

class Game {
public:
	Game();
	void SetupGame();
	void DrawGame();
	void TranslateDirection(string direction, int& rowChange, int& colChange);
	bool LegalMove(int rowChange, int colChange);
	void PlayGame();
	bool CheckWin();
protected:
	Location*** world;
	Player p;
	int rows;
	int cols;
	int playerRow;
	int playerCol;
	int dropRow = -1;
	int dropCol = -1;
};
#endif