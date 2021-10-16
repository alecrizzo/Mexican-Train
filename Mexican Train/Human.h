// Alec Rizzo - arizzo3@ramapo.edu
// Header file for polymorphic human player
#pragma once

#include "Player.h"

class Human: private Player
{
public:
	Human();
	~Human();

protected:
	friend class Round;
	friend class Game;

private:
	// !ALEC These values are in player, might remove
	//int score;				// Humans score
	//vector<Tile> hand;		// Humans hand
	//vector<Tile> train;		// Humans train

};

// End of file Human.h