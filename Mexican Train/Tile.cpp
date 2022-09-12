//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
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

/* *********************************************************************
Function Name: verifyTile()
Purpose: verify that a tile is a possible tile from the double nine set
Parameters: none
Return Value: bool
Algorithm: 
			1) create a string array of possible tiles to compare to
			2) if one side of the tile is greater flip them
			3) determine if the arguments exist in the array of possible tiles
					if so return true
			4) else return false
Assistance Received: https://www.codegrepper.com/code-examples/cpp/convert+int+to+char+c%2B%2B
********************************************************************* */
bool Tile::verifyTile(int A, int B)
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
}// End of verifyTile()

/* *********************************************************************
Function Name: printTile()
Purpose: print this tiles values using sideA and sideB
Parameters: none
Return Value: void
Algorithm: output sideA-SideB so it looks like a tile
Assistance Received: none
********************************************************************* */
void Tile::printTile()
{
	cout << this->sideA << "-" << this->sideB;
}// End of printTile()

/* *********************************************************************
Function Name: getSideA()
Purpose: returns this tiles sideA
Parameters: none
Return Value: int
Algorithm: return sideA
Assistance Received: none
********************************************************************* */
int Tile::getSideA()
{
	return this->sideA;
}// End of getSideA()

/* *********************************************************************
Function Name: getSideB()
Purpose: returns this tiles sideB
Parameters: none
Return Value: int
Algorithm: return sideB
Assistance Received: none
********************************************************************* */
int Tile::getSideB()
{
	return this->sideB;
}// End of getSideB()

/* *********************************************************************
Function Name: stringTile()
Purpose: return the sideA and sideB in a string of sideA-SideB
Parameters: none
Return Value: string
Algorithm: return string of sideA-SideB
Assistance Received: none
********************************************************************* */
string Tile::stringTile()
{
	return to_string(this->sideA) + "-" + to_string(this->sideB);
}// End of stringTile()

/* *********************************************************************
Function Name: setTile()
Purpose: sets a tile using the values passed
Parameters: 
			A, integer to be set to sideA, pass by value
			B, integet to be set to SideB, pass by value
Return Value: void
Algorithm: if verifyTile is true, set this tile to sideA = A sideB = B
Assistance Received: none
********************************************************************* */
void Tile::setTile(int A, int B)
{
	// If is possible tile, set the tiles sides to that of the given arguments
	if(verifyTile(A, B) == true)
	{
		this->sideA = A;
		this->sideB = B;
	}
}// End of setTile()

/* *********************************************************************
Function Name: isDouble()
Purpose: determine if this tile is a double
Parameters: none
Return Value: bool
Algorithm: if both sideA and sideB are equal return true
Assistance Received: none
********************************************************************* */
// Checks if the current tile is  double tile
bool Tile::isDouble()
{
	if (this->sideA == this->sideB) { return true; }
	else { return false; }
}// End of isDouble()
// End of file Tile.cpp