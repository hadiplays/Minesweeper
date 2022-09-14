#include "GameTiles.h"
#include "SFML/Graphics.hpp"

bool GameTiles::GetIsHidden()
{
	return is_Hidden;
}
void GameTiles::IsHiddenFalse()
{
	is_Hidden = false;
}
void GameTiles::IsHiddenTrue()
{
	is_Hidden = true;
}
bool GameTiles::GetIsMine()
{
	return is_Mine;
}
void GameTiles::IsMineTrue()
{
	is_Mine = true;
}
void GameTiles::IsMineFalse()
{
	is_Mine = false;
}
bool GameTiles::GetIsFlagged()
{
	return is_Flagged;
}
void GameTiles::ChangeIsFlagged()
{
	if (is_Flagged == false)
	{
		is_Flagged = true;
	}
	else if (is_Flagged == true)
	{
		is_Flagged = false;
	}
		
}
int GameTiles::GetBorderingMines()
{
	return borderingMines;
}
void GameTiles::ChangeBorderingMines()
{
	borderingMines++;
}
void GameTiles::ResetBorderingMines()
{
	borderingMines = 0;
}
