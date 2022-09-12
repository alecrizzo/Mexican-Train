//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for game related functions
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Tile.h"
#include "Human.h"
#include "Computer.h"
#include "Player.h"
#include "Round.h"
using namespace std;

class Game
{
public:
	Game();
	~Game();

protected:

private:
	void loadOrRound();
	Round readSave();
	string readSaveInput();

	Human p1;
	Computer p2;
};

// End of file Game.h