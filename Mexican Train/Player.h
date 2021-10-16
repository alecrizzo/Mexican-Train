// Alec Rizzo - arizzo3@ramapo.edu
// Header file for a player
#pragma once

#include <iostream>
#include <vector>
#include "Deck.h"
#include "Tile.h"

class Player
{
public:
	Player();
	~Player();

protected:
	friend class Round;
	friend class Game;

	void printHand();
	void printTrain(Tile engine);		// Prints the train without the passed engine

	// Set functions for use with loading games
	void setScore(int newScore);
	void setHand(vector<Tile> newHand);
	void setTrain(vector<Tile> newTrain);
	void setMarker(bool mark);

	// Get functions for gameplay and set 
	int getScore();
	bool getMarker();
	vector<Tile> getHand();
	vector<Tile> getTrain();

	void addTileTrain(Tile t);
	void addTileHand(Tile t);

private:
	int score;				// Players score
	vector<Tile> hand;		// Players hand
	vector<Tile> train;		// Players train
	bool marker;			// 0/false is no marker 1/true is yes marker
};

// End of file Player.h