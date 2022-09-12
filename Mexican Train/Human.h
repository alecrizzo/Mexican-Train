//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for polymorphic human player
#pragma once

#include "Player.h"
#include "Computer.h"

using namespace std;

class Human: private Player
{
public:
	Human();
	~Human();

protected:
	friend class Round;
	friend class Game;
	friend class Computer;

	virtual void playTurn(vector<Tile>& mex_train, vector<Tile>& yard, Computer& computer, bool& mexOrphan, bool& gameEnd);
	virtual void playTile(Tile tile, string trainChoice, vector<Tile>& mex_train, vector<Tile>& yard, Computer& computer, bool& mexOrphan, bool& gameEnd);
	void noPlayableTiles(vector<Tile>& mex_train, vector<Tile>& yard, Computer& computer, bool& mexOrphan);
	bool twoPlayableDoubles(vector<Tile> mex_train, vector<Tile> computer_train);

	Tile pickTile(vector<Tile> passed_train);
	Tile pickTileComputerTrain(vector<Tile> computer_train);
	string selectTrain(vector<Tile> mex_train, Computer computer);

	virtual vector<Tile> playableTiles(vector<Tile> mex_train, Computer computer);

	void help(vector<Tile> mex_train, Computer computer, bool mexOrphan);

private:

};

// End of file Human.h