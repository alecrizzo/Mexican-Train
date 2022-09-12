//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for the full deck
#pragma once

#include "Tile.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <random>      

using namespace std;

class Deck
{
public:
	Deck();

	void printDeck();

protected:
	friend class Player;
	void popNumTiles(vector<Tile> & stack, int num);

private:
	friend class Round;

	void shuffleDeck();
	vector<Tile> double_nine_set;
	const int DOUBLE_NINE_SIZE = 55;
};

// End of file Deck.h