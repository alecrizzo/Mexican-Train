// Alec Rizzo - arizzo3@ramapo.edu
// Header file for a single round
#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include "Game.h"
#include "Tile.h"
#include "Player.h"
#include "Deck.h"
using namespace std;

class Round
{
public:
	Round();
	Round(string loadTurn, int numRounds, Human p1, Computer p2, vector<Tile> load_mexican_train, vector<Tile> load_boneyard);
	~Round();

protected:
private:
	friend class Game;

	Tile getEngine();						// Determines the current engine from a double nine set

	void setUpRound();						// Sets up a new round
	void setEngine(Tile eng);				// Change the value of Engine tile
	void removeEngineFromDeck(Tile eng);	// Removes the engine from the roundDeck
	void determineFirstTurn();
	void gameplayLoop();

	// Print functions
	void printMexicanTrain();
	void printBoneyard();
	void printCoin(bool coin);				// Prints the face value of the coin
	void printFirstTurn();

	void displayBoard();					// Outputs the gameboard content for the user
	void menu();				
	int getMenuInput();
	int getMenuWidth();

	bool flipCoin(bool userVal);
	bool getUsersCoin();					// get the side of the coin the user calls

	void writeSave();						// creates a save file of the current state of the game
	string writeSaveInput();				// gets user input for the creating a save files name

	vector<Tile> boneyard;
	vector<Tile> mexican_train;

	Deck roundDeck;					// Full deck to start a round
	Tile engine;					// The current engine tile

	Human hum;						// Human player object
	Computer comp;					// Computer player object

	string turn;					// String for turns, should be either "Human" or "Computer"
	int roundNum;					// The current round number
};

// End of file Round.h