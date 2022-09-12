//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
#include "Player.h"

/*
====================================================================
							  Player
====================================================================
*/

// Constructor of Player class
Player::Player()
{
	this->hand.clear();
	this->train.clear();
	this->score = 0;
	this->marker = false;
	this->orphanDouble = false;
}

Player::~Player()
{
}

void Player::playTurn()
{
}

void Player::playTile(Tile tile, string trainChoice, vector<Tile>& mex_train, Player& computer)
{
}

/* *********************************************************************
Function Name: printHand()
Purpose: print the tiles in the Players hand
Parameters:
Return Value: void
Algorithm:
			1) for loop to print all values in hand
Assistance Received: none
********************************************************************* */
void Player::printHand()
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		this->hand.at(i).printTile();
		cout << " ";

	}
}// End of printHand()

/* *********************************************************************
Function Name: printTrain()
Purpose: print the tiles in the Players train
Parameters:
Return Value: void
Algorithm:
			1) for loop to print all values in train
Assistance Received: none
********************************************************************* */
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
}// End of printTrain()

/* *********************************************************************
Function Name: printM()
Purpose: print M if there is a marker on the train
Parameters:
Return Value: void
Algorithm:
			1) if marked train, print M to show marker in output
Assistance Received: none
********************************************************************* */
void Player::printM()
{
	if (this->marker == true)
	{
		cout << "M";
	}
}// End of printM

/* *********************************************************************
Function Name: setScore
Purpose: set int value for member variable score
Parameters:	int newScore passed by value
Return Value: void
Algorithm: assign value
Assistance Received: none
********************************************************************* */
void Player::setScore(int newScore)
{
	this->score = newScore;
}// End of setScore()

/* *********************************************************************
Function Name: setHand()
Purpose: set hand vector to the passed vector
Parameters:	new_hand vector of tiles passed by value
Return Value: void
Algorithm: assign value
Assistance Received: none
********************************************************************* */
void Player::setHand(vector<Tile> new_hand)
{
	this->hand = new_hand;
}// End of setHand()

/* *********************************************************************
Function Name: setTrain()
Purpose: set train vector to the passed vector
Parameters:	new_train vector of tiles passed by value
Return Value: void
Algorithm: assign value
Assistance Received: none
********************************************************************* */
void Player::setTrain(vector<Tile> new_train)
{
	this->train = new_train;
}// End of setTrain

/* *********************************************************************
Function Name: setMarker()
Purpose: set merker to the passed marker value
Parameters:	mark, boolean for if train is marked passed by value
Return Value: void
Algorithm: assign value
Assistance Received: none
********************************************************************* */
void Player::setMarker(bool mark)
{
	this->marker = mark;
}// End of setMarker()


/* *********************************************************************
Function Name: getScore()
Purpose: get the score value
Parameters:	none
Return Value: int
Algorithm: return the value of score
Assistance Received: none
********************************************************************* */
int Player::getScore()
{
	return this->score;
}// End of getScore()

/* *********************************************************************
Function Name: getTrain()
Purpose: get the train
Parameters:	none
Return Value: vector<Tile>
Algorithm: return the train
Assistance Received: none
********************************************************************* */
vector<Tile> Player::getTrain()
{
	return this->train;
}// End of getTrain()

/* *********************************************************************
Function Name: getHand()
Purpose: get the hand
Parameters:	none
Return Value: vector<Tile>
Algorithm: return the hand
Assistance Received: none
********************************************************************* */
vector<Tile> Player::getHand()
{
	return this->hand;
}// End of getHand()

/* *********************************************************************
Function Name: getMarker()
Purpose: get the marker
Parameters:	none
Return Value: bool
Algorithm: return the marker
Assistance Received: none
********************************************************************* */
bool Player::getMarker()
{
	return this->marker;
}// End of getMarker()

/* *********************************************************************
Function Name: addTileTrain()
Purpose: add tile to the train
Parameters:	
			t, tile to add to the train passed by value
			t_train, vector of tiles to push the tile onto
Return Value: void
Algorithm: push the tile t onto the passed train t_train
Assistance Received: none
********************************************************************* */
void Player::addTileTrain(Tile t, vector<Tile> & t_train)
{
	t_train.push_back(t);
}// End of addTileTrain()

/* *********************************************************************
Function Name: addTileComputerTrain()
Purpose: add tile to the computer train
Parameters:
			t, tile to add to the train passed by value
			computer, Player object to insert the values onto
Return Value: void
Algorithm: insert the tile t onto the passed computer players train at the beginning
Assistance Received: none
********************************************************************* */
void Player::addTileComputerTrain(Tile t, Player & computer)
{
	computer.train.insert(computer.train.begin(), t);
}// End of addTileComputerTrain()

/* *********************************************************************
Function Name: addTileHand()
Purpose: add tile to the hand
Parameters:
			t, tile to add to the hand passed by value
Return Value: void
Algorithm: push the tile t onto the member hand
Assistance Received: none
********************************************************************* */
void Player::addTileHand(Tile t)
{
	this->hand.push_back(t);
}// End of addTileHand()

/* *********************************************************************
Function Name: removeTileHand()
Purpose: removes the passed tile from hand
Parameters:
			t, tile to remove from the hand
Return Value: void
Algorithm:  if a matching tile exists in the hand erase it from the hand
Assistance Received: none
********************************************************************* */
void Player::removeTileHand(Tile t)
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		// If matching tile exists in hand remove the tile 
		if ((t.sideA == this->hand.at(i).sideA && t.sideB == this->hand.at(i).sideB) || ((t.sideB == this->hand.at(i).sideA && t.sideA == this->hand.at(i).sideB)))
		{
			this->hand.erase(hand.begin() + i);
			return;
		}
	}
}// End of removeTileHand()

/* *********************************************************************
Function Name: hasNonDoubleFollowUp()
Purpose: determines if player has a non double follow up tile
Parameters:
			doubleTile, tile to compare to, passed by value
Return Value: bool
Algorithm:  if a non double follow up is found return true
Assistance Received: none
********************************************************************* */
bool Player::hasNonDoubleFollowUp(Tile doubleTile)
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (doubleTile.sideA == this->hand.at(i).sideA && doubleTile.sideB == this->hand.at(i).sideB)
		{
			// Found the passed double in the hand, skip
			continue;
		}
		else if (doubleTile.sideA == this->hand.at(i).sideA || doubleTile.sideA == this->hand.at(i).sideB)
		{
			// Found a follow up to the passed double
			return true;
		}
	}
	// Couldn't find a follow up to passed double
	return false;
}// End of hasNonDoubleFollowUp

/* *********************************************************************
Function Name: getNonDoubleFollowUp()
Purpose: get the non double follow up that we determined exists using hasNonDoubleFollowUp
Parameters:
			doubleTile, tile to compare to to find a follow up, passed by value
Return Value: void
Algorithm:  if a non double follow up exists, return it
Assistance Received: none
********************************************************************* */
Tile Player::getNonDoubleFollowUp(Tile doubleTile)
{
	Tile tempTile;
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (doubleTile.sideA == this->hand.at(i).sideA && doubleTile.sideB == this->hand.at(i).sideB)
		{
			// Found the passed double in the hand, skip
			continue;
		}
		else if (doubleTile.sideA == this->hand.at(i).sideA || doubleTile.sideA == this->hand.at(i).sideB)
		{
			// Found a follow up to the passed double
			return tempTile;
		}
	}
	// Couldn't find a follow up to passed double
	return tempTile;
}// End of getNonDoubleFollowUp

/* *********************************************************************
Function Name: playableTiles()
Purpose: return a vector of playable tiles in the hand
Parameters:
			mex_train, vector of tiles for mexican train by value
			computer, Player computer passed by value
			mexOrphan, mexican train orphan value passed by value
Return Value: vector<Tile>
Algorithm:  use isTilePlayable to determine playable tiles, add them to our
			vector and when done return the playable tiles vector
Assistance Received: none
********************************************************************* */
// Returns a vector of the playable tiles in the players hand to mexican train computer train and personal train
vector<Tile> Player::playableTiles(vector<Tile> mex_train, Player computer, bool mexOrphan)
{
	vector<Tile> playable_tiles;
	playable_tiles.clear();
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (isTilePlayable(this->hand.at(i), mex_train) == true ||
			isTilePlayable(this->hand.at(i), this->train) == true ||
			isTilePlayableToComputer(this->hand.at(i), computer.train) == true)
		{
			addTileTrain(this->hand.at(i), playable_tiles);
		}
	}
	return playable_tiles;
}// End of playableTiles()

/* *********************************************************************
Function Name: playableTilesToTrain()
Purpose: gets playable tiles to one specific train
Parameters:
			t_train, vector of tiles to check if this hand is playable to, passed by value
Return Value: vector<Tile>
Algorithm:  use isTilePlayable for all values in hand on the passed train to determine
			if the tiles in hand are playable
Assistance Received: none
********************************************************************* */
vector<Tile> Player::playableTilesToTrain(vector<Tile> t_train)
{
	vector<Tile> playable_tiles;
	playable_tiles.clear();
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (isTilePlayable(this->hand.at(i), t_train) == true)
		{
			addTileTrain(this->hand.at(i), playable_tiles);
		}
	}
	return playable_tiles;
}// End of playableTilestoTrain()

/* *********************************************************************
Function Name: flipTileForTrain()
Purpose: flips a tile to the proper orientation for the passed train
Parameters:
			tile, Tile object passed by reference
			passed_train, vector of tiles passed by value
Return Value: void
Algorithm:  check the end of the trains sideB and compare it to both sideA and SideB of
			our passed tile. flip the tile if needed
Assistance Received: none
********************************************************************* */
void Player::flipTileForTrain(Tile& tile, vector<Tile> passed_train)
{
	if (passed_train.size() > 0)
	{
		if (passed_train.back().sideB == tile.sideA)
		{
			return;
		}
		else if (passed_train.back().sideB == tile.sideB)
		{
			// Flip values to the proper display for the train
			int tempside = tile.sideA;
			tile.sideA = tile.sideB;
			tile.sideB = tempside;

			return;
		}
		else
		{
			cout << "WHAT?! Error using flipTileForTrain with ";
			tile.printTile();
			cout << " to ";
			passed_train.back().printTile();
			exit(1);
		}
	}
	else
	{
		cout << "Error at flipTileForTrain, passed train has no values to compare\n";
		exit(1);
	}

}// End of flipTilesForTrain()

/* *********************************************************************
Function Name: flipTileForComputerTrain()
Purpose: flips a tile to the proper orientation for the computer train
Parameters:
			tile, Tile object passed by reference
			computer_train, vector of tiles passed by value
Return Value: void
Algorithm:  check the start of the trains sideA and compare it to both sideA and SideB of
			our passed tile. flip the tile if needed
Assistance Received: none
********************************************************************* */
void Player::flipTileForComputerTrain(Tile& tile, vector<Tile> computer_train)
{
	if (computer_train.size() > 0)
	{
		if (computer_train.front().sideA == tile.sideB)
		{
			return;
		}
		else if (computer_train.front().sideA == tile.sideA)
		{
			// Flip values to the computers logic on the board (backwards)
			int tempside = tile.sideA;
			tile.sideA = tile.sideB;
			tile.sideB = tempside;

			return;
		}
		else
		{
			cout << "WHAT?! Error using flipTileForComputerTrain with ";
			tile.printTile();
			cout << " to ";
			computer_train.front().printTile();
			exit(1);
		}
	}
}// End of flipTileForComputerTrain()


/* *********************************************************************
Function Name: setOrphan()
Purpose: set the orphan double member to the passed boolean
Parameters:
			orphan, boolean passed by value
Return Value: void
Algorithm:  set the member value to the parameter
Assistance Received: none
********************************************************************* */
void Player::setOrphan(bool orphan)
{
	this->orphanDouble = orphan;
}// End of setOrphan()

/* *********************************************************************
Function Name: getOrphan()
Purpose: get the orphan double value from the object
Parameters:
Return Value: bool
Algorithm:  return the member value of orphanDouble
Assistance Received: none
********************************************************************* */
bool Player::getOrphan()
{
	return this->orphanDouble;
}// End of getOrphan()

/* *********************************************************************
Function Name: isTilePlayable()
Purpose: determine if the passed tile is playable to the passed train
Parameters:
			tile, Tile object by value
			train, vector of Tiles by value
Return Value: bool
Algorithm:  check if the sideB of the last value in passed train is equal to either
			side of our passed tile. if so return true, otherwise return false
Assistance Received: none
********************************************************************* */
bool Player::isTilePlayable(Tile tile, vector<Tile> train)
{
	if (train.size() > 0)
	{
		int trainTail = train.back().getSideB();
		if (tile.getSideA() == trainTail || tile.getSideB() == trainTail)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}// End of isTilePlayable()

/* *********************************************************************
Function Name: isTilePlayableToComputer()
Purpose: determine if the passed tile is playable to the passed train
Parameters:
			tile, Tile object by value
			computer_train, vector of Tiles by value
Return Value: bool
Algorithm:  check if the sideA of the first value in passed train is equal to either
			side of our passed tile. if so return true, otherwise return false
Assistance Received: none
********************************************************************* */
bool Player::isTilePlayableToComputer(Tile tile, vector<Tile> computer_train)
{
	if (computer_train.size() > 0)
	{
		int trainTail = computer_train.front().getSideA();
		if (tile.getSideA() == trainTail || tile.getSideB() == trainTail)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}// End of isTilePlayableToComputer()

/* *********************************************************************
Function Name: isHandElligibleTrain()
Purpose: determine if the hand is elligible to play on the passed train
Parameters:
			elligible_train, vector of tiles to see if we can play to
Return Value: bool
Algorithm:  check if the sideB of the last value in passed train is equal to either
			side of our hands tiles. if so any of them are elligible return true,
			otherwise false.
Assistance Received: none
********************************************************************* */
bool Player::isHandElligibleTrain(vector<Tile> elligible_train)
{
	if (elligible_train.size() == 0)
	{
		return false;
	}
	else
	{
		int trainTail = elligible_train.back().getSideB();
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (trainTail == hand.at(i).getSideA() || trainTail == hand.at(i).getSideB())
			{
				return true;
			}
		}
		return false;
	}
}// End of isHandElligibleTrain()


/* *********************************************************************
Function Name: isHandElligibleComputerTrain()
Purpose: determine if the hand is elligible to play on the computer train
Parameters:
			computer_train, vector of tiles to compare our hand values to, passed by value
Return Value: bool
Algorithm:  check if the sideA of the first value in passed train is equal to either
			side of our passed hands tiles. if so any of them are elligible return true,
			otherwise false.
Assistance Received: none
********************************************************************* */
bool Player::isHandElligibleComputerTrain(vector<Tile> computer_train)
{
	// Computer train faces left so the concept is the same but the 
	// syntax is slightly flipped from isHandElligibleTrain
	if (computer_train.size() > 0)
	{
		int compTail = computer_train.front().getSideA();
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (compTail == hand.at(i).getSideA() || compTail == hand.at(i).getSideB())
			{
				return true;
			}
		}
		return false;
	}
	return false;
}// End of isHandElligibleComputerTrain()

/* *********************************************************************
Function Name: playableTilesToComputerTrain()
Purpose: get the playable tiles vector to the passed computer train
Parameters:
			t_train, vector of tiles to compare our hand values to, passed by value
Return Value: vector<Tile> 
Algorithm:  use isTilePlayableToComputer and if so addTileTrain to our temp vector
			return our temp vector after looping through the values
Assistance Received: none
********************************************************************* */
vector<Tile> Player::playableTilesToComputerTrain(vector<Tile> t_train)
{
	vector<Tile> playable_tiles;
	playable_tiles.clear();
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (isTilePlayableToComputer(this->hand.at(i), t_train) == true)
		{
			addTileTrain(this->hand.at(i), playable_tiles);
		}
	}
	return playable_tiles;
}// End of playableTilesToComputerTrain()

/* *********************************************************************
Function Name: isTileInHand()
Purpose: determines if the tile passed is in the hand
Parameters:
			tile, tile to check our hand for, passed by value
Return Value: bool
Algorithm:  if the values of the passed tile match our hands tile at i
			return true, otherwise return false
Assistance Received: none
********************************************************************* */
bool Player::isTileInHand(Tile tile)
{
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (tile.getSideA() == this->hand.at(i).getSideA() && tile.getSideB() == this->hand.at(i).getSideB())
		{
			return true;
		}
	}
	return false;
}// End of isTileInHand()

/* *********************************************************************
Function Name: calculateTotalPips()
Purpose: calculate the total pips to update score at end of round
Parameters: none
Return Value: int
Algorithm:  loop through all our hands values and add up the pips to pipScore
Assistance Received: none
********************************************************************* */
int Player::calculateTotalPips()
{
	int pipScore = 0;
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		pipScore += this->hand.at(i).getSideA();
		pipScore += this->hand.at(i).getSideB();
	}

	return pipScore;
}// End of calculateTotalPips()

/* *********************************************************************
Function Name: addScore
Purpose: add the passed points to our member value of score
Parameters: 
			points, integer passed by value
Return Value: void
Algorithm: update our score variable
Assistance Received: none
********************************************************************* */
void Player::addScore(int points)
{
	this->score += points;
}// End of addScore()

/* *********************************************************************
Function Name: clearHand
Purpose: clear the hand vector
Parameters: none
Return Value: void
Algorithm: clear our hand vector
Assistance Received: none
********************************************************************* */
void Player::clearHand()
{
	this->hand.clear();
}// End of clearHand()

/* *********************************************************************
Function Name: clearTrain
Purpose: clear the train vector
Parameters: none
Return Value: void
Algorithm: clear our train vector
Assistance Received: none
********************************************************************* */
void Player::clearTrain()
{
	this->train.clear();
}// End of clearTrain()

/* *********************************************************************
Function Name: clearOrphan
Purpose: set the orphandouble member value to false
Parameters: none
Return Value: void
Algorithm: reset our orphanDouble value
Assistance Received: none
********************************************************************* */
void Player::clearOrphan() 
{
	this->orphanDouble = false;
}// End of clearOrphan()

/* *********************************************************************
Function Name: clearMarker
Purpose: set the marker member value to false
Parameters: none
Return Value: void
Algorithm: reset our marker value
Assistance Received: none
********************************************************************* */
void Player::clearMarker() 
{
	this->marker = false;
}// End of clearMarker()

/* *********************************************************************
Function Name: newRoundReset
Purpose: reset all the necessary values for new round
Parameters: none
Return Value: void
Algorithm: reset our hand, train, orphanDouble and marker
Assistance Received: none
********************************************************************* */
void Player::newRoundReset()
{
	clearHand();
	clearTrain();
	clearOrphan();
	clearMarker();
}// End of newRoundReset()
// End of file Player.cpp