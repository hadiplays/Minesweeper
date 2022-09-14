#pragma once
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;
class GameTiles
{
private:
	bool is_Hidden = true;
	bool is_Mine = false;
	bool is_Flagged = false;
	int borderingMines = 0;

public:
	bool GetIsHidden();
	void IsHiddenFalse();
	void IsHiddenTrue();

	bool GetIsMine();
	void IsMineTrue();
	void IsMineFalse();

	bool GetIsFlagged();
	void ChangeIsFlagged();

	int GetBorderingMines();
	void ChangeBorderingMines();
	void ResetBorderingMines();
};

