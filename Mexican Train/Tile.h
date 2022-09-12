//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for the domino tiles
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tile
{
public:
	Tile();
	Tile(int A, int B);	
	~Tile();

	void printTile();

protected:
	friend class Round;
	friend class Game;
	friend class Player;
	friend class Human;
	friend class Computer;

	int getSideA();
	int getSideB();
	string stringTile();
	void setTile(int A, int B);
	bool verifyTile(int A, int B);
	bool isDouble();

private:
	int sideA;
	int sideB;
};

// End of file Tile.h