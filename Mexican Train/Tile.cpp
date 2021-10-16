// Alec Rizzo - arizzo3@ramapo.edu

#include "Tile.h"

/*
====================================================================
								Tile
====================================================================
*/

// Default constructor for Tile()
// Constructs an empty default tile of 0-0
Tile::Tile()
{
	this->sideA = 0;
	this->sideB = 0;
}

// Parameter constuctor for Tile()
// Construct a tile using given values
Tile::Tile(int A, int B)
{
	if (verifyTile(A, B) == true)
	{
		this->sideA = A;
		this->sideB = B;
	}
	else
	{
		this->sideA = 0;
		this->sideB = 0;
	}
}

Tile::~Tile()
{

}

// Verify the legitimacy of a tile according to the tiles in a double nine set
bool Tile::verifyTile(int A, int B)	// Pass by reference to allow flipping into proper orientation
{
	string possible_tiles[] =
	{
		"0-0", "0-1", "0-2", "0-3", "0-4", "0-5", "0-6", "0-7", "0-8", "0-9",
		"1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "1-8", "1-9",
		"2-2", "2-3", "2-4", "2-5", "2-6", "2-7", "2-8", "2-9",
		"3-3", "3-4", "3-5", "3-6", "3-7", "3-8", "3-9",
		"4-4", "4-5", "4-6", "4-7","4-8", "4-9",
		"5-5", "5-6", "5-7", "5-8", "5-9",
		"6-6", "6-7", "6-8", "6-9",
		"7-7", "7-8", "7-9",
		"8-8", "8-9",
		"9-9"
	};

	if(A > B)
	{	
	// Flip the values if A is greater to match the possible tiles
		int temp = A;
		A = B;
		B = temp;
	}

	// Determine if the function arguments exist as a possible tile in the array
	int size = sizeof(possible_tiles)/sizeof(possible_tiles[0]);
	for (int i = 0; i < size; i++)
	{
		string current;
		current = possible_tiles[i];

		// Convert our ints to character for comparison (technique from https://www.codegrepper.com/code-examples/cpp/convert+int+to+char+c%2B%2B)
		// We return true if there is a match
		if((A + '0') == current[0] && (B + '0') == current[2])	
		{ 
			return true; 
		}
	}

	// If we get through the loop without a match the value must be false
	return false;
}

// 
void Tile::printTile()
{
	cout << this->sideA << "-" << this->sideB;
}

// Returns side A of the tile
int Tile::getSideA()
{
	return this->sideA;
}

// Returns side B of the tile
int Tile::getSideB()
{
	return this->sideB;
}

// Returns the tile as a string
string Tile::stringTile()
{
	return to_string(this->sideA) + "-" + to_string(this->sideB);
}

void Tile::setTile(int A, int B)
{
	// If is possible tile, set the tiles sides to that of the given arguments
	if(verifyTile(A, B) == true)
	{
		this->sideA = A;
		this->sideB = B;
	}
}

// End of file Tile.cpp