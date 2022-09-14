#pragma once
#include "GameTiles.h"
#include <vector>

using namespace std;


class GameBoard
{
private:
	int columns;
	int rows;
	int mineCount;
	vector<GameTiles> tiles;

public:
	void SetColumns(int columns);
	void SetRows(int rows);
	void SetMineCount(int mineCount);
};

