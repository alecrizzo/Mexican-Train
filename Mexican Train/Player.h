//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for a player
#pragma once

#include <iostream>
#include <vector>
#include "Deck.h"
#include "Tile.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();

protected:
	friend class Round;
	friend class Game;

	// Main gameplay functions (defined in Computer and Human)
	virtual void playTurn();
	virtual void playTile(Tile tile, string trainChoice, vector<Tile>& mex_train, Player& computer);

	void flipTileForComputerTrain(Tile& tile, vector<Tile> computer_train);
	void flipTileForTrain(Tile& tile, vector<Tile> passed_train);
	void removeTileHand(Tile t);

	virtual vector<Tile> playableTiles(vector<Tile> mex_train, Player computer, bool mexOrphan);
	vector<Tile> playableTilesToTrain(vector<Tile> t_train);
	vector<Tile> playableTilesToComputerTrain(vector<Tile> t_train);

	// Prints functions for use with display
	void printTrain(Tile engine);
	void printHand();
	void printM();

	// Clear functions to help setup next round
	void clearHand();
	void clearTrain();
	void clearOrphan();
	void clearMarker();
	void newRoundReset();

	// Set functions for use with loading games
	void setScore(int newScore);
	void setHand(vector<Tile> newHand);
	void setTrain(vector<Tile> newTrain);
	void setMarker(bool mark);
	void setOrphan(bool orphan);

	// Logic check functions to make sure actions can be performed
	bool isTilePlayable(Tile tile, vector<Tile> train);
	bool isTilePlayableToComputer(Tile tile, vector<Tile> computer_train);
	bool isHandElligibleTrain(vector<Tile> elligible_train);
	bool isHandElligibleComputerTrain(vector<Tile> computer_train);
	bool isTileInHand(Tile tile);
	bool hasNonDoubleFollowUp(Tile doubleTile);

	// Get functions for gameplay and set 
	int getScore();
	bool getMarker();
	bool getOrphan();
	vector<Tile> getHand();
	vector<Tile> getTrain();
	Tile getNonDoubleFollowUp(Tile doubleTile);

	// Functions to allow us to add to the member values
	virtual void addTileTrain(Tile t, vector<Tile>& t_train);
	void addTileHand(Tile t);
	virtual void addTileComputerTrain(Tile t, Player& computer);
	void addScore(int points);

	int calculateTotalPips();

private:
	// Put these classes as private friends as a workaround to accessing the data members in
	// their function definitions. In the future for Java might want to find a better way to 
	// do this as this kind of ruins the encapsulation.
	friend class Computer;
	friend class Human;

	int score;
	vector<Tile> hand;
	vector<Tile> train;	

	// false is no marker - true is yes marker
	bool marker;
	// false is no orphan double on train - true is yes
	bool orphanDouble;

};

// End of file Player.h