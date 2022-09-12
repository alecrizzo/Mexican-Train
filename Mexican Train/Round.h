//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
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

	Tile getEngine();

	void changeTurn();
	void setUpRound();
	void resetRound();
	void setEngine(Tile eng);
	void removeEngineFromDeck(Tile eng);
	void determineFirstTurn();
	void gameplayLoop();

	// Print functions
	void printMexicanTrain();
	void printBoneyard();
	void printCoin(bool coin);
	void printFirstTurn();

	void displayBoard();
	void menu();				
	int getMenuInput();
	int getMenuWidth();

	bool flipCoin(bool userVal);
	bool getUsersCoin();

	void writeSave();
	string writeSaveInput();

	vector<Tile> boneyard;
	vector<Tile> mexican_train;

	Deck roundDeck;
	Tile engine;

	Human hum;
	Computer comp;

	string turn;
	int roundNum;

	bool mexTrainOrphanDouble;
	bool gameEnd;
	bool isFirstRun;
};

// End of file Round.h