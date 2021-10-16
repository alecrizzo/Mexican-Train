// Alec Rizzo - arizzo3@ramapo.edu
// Header file for the domino tiles
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tile
{
public:
	Tile();							// construct an empty tile 
	Tile(int A, int B);				// construct a tile using given values
	~Tile();

	void printTile();

protected:
	friend class Round;
	friend class Game;
	friend class Player;

	int getSideA();
	int getSideB();
	string stringTile();
	void setTile(int A, int B);
	
	bool verifyTile(int A, int B);	// verify the legitimacy of a tile

private:
	int sideA;
	int sideB;
};

// End of file Tile.h