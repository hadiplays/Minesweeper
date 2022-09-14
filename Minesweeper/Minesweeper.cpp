// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.


/* Things to do to finish game: 
*  1.) Fix amount of mines printed to board to be mineCount distinct numbers...................FIXED
*  2.) Read brd files
*  3.) Complete win scenario
*  4.) Allow flag to show above the mine while debug button is on..............................WTV TBH
*  5.) Fix numbers being shown on right and left side walls....................................FIXED
*  6.) Move everything to a GameBoard cpp and h file for cleaner look
*  7.) Add flag counter
*  8.) Obv add comments on everything
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "TextureMaker.h"
#include <fstream>
#include "GameBoard.h"
#include "GameTiles.h"
#include <vector>
#include "RandomNumberGenerator.h"

using namespace std;

void CheckRight(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count);
void CheckLeft(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count);
void CheckUp(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count);
void CheckDown(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count);
void CheckDiagonal(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count);

void CheckRight(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    int r;
    r = initPos + 1;
    
    if (r >= 0 && r < columns * rows)
    {
        if ((!(r % columns == 0)) && tiles[r].GetIsMine() == false)
        {
            if (tiles[r].GetBorderingMines() > 0)
            {
                tiles[r].IsHiddenFalse();
                //CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                if ((r - 1) - columns >= 0)
                {
                    if (tiles[(r - 1) - columns].GetIsHidden() == 1)
                    {
                        //CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                        CheckUp(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }
                if ((r - 1) + columns < (rows * columns))
                {
                    if (tiles[(r - 1) + columns].GetIsHidden() == 1)
                    {
                        //CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                        CheckDown(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }
                if ((r - columns) >= 0)
                {
                    if (tiles[(r - columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }
                if ((r + columns) < (rows * columns))
                {
                    if (tiles[(r + columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }

            }
            else
            {
                tiles[r].IsHiddenFalse();
                //CheckDiagonal(tiles, columns, rows, gameOver, r, count);
                CheckRight(tiles, columns, rows, gameOver, r, count);
                if (r - columns >= 0)
                {
                    if (tiles[(r)-columns].GetIsHidden() == 1)
                    {
                        CheckUp(tiles, columns, rows, gameOver, r, count);
                    }
                }
                if (r + columns < (rows * columns))
                {
                    if (tiles[(r)+columns].GetIsHidden() == 1)
                    {
                        CheckDown(tiles, columns, rows, gameOver, r, count);
                    }
                }
                if ((r - columns) >= 0)
                {
                    if (tiles[(r - columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }
                if ((r + columns) < (rows * columns))
                {
                    if (tiles[(r + columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, r - 1, count);
                    }
                }
                if ((r + 1) < (columns * rows) && (r - 1) < (columns * rows) && tiles[r + 1].GetBorderingMines() > 0 && tiles[r - 1].GetBorderingMines() > 0)
                {

                    CheckDiagonal(tiles, columns, rows, gameOver, r, count);
                }
            }

        }
    }

    
}
void CheckLeft(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    int l, r, u, d;
    //l = (tempY * (columns - 1)) + (tempX - count) + tempY;
    l = initPos - 1;
    
    if (l >= 0 && l < columns * rows)
    {
        
        if (!((l + 1) % columns == 0) && tiles[l].GetIsMine() == false)
        {
            
            if (tiles[l].GetBorderingMines() > 0)
            {
                
                tiles[l].IsHiddenFalse();
                
                //CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                if ((l + 1) - columns >= 0 && (l + 1) - columns < (rows * columns))
                {
                    
                    if (tiles[(l + 1) - columns].GetIsHidden() == 1)
                    {
                        
                        //CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                        CheckUp(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }
                
                if ((l + 1) + columns < (rows * columns))
                {
                    
                    if (tiles[(l + 1) + columns].GetIsHidden() == 1)
                    {
                        
                        //CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                        CheckDown(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }
                if ((l - columns) >= 0) //had -1
                {
                    if (tiles[(l - columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }
                if ((l + columns) < (rows * columns)) //had -1
                {
                    if (tiles[(l + columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }

            }
            else
            {
                tiles[l].IsHiddenFalse();
                //CheckDiagonal(tiles, columns, rows, gameOver, l, count);
                CheckLeft(tiles, columns, rows, gameOver, l, count);
                if ((l)-columns >= 0)
                {
                    if (tiles[(l)-columns].GetIsHidden() == 1)
                    {
                        CheckUp(tiles, columns, rows, gameOver, l, count);
                    }
                }
                if (l + columns < (rows * columns))
                {
                    if (tiles[(l)+columns].GetIsHidden() == 1)
                    {
                        CheckDown(tiles, columns, rows, gameOver, l, count);
                    }
                }
                if ((l - columns) >= 0) //was (l - columns) - 1
                {
                    if (tiles[(l - columns)].GetIsHidden() == 1)
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }
                if ((l + columns) < (rows * columns)) //was (l + columns) - 1
                {
                    if (tiles[(l + columns)].GetIsHidden() == 1) 
                    {
                        CheckDiagonal(tiles, columns, rows, gameOver, l + 1, count);
                    }
                }
            }

            //tiles[l].IsHiddenFalse();
            //Recursion(tiles, tempY, tempX, columns, rows, gameOver, l, count);

        }
    }
}
void CheckUp(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    int l, r, u, d;
    u = initPos - columns;
    if (u >= 0 && u < (rows * columns) && tiles[u].GetIsMine() == false)
    {
        if (tiles[u].GetBorderingMines() > 0)
        {
            tiles[u].IsHiddenFalse();
            //CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
            if ((0 <= ((u + columns) - 1) && ((u + columns) - 1) < (columns * rows)) && tiles[(u + columns) - 1].GetIsHidden() == 1)
            {
                //CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
                CheckLeft(tiles, columns, rows, gameOver, u + columns, count);
            }
            if ((0 <= ((u + columns) + 1) && ((u + columns) + 1) < (columns * rows)) && tiles[(u + columns) + 1].GetIsHidden() == 1)
            {
                //CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
                CheckRight(tiles, columns, rows, gameOver, u + columns, count);
            }
            if (0 <= (u - 1) && (u - 1) > (columns * rows) && tiles[u - 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
            }
            if (0 <= (u + 1) && (u + 1) > (columns * rows) && tiles[u + 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
            }


        }
        else
        {
            tiles[u].IsHiddenFalse();
            //CheckDiagonal(tiles, columns, rows, gameOver, u, count);
            CheckUp(tiles, columns, rows, gameOver, u, count);
            if ((0 <= (u - 1) && (u - 1) < (columns * rows)) && tiles[(u) - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, u, count);
            }
            if ((0 <= (u + 1) && (u + 1) < (columns * rows)) && tiles[(u) + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, u, count);
            }
            if (0 <= (u - 1) && (u - 1) > (columns * rows) && tiles[u - 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
            }
            if (0 <= (u + 1) && (u + 1) > (columns * rows) && tiles[u + 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, u + columns, count);
            }
            /*if ((d + 1) < (columns * rows) && (d + columns) < (columns * rows) && tiles[d + 1].GetBorderingMines() > 0 && tiles[d + columns].GetBorderingMines() > 0)
            {

                CheckDiagonal(tiles, columns, rows, gameOver, d, count);
            }*/
            //LEFT OFF HERE BRO

        }
    }
}
void CheckDown(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    int l, r, u, d;
    d = initPos + columns;
    if (d >= 0 && d < (rows * columns) && tiles[d].GetIsMine() == false)
    {
        if (tiles[d].GetBorderingMines() > 0)
        {
            tiles[d].IsHiddenFalse();
            //CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
            if ((0 <= (d - columns) - 1 && (d - columns) - 1 < (columns * rows)) && tiles[(d - columns) - 1].GetIsHidden() == 1)
            {
                //CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
                CheckLeft(tiles, columns, rows, gameOver, d - columns, count);
                
            }
            if ((0 <= (d - columns) + 1 && (d - columns) + 1 < (columns * rows)) && tiles[(d - columns) + 1].GetIsHidden() == 1)
            {
                //CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
                CheckRight(tiles, columns, rows, gameOver, d - columns, count);
            }
            if (0 <= (d - 1) && (d - 1) > (columns * rows) && tiles[d - 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
            }
            if (0 <= (d + 1) && (d + 1) > (columns * rows) && tiles[d + 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
            }
        }
        else
        {
            tiles[d].IsHiddenFalse();
            //CheckDiagonal(tiles, columns, rows, gameOver, d, count);
            CheckDown(tiles, columns, rows, gameOver, d, count);
            if ((0 <= d - 1 && d - 1 < (columns * rows)) && tiles[(d) - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, d, count);
            }
            if ((0 <= d + 1 && d + 1 < (columns * rows)) && tiles[(d) + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, d, count);
            }
            if (0 <= (d - 1) && (d - 1) > (columns * rows) && tiles[d - 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
            }
            if (0 <= (d + 1) && (d + 1) > (columns * rows) && tiles[d + 1].GetIsHidden() == 1)
            {
                CheckDiagonal(tiles, columns, rows, gameOver, d - columns, count);
            }
            if ((d + 1) < (columns * rows) && (d + columns) < (columns * rows) && tiles[d + 1].GetBorderingMines() > 0 && tiles[d + columns].GetBorderingMines() > 0)
            {

                CheckDiagonal(tiles, columns, rows, gameOver, d, count);
            }
        }
    }

    
}
void CheckDiagonal(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    int l, r, u, d, z;
    //Top right diagonal
    z = (initPos - columns) + 1;
    //cout << z << " ";
    if (z >= 0 && z < (rows * columns) && (!(z % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
    {
        if (tiles[z].GetBorderingMines() > 0)
        {
            tiles[z].IsHiddenFalse();
            if ((0 <= (initPos - columns) && (initPos - columns) < (columns * rows)) && tiles[initPos - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + columns) && (initPos + columns) < (columns * rows)) && tiles[initPos + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + 1) && (initPos + 1) < (columns * rows)) && tiles[initPos + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos - 1) && (initPos - 1) < (columns * rows)) && tiles[initPos - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, initPos, count);
            }
        }
        else
        {
            tiles[z].IsHiddenFalse();
            CheckDiagonal(tiles, columns, rows, gameOver, z, count);
            if ((0 <= (z - columns) && (z - columns) < (columns * rows)) && tiles[z - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + columns) && (z + columns) < (columns * rows)) && tiles[z + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + 1) && (z + 1) < (columns * rows)) && tiles[z + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z - 1) && (z - 1) < (columns * rows)) && tiles[z - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, z, count);
            }

            
        }
    }
    //Top left diagonal
    z = (initPos - columns) - 1;
    //cout << z << " ";
    if (z >= 0 && z < (rows * columns) && (!((z + 1) % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
    {
        if (tiles[z].GetBorderingMines() > 0)
        {
            tiles[z].IsHiddenFalse();
            if ((0 <= (initPos - columns) && (initPos - columns) < (columns * rows)) && tiles[initPos - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + columns) && (initPos + columns) < (columns * rows)) && tiles[initPos + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + 1) && (initPos + 1) < (columns * rows)) && tiles[initPos + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos - 1) && (initPos - 1) < (columns * rows)) && tiles[initPos - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, initPos, count);
            }
        }
        else
        {
            tiles[z].IsHiddenFalse();
            CheckDiagonal(tiles, columns, rows, gameOver, z, count);
            if ((0 <= (z - columns) && (z - columns) < (columns * rows)) && tiles[z - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + columns) && (z + columns) < (columns * rows)) && tiles[z + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + 1) && (z + 1) < (columns * rows)) && tiles[z + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z - 1) && (z - 1) < (columns * rows)) && tiles[z - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, z, count);
            }
        }
    }
    //Bottom left diagonal
    z = (initPos + columns) - 1;
    //cout << z << " ";
    if (z >= 0 && z < (rows * columns) && !((z + 1) % columns == 0) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
    {
        if (tiles[z].GetBorderingMines() > 0)
        {
            tiles[z].IsHiddenFalse();
            if ((0 <= (initPos - columns) && (initPos - columns) < (columns * rows)) && tiles[initPos - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + columns) && (initPos + columns) < (columns * rows)) && tiles[initPos + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + 1) && (initPos + 1) < (columns * rows)) && tiles[initPos + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos - 1) && (initPos - 1) < (columns * rows)) && tiles[initPos - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, initPos, count);
            }
        }
        else
        {
            tiles[z].IsHiddenFalse();
            CheckDiagonal(tiles, columns, rows, gameOver, z, count);
            if ((0 <= (z - columns) && (z - columns) < (columns * rows)) && tiles[z - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + columns) && (z + columns) < (columns * rows)) && tiles[z + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + 1) && (z + 1) < (columns * rows)) && tiles[z + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z - 1) && (z - 1) < (columns * rows)) && tiles[z - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, z, count);
            }
        }
    }
    //Bottom right diagonal
    z = (initPos + columns) + 1;
    //cout << z << " ";
    if (z >= 0 && z < (rows * columns) && (!(z % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
    {
        if (tiles[z].GetBorderingMines() > 0)
        {
            tiles[z].IsHiddenFalse();
            if ((0 <= (initPos - columns) && (initPos - columns) < (columns * rows)) && tiles[initPos - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + columns) && (initPos + columns) < (columns * rows)) && tiles[initPos + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos + 1) && (initPos + 1) < (columns * rows)) && tiles[initPos + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, initPos, count);
            }
            if ((0 <= (initPos - 1) && (initPos - 1) < (columns * rows)) && tiles[initPos - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, initPos, count);
            }
        }
        else
        {
            tiles[z].IsHiddenFalse();
            CheckDiagonal(tiles, columns, rows, gameOver, z, count);
            if ((0 <= (z - columns) && (z - columns) < (columns * rows)) && tiles[z - columns].GetIsHidden() == 1)
            {
                CheckUp(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + columns) && (z + columns) < (columns * rows)) && tiles[z + columns].GetIsHidden() == 1)
            {
                CheckDown(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z + 1) && (z + 1) < (columns * rows)) && tiles[z + 1].GetIsHidden() == 1)
            {
                CheckRight(tiles, columns, rows, gameOver, z, count);
            }
            if ((0 <= (z - 1) && (z - 1) < (columns * rows)) && tiles[z - 1].GetIsHidden() == 1)
            {
                CheckLeft(tiles, columns, rows, gameOver, z, count);
            }
        }
    }
}
void Recursion(vector<GameTiles>& tiles, int columns, int rows, int gameOver, int initPos, int count)
{
    //If game isnt over and tile clicked doesn't contain mine
    if (gameOver == 0 && !(tiles[initPos].GetIsMine()))
    {
        //int l, r, u, d, z;

        ////u = ((tempY - count) * (columns - 1)) + tempX + (tempY - count);
        //u = initPos - columns;

        //if (u > 0 && u < (rows * columns))
        //{
        //    if (tiles[u].GetIsMine() == false)
        //    {
        //        if (tiles[u].GetBorderingMines() > 0)
        //        {
        //            tiles[u].IsHiddenFalse();
        //        }
        //        else
        //        {
        //            tiles[u].IsHiddenFalse();
        //            CheckUp(tiles, columns, rows, gameOver, u, count);
        //        }
        //    }
        //}
        ////l = (tempY * (columns - 1)) + (tempX - count) + tempY;
        //l = initPos - 1;

        //if (!((l + 1) % columns == 0) && tiles[l].GetIsMine() == false)
        //{
        //    if (tiles[l].GetBorderingMines() > 0)
        //    {
        //        tiles[l].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[l].IsHiddenFalse();
        //        CheckLeft(tiles, columns, rows, gameOver, l, count);
        //    }

        //    //tiles[l].IsHiddenFalse();
        //    //Recursion(tiles, tempY, tempX, columns, rows, gameOver, l, count);

        //}

        ////r = (tempY * (columns - 1)) + (tempX + count) + tempY;
        //r = initPos + 1;

        //if ((!(r % columns == 0)) && tiles[r].GetIsMine() == false)
        //{
        //    if (tiles[r].GetBorderingMines() > 0)
        //    {
        //        tiles[r].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[r].IsHiddenFalse();
        //        CheckRight(tiles, columns, rows, gameOver, r, count);
        //    }

        //}

        //


        ////d = ((tempY + count) * (columns - 1)) + tempX + (tempY + count);
        //d = initPos + columns;

        //if (d > 0 && d < (rows * columns))
        //{
        //    if (tiles[d].GetIsMine() == false)
        //    {
        //        if (tiles[d].GetBorderingMines() > 0)
        //        {
        //            tiles[d].IsHiddenFalse();
        //            //CheckRight(tiles, columns, rows, gameOver, d, count);
        //        }
        //        else
        //        {
        //            tiles[d].IsHiddenFalse();
        //           CheckDown(tiles, columns, rows, gameOver, d, count);
        //           //CheckRight(tiles, columns, rows, gameOver, d, count);
        //        }
        //    }
        //}
        
        CheckUp(tiles, columns, rows, gameOver, initPos, count);
        CheckDown(tiles, columns, rows, gameOver, initPos, count);
        CheckRight(tiles, columns, rows, gameOver, initPos, count);
        CheckLeft(tiles, columns, rows, gameOver, initPos, count);
        CheckDiagonal(tiles, columns, rows, gameOver, initPos, count);

        //z = (initPos - columns) + 1;
        ////cout << z << " ";
        //if (z > 0 && z < (rows * columns) && (!(z % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
        //{
        //    if (tiles[z].GetBorderingMines() > 0)
        //    {
        //        tiles[z].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[z].IsHiddenFalse();
        //        CheckDiagonal(tiles, columns, rows, gameOver, z, count);


        //    }
        //}

        ////Top left diagonal
        //z = (initPos - columns) - 1;
        ////cout << z << " ";
        //if (z > 0 && z < (rows * columns) && (!((z + 1) % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
        //{
        //    if (tiles[z].GetBorderingMines() > 0)
        //    {
        //        tiles[z].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[z].IsHiddenFalse();
        //        CheckDiagonal(tiles, columns, rows, gameOver, z, count);
        //    }
        //}
        ////Bottom left diagonal
        //z = (initPos + columns) - 1;
        ////cout << z << " ";
        //if (z > 0 && z < (rows * columns) && !((z + 1) % columns == 0) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
        //{
        //    if (tiles[z].GetBorderingMines() > 0)
        //    {
        //        tiles[z].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[z].IsHiddenFalse();
        //        CheckDiagonal(tiles, columns, rows, gameOver, z, count);
        //    }
        //}
        ////Bottom right diagonal
        //z = (initPos + columns) + 1;
        ////cout << z << " ";
        //if (z > 0 && z < (rows * columns) && (!(z % columns == 0)) && tiles[z].GetIsMine() == false && tiles[z].GetIsHidden() == 1)
        //{
        //    if (tiles[z].GetBorderingMines() > 0)
        //    {
        //        tiles[z].IsHiddenFalse();
        //    }
        //    else
        //    {
        //        tiles[z].IsHiddenFalse();
        //        CheckDiagonal(tiles, columns, rows, gameOver, z, count);
        //    }
        //}


    }


}

int main()
{
    GameBoard board;
    GameTiles t;

    //Side Buttons
    sf::Sprite debug(TextureMaker::GetTexture("debug"));
    sf::Sprite testOne(TextureMaker::GetTexture("test_1"));
    sf::Sprite testTwo(TextureMaker::GetTexture("test_2"));
    sf::Sprite testThree(TextureMaker::GetTexture("test_3"));

    //Numbers
    sf::Sprite numOne(TextureMaker::GetTexture("number_1"));
    sf::Sprite numTwo(TextureMaker::GetTexture("number_2"));
    sf::Sprite numThree(TextureMaker::GetTexture("number_3"));
    sf::Sprite numFour(TextureMaker::GetTexture("number_4"));
    sf::Sprite numFive(TextureMaker::GetTexture("number_5"));
    sf::Sprite numSix(TextureMaker::GetTexture("number_6"));
    sf::Sprite numSeven(TextureMaker::GetTexture("number_7"));
    sf::Sprite numEight(TextureMaker::GetTexture("number_8"));

    //Faces
    sf::Sprite happy(TextureMaker::GetTexture("face_happy"));
    sf::Sprite win(TextureMaker::GetTexture("face_win"));
    sf::Sprite lose(TextureMaker::GetTexture("face_lose"));

    //Flag and Mine
    sf::Sprite flag(TextureMaker::GetTexture("flag"));
    sf::Sprite mine(TextureMaker::GetTexture("mine"));

    //Tiles
    sf::Sprite tileHidden(TextureMaker::GetTexture("tile_hidden"));
    sf::Sprite tileRevealed(TextureMaker::GetTexture("tile_revealed"));

    //Counter
    sf::Sprite digits(TextureMaker::GetTexture("digits"));

    //Variables for capturing file data
    string text;
    int columns, rows, mineCount;

    //Open file
    ifstream file;
    file.open("boards/config.cfg");
    if (file.is_open())
    {
        //Columns
        getline(file, text);
        columns = stoi(text);
        //Rows
        getline(file, text);
        rows = stoi(text);
        //Mine Count
        getline(file, text);
        mineCount = stoi(text);

        //Add data to GameBoard class
        board.SetColumns(columns);
        board.SetRows(rows);
        board.SetMineCount(mineCount);

    }

    //Initialize vector for tiles
    vector<GameTiles> tiles(rows * columns);
    for (unsigned int i = 0; i < rows * columns; i++)
    {
        tiles.at(i) = t;
    }

    //Randomize mine positions
    int tilesWithMines = 0;
    while (tilesWithMines != mineCount)
    {
        int temp = mineCount - tilesWithMines;
        tilesWithMines = 0;
        for (unsigned int i = 0; i < temp; i++)
        {
            tiles.at(RandomNumberGenerator::Int(0, ((rows * columns) - 1))).IsMineTrue();
        }

        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            if (tiles.at(i).GetIsMine() == 1)
            {
                tilesWithMines++;
            }
        }
        
    }
    /*for (unsigned int i = 0; i < mineCount; i++)
    {
        tiles.at(RandomNumberGenerator::Int(0, ((rows * columns) - 1))).IsMineTrue();
    }*/
    
    /*for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles.at(i).GetIsMine() == 1)
        {
            tilesWithMines++;
        }
    }
    if (tilesWithMines < mineCount)
    {
        for (unsigned int i = 0; i < mineCount - tilesWithMines; i++)
        {
            tiles.at(RandomNumberGenerator::Int(0, ((rows * columns) - 1))).IsMineTrue();
        }
    }*/

    /*tilesWithMines = 0;
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles.at(i).GetIsMine() == 1)
        {
            tilesWithMines++;
        }
    }
    cout << tilesWithMines;*/

    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].GetIsMine() == 0)
        {
            int N = -10, NE = -10, E = -10, SE = -10, S = -10, SW = -10, W = -10, NW = -10;

            if ((i % (columns) == 0))
            {
                N = i - columns;
                E = i + 1;
                S = i + columns;
                NE = N + 1;
                SE = S + 1;

            }
            else if ((i + 1) % columns == (0))
            {
                N = i - columns;
                S = i + columns;
                W = i - 1;
                SW = S - 1;
                NW = N - 1;
            }
            else
            {
                N = i - columns;
                E = i + 1;
                S = i + columns;
                W = i - 1;

                NE = N + 1;
                SE = S + 1;
                SW = S - 1;
                NW = N - 1;
            }


            if (N > 0 && N < rows * columns)
            {
                if (tiles[N].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }

            }
            if (NE > 0 && NE < rows * columns)
            {
                if (tiles[NE].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (SE > 0 && SE < rows * columns)
            {
                if (tiles[SE].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (S > 0 && S < rows * columns)
            {
                if (tiles[S].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (E > 0 && E < rows * columns && (E) % columns != 0)
            {
                if (tiles[E].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (W > 0 && W < rows * columns && (W + 1) % columns != 0)
            {
                if (tiles[W].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (NW > 0 && NW < rows * columns)
            {
                if (tiles[NW].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
            if (SW > 0 && SW < rows * columns)
            {
                if (tiles[SW].GetIsMine() == 1)
                {
                    tiles[i].ChangeBorderingMines();
                }
            }
        }

        



    }

    //Checks if game is over
    int gameOver = 0;
    int restart = 0;
    bool showMines = false;
    bool clicked = false;
    /*for (unsigned int i = 0; i < rows*columns; i++)
    {
        cout << tiles.at(i).GetIsFlagged() << " ";
    }*/

    //Set Window Size
    int width, height;
    width = 32 * columns;
    height = (32 * rows) + 100;

    //Create Window
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper :)");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //While window is open
    while (window.isOpen())
    {
        sf::Event event;
        //While an event is happening
        while (window.pollEvent(event))
        {
            //Clear window; make it all white
            window.clear(sf::Color::White);

            //Closes window when you hit the top right x
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameOver == 0)
            {
                happy.setPosition((width / 2) - 32, (height - 100));
                window.draw(happy);
                

                //If mouse is clicked
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.y >= 0 && event.mouseButton.y <= height - 100)
                        {
                            if (event.mouseButton.x >= 0 && event.mouseButton.x <= width)
                            {
                                //If left button is clicked
                                /*if (event.mouseButton.button == sf::Mouse::Left)
                                {*/

                                //Store X and Y positions
                                int tempX = event.mouseButton.x / 32;
                                int tempY = event.mouseButton.y / 32;
                                //Get index of position
                                int position = (tempY * (columns - 1)) + tempX + tempY;
                                //If there is a flag on the tile, do not do anything to the tile, else, reveal the tile
                                if (tiles[position].GetIsFlagged() == false)
                                {
                                    //Change from hidden tile to revealed tile
                                    tiles[position].IsHiddenFalse();
                                    //if (tiles[position].GetIsMine() == true)
                                    //{
                                    //clicked = true;
                                    //}
                                    if (tiles[position].GetBorderingMines() == 0)
                                    {
                                        Recursion(tiles, columns, rows, gameOver, position, 1);
                                    }
                                    
                                    
                                    /*int position;

                                        position = (tempY * (columns - 1)) + (tempX - 1) + tempY;

                                        if (tiles[position].GetIsMine() == false)
                                        {
                                            tiles[position].IsHiddenFalse();
                                        }
                                    
                                        position = (tempY * (columns - 1)) + (tempX + 1) + tempY;

                                        if (tiles[position].GetIsMine() == false)
                                        {
                                            tiles[position].IsHiddenFalse();
                                        }

                                        position = ((tempY - 1) * (columns - 1)) + tempX + (tempY - 1);

                                        if (tiles[position].GetIsMine() == false)
                                        {
                                            tiles[position].IsHiddenFalse();
                                        }

                                        position = ((tempY + 1) * (columns - 1)) + tempX + (tempY + 1);

                                        if (tiles[position].GetIsMine() == false)
                                        {
                                            tiles[position].IsHiddenFalse();
                                        }*/
                                    
                                }

                                //if (tiles[position].GetIsFlagged() == true)
                                //{
                                //    continue;
                                //}
                                //else
                                //{
                                //    //Change from hidden tile to revealed tile
                                //    tiles[position].IsHiddenFalse();
                                //}



                                /*for (unsigned int i = 0; i < columns * rows; i++)
                                {
                                    cout << tiles.at(i).DisplaySprite() << " ";
                                }*/

                                //tileRevealed.setPosition(tempX, tempY);
                                //window.draw(tileRevealed);
                                std::cout << "the left button was pressed" << std::endl;
                                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                            }
                        }

                        if (event.mouseButton.y >= (height - 100) && event.mouseButton.y <= (height - 32))
                        {
                            if (event.mouseButton.x >= (width - 256) && event.mouseButton.x <= (width - 192))
                            {
                                if (showMines == true) 
                                {
                                    showMines = false;
                                    clicked = true;
                                }
                                else
                                {
                                    showMines = true;

                                    clicked = false;
                                }
                                
                                
                            }
                        }
                    }

                    //If right button is clicked
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (event.mouseButton.y >= 0 && event.mouseButton.y <= height - 100)
                        {
                            if (event.mouseButton.x >= 0 && event.mouseButton.x <= width)
                            {
                                //Store X and Y positions
                                int tempX = event.mouseButton.x / 32;
                                int tempY = event.mouseButton.y / 32;
                                //Get index of position
                                int position = (tempY * (columns - 1)) + tempX + tempY;
                                //Change from flag to unflagged and vice versa
                                tiles.at(position).ChangeIsFlagged();

                                //cout << position << tiles[position].GetIsFlagged();


                                std::cout << "the right button was pressed" << std::endl;
                                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                            }
                        }
                    }
                }

                //if (event.mouseButton.y >= (height - 100) && event.mouseButton.y <= (height - 36))
                //{
                //    if (event.mouseButton.x >= ((width / 2) - 32) && event.mouseButton.y <= ((width / 2) + 32))
                //    {
                //        //If left button is clicked
                //        if (event.mouseButton.button == sf::Mouse::Left)
                //        {
                //            gameOver = 0;
                //            std::cout << "the left button was pressed" << std::endl;
                //            std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                //            std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                //        }
                //    }
                //}
            }
            else
            {
                int count = 0;
                for (unsigned int i = 0; i < rows; i++)
                {
                    for (unsigned int j = 0; j < columns; j++)
                    {
                        if (tiles[count].GetIsMine() == true)
                        {
                            tiles.at(count).IsHiddenFalse();
                        }
                        count++;
                    }
                }
                lose.setPosition((width / 2) - 32, (height - 100));
                window.draw(lose);

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.y >= height - 100 && event.mouseButton.y <= height)
                        {
                            if (event.mouseButton.x >= ((width / 2) - 32) && event.mouseButton.x <= ((width / 2) + 32))
                            {
                                gameOver = 0;
                                for (unsigned int i = 0; i < tiles.size(); i++)
                                {
                                    tiles[i].IsMineFalse();
                                    tiles[i].IsHiddenTrue();
                                    tiles[i].ResetBorderingMines();
                                    if (tiles[i].GetIsFlagged() == true)
                                    {
                                        tiles[i].ChangeIsFlagged();
                                    }
                                    
                                }
                                restart = 1;

                                std::cout << "the left button was pressed" << std::endl;
                                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                                std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                            }
                        }
                    }
                }
            }
            
            
            //else
            //{
            //    int count = 0;
            //    for (unsigned int i = 0; i < rows; i++)
            //    {
            //        for (unsigned int j = 0; j < columns; j++)
            //        {
            //            if (tiles[count].GetIsMine() == true)
            //            {
            //                tiles.at(count).ChangeIsHidden();
            //            }
            //            count++;
            //        }
            //    }
            //    lose.setPosition((width / 2) - 32, (height - 100));
            //    window.draw(lose);

            //    //If mouse is clicked
            //    if (event.type == sf::Event::MouseButtonPressed)
            //    {
            //        if (event.mouseButton.y >= (height - 100) && event.mouseButton.y <= (height - 36))
            //        {
            //            if (event.mouseButton.x >= ((width / 2) - 32) && event.mouseButton.y <= ((width / 2) + 32))
            //            {
            //                //If left button is clicked
            //                if (event.mouseButton.button == sf::Mouse::Left)
            //                {
            //                    gameOver = 0;
            //                    std::cout << "the left button was pressed" << std::endl;
            //                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
            //                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            //                }
            //            }
            //        }
            //    }
            //}


            int count = 0;
            for (unsigned int i = 0; i < rows; i++)
            {
                for (unsigned int j = 0; j < columns; j++)
                {
                    //cout << tiles.at(i).DisplaySprite() << " ";

                    if (tiles.at(count).GetIsHidden() == 1)
                    {
                        //cout << gameOver << " ";
                        tileHidden.setPosition(j * 32, i * 32);
                        window.draw(tileHidden);
                        if (tiles.at(count).GetIsFlagged() == true)
                        {
                            flag.setPosition(j * 32, i * 32);
                            window.draw(flag);
                        }
                    }
                    else if(tiles.at(count).GetIsHidden() == 0)
                    {
                        //cout << gameOver << " ";
                        tileRevealed.setPosition(j * 32, i * 32);
                        window.draw(tileRevealed);

                        if (tiles.at(count).GetIsMine() == true)
                        {
                            if (tiles.at(count).GetIsFlagged() == true)
                            {
                                flag.setPosition(j * 32, i * 32);
                                window.draw(flag);

                            }
                            
                            //cout << gameOver << " ";
                            mine.setPosition(j * 32, i * 32);
                            window.draw(mine);
                            //if (clicked == false)
                            //{
                                gameOver = 1;
                            //}
                            
                            
                            
                            //clicked = false;
                        //}

                        //cout << gameOver << " ";
                        /*int count = 0;
                        for (unsigned int i = 0; i < rows; i++)
                        {
                            for (unsigned int j = 0; j < columns; j++)
                            {
                                if (tiles[count].GetIsMine() == true)
                                {
                                    tiles.at(count).ChangeIsHidden();
                                }
                                count++;
                            }
                        }
                        lose.setPosition((width / 2) - 32, (height - 100));
                        window.draw(lose);*/

                        }
                        else
                        {
                            switch (tiles.at(count).GetBorderingMines()) {

                            case 1:
                                numOne.setPosition(j * 32, i * 32);
                                window.draw(numOne);
                                break;

                            case 2:
                                numTwo.setPosition(j * 32, i * 32);
                                window.draw(numTwo);
                                break;

                            case 3:
                                numThree.setPosition(j * 32, i * 32);
                                window.draw(numThree);
                                break;

                            case 4:
                                numFour.setPosition(j * 32, i * 32);
                                window.draw(numFour);
                                break;

                            case 5:
                                numFive.setPosition(j * 32, i * 32);
                                window.draw(numFive);
                                break;

                            case 6:
                                numSix.setPosition(j * 32, i * 32);
                                window.draw(numSix);
                                break;

                            case 7:
                                numSeven.setPosition(j * 32, i * 32);
                                window.draw(numSeven);
                                break;

                            case 8:
                                numEight.setPosition(j * 32, i * 32);
                                window.draw(numEight);
                                break;

                            default:
                                break;
                            }
                        }
                        

                        

                    }

                    count++;
                    
                }
            }

            if (restart == 1)
            {
                //Randomize mine positions
                int tilesWithMines = 0;
                while (tilesWithMines != mineCount)
                {
                    int temp = mineCount - tilesWithMines;
                    tilesWithMines = 0;
                    for (unsigned int i = 0; i < temp; i++)
                    {
                        tiles.at(RandomNumberGenerator::Int(0, ((rows * columns) - 1))).IsMineTrue();
                    }

                    for (unsigned int i = 0; i < tiles.size(); i++)
                    {
                        if (tiles.at(i).GetIsMine() == 1)
                        {
                            tilesWithMines++;
                        }
                    }

                }



                for (unsigned int i = 0; i < tiles.size(); i++)
                {
                    if (tiles[i].GetIsMine() == 0)
                    {
                        int N = -10, NE = -10, E = -10, SE = -10, S = -10, SW = -10, W = -10, NW = -10;

                        if ((i % (columns) == 0))
                        {
                            N = i - columns;
                            E = i + 1;
                            S = i + columns;
                            NE = N + 1;
                            SE = S + 1;

                        }
                        else if ((i + 1) % columns == (0))
                        {
                            N = i - columns;
                            S = i + columns;
                            W = i - 1;
                            SW = S - 1;
                            NW = N - 1;
                        }
                        else
                        {
                            N = i - columns;
                            E = i + 1;
                            S = i + columns;
                            W = i - 1;

                            NE = N + 1;
                            SE = S + 1;
                            SW = S - 1;
                            NW = N - 1;
                        }


                        if (N > 0 && N < rows * columns)
                        {
                            if (tiles[N].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }

                        }
                        if (NE > 0 && NE < rows * columns)
                        {
                            if (tiles[NE].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (SE > 0 && SE < rows * columns)
                        {
                            if (tiles[SE].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (S > 0 && S < rows * columns)
                        {
                            if (tiles[S].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (E > 0 && E < rows * columns && (E) % columns != 0)
                        {
                            if (tiles[E].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (W > 0 && W < rows * columns && (W + 1) % columns != 0)
                        {
                            if (tiles[W].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (NW > 0 && NW < rows * columns)
                        {
                            if (tiles[NW].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                        if (SW > 0 && SW < rows * columns)
                        {
                            if (tiles[SW].GetIsMine() == 1)
                            {
                                tiles[i].ChangeBorderingMines();
                            }
                        }
                    }





                }

                /*int count = 0;
                for (unsigned int i = 0; i < rows; i++)
                {
                    for (unsigned int j = 0; j < columns; j++)
                    {
                        if (tiles[count].GetIsMine() == true)
                        {
                            mine.setPosition(j * 32, i * 32);
                            window.draw(mine);
                        }
                        count++;
                    }
                }*/

                restart = 0;
            }

            //count = 0;
            //for (unsigned int i = 0; i < rows; i++)
            //{
            //    for (unsigned int j = 0; j < columns; j++)
            //    {
            //        if (tiles.at(count).GetIsFlagged())
            //        {
            //            flag.setPosition(j * 32, i * 32);
            //            window.draw(flag);
            //        }
            //        /*else
            //        {
            //            tileHidden.setPosition(j * 32, i * 32);
            //            window.draw(tileHidden);
            //        }*/
            //        count++;
            //    }
            //}
            
            //Draw Side Buttons
            /*if (gameOver == 0)
            {
                happy.setPosition((width / 2) - 32, (height - 100));
                window.draw(happy);
            }
            else
            {
                int count = 0;
                for (unsigned int i = 0; i < rows; i++)
                {
                    for (unsigned int j = 0; j < columns; j++)
                    {
                        if (tiles[count].GetIsMine() == true)
                        {
                            tiles.at(count).ChangeIsHidden();
                        }
                        count++;
                    }
                }
                lose.setPosition((width / 2) - 32, (height - 100));
                window.draw(lose);
            }*/

            if (clicked == true)
            {
                int count = 0;
                for (unsigned int i = 0; i < rows; i++)
                {
                    for (unsigned int j = 0; j < columns; j++)
                    {
                        if (tiles.at(count).GetIsMine() == true)
                        {
                            mine.setPosition(j * 32, i * 32);
                            window.draw(mine);
                            //tiles.at(count).IsHiddenFalse();
                            //clicked = true;
                        }
                        count++;
                    }
                }
            }

            testThree.setPosition((width - 64), (height - 100));
            window.draw(testThree);
            testTwo.setPosition((width - 128), (height - 100));
            window.draw(testTwo);
            testOne.setPosition((width - 192), (height - 100));
            window.draw(testOne);
            debug.setPosition((width - 256), (height - 100));
            window.draw(debug);

            window.display();
        }

    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
