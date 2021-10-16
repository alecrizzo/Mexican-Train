// Alec Rizzo - arizzo3@ramapo.edu
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
	void matchOrRound();
	//Round readSave(int& roundNum, Human& hum, Computer& comp);
	Round readSave();
	string readSaveInput();

	Human p1;
	Computer p2;
	//Round gameRound;

	// vector<Tile> boneyard;
};

// End of file Game.h