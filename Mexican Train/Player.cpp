// Alec Rizzo - arizzo3@ramapo.edu

#include "Player.h"

/*
====================================================================
							  Player
====================================================================
*/

Player::Player()
{
	this->hand.clear();
	this->train.clear();
	this->score = 0;
}

Player::~Player()
{

}

// Prints the values of a players hand
void Player::printHand()
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		this->hand.at(i).printTile();
		cout << " ";

	}
}

// Prints the values of a players train
void Player::printTrain(Tile engine)
{
	for (unsigned int i = 0; i < this->train.size(); i++)
	{
		if (this->train.at(i).getSideA() == engine.getSideA() && this->train.at(i).getSideB() == engine.getSideB())
		{
			continue;
		}
		else
		{
			this->train.at(i).printTile();
			cout << " ";
		}
	}
}

void Player::setScore(int newScore)
{
	this->score = newScore;
}

void Player::setHand(vector<Tile> newHand)
{
	this->hand = newHand;
}

void Player::setTrain(vector<Tile> newTrain)
{
	this->train = newTrain;
}

void Player::setMarker(bool mark)
{
	this->marker = mark;
}

// Returns the score of the player
int Player::getScore()
{
	return this->score;
}

// Returns the train of the player
vector<Tile> Player::getTrain()
{
	return this->train;
}

// Returns the hand of the player
vector<Tile> Player::getHand()
{
	return this->hand;
}

// Returns the marker of the player
bool Player::getMarker()
{
	return this->marker;
}


void Player::addTileTrain(Tile t)
{
	this->train.push_back(t);
}

void Player::addTileHand(Tile t)
{
	this->hand.push_back(t);
}

// End of file Player.cpp