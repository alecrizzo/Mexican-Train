//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
// Header file for polymorphic computer player
#pragma once

#include "Player.h"
#include "Human.h"

class Computer : private Player
{
public:
	Computer();
	~Computer();

protected:
	friend class Round;
	friend class Game;
	friend class Human;

	virtual void printM();

	virtual void playTile(Tile tile, string trainChoice, vector<Tile>& mex_train, vector<Tile>& yard, Human& human, bool& mexOrphan, bool& gameEnd);
	virtual void playTurn(vector<Tile>& mex_train, vector<Tile>& yard, Human& human, bool& mexOrphan, bool& gameEnd);
	void noPlayableTiles(vector<Tile>& mex_train, vector<Tile>& yard, Human& human, bool& mexOrphan);
	virtual void addTileComputerTrain(Tile t);

	bool checkPlayableDoubles(vector<Tile> playable_tiles);
	bool twoPlayableDoubles(vector<Tile> mex_train, vector<Tile> human_train);

	Tile getPlayableDouble(vector<Tile> playable_tiles);
	Tile getComputerChoice(vector<Tile> playable_tiles);
	string getTrainChoice(Tile tile, Human human, vector<Tile> mex_train);

private:
};

// End of file Computer.h