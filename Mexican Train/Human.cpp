//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
#include "Human.h"


/*
====================================================================
							 Human
====================================================================
*/

Human::Human()
{
}

Human::~Human()
{
}

/* *********************************************************************
Function Name: playTurn
Purpose: To let the user play through their turn following the games logic.
		 Activated via entering "2" in the menu 
Parameters:
			mexican_train<>, passed by reference. Has the tiles of the mexican_train
			yard<>, passed by reference. Has the tiles of the boneyard
			copmuter, passed by reference. Other player of the game, of class type Computer()
			mexOrphan, passed by reference. Boolean value to indicate mexican train has an orphan double
			gameEnd, passed by reference. Boolean value to flag whether or not the game needs to be ended
Return Value: void
Algorithm:
			1) Check playable tiles using isHandElligibleTrain(vector<Tiles> train)
				if none playable call function noPlayableTiles()
				if hand is playable to any elligible trains, check for orphan doubles 
					if orphan double is true and hand is not elligible to the train call noPlayableTiles()
					if orphan double is true and hand is elligible call playTile(pickTile(vector<Tile> train), trainChoice ...)
			2) Else call selectTrain() to have the user select an elligible train they can play on and they will 
			   then call playTile(pickTile(vector<Tile> train), trainChoice ...)
Assistance Received: none
********************************************************************* */
void Human::playTurn(vector<Tile>& mex_train, vector<Tile>& yard, Computer& computer, bool& mexOrphan, bool& gameEnd)
{
	// Prompt user for input on their choice of tile
	string temp = "";
	string temp2 = "";

	Tile userTile;

	// No playable tiles: If the player does not have a tile that can be played at the end of any eligible train
	if (isHandElligibleTrain(mex_train) == false && isHandElligibleTrain(this->train) == false && 
		(isHandElligibleComputerTrain(computer.getTrain()) == false || computer.getMarker() == false))
	{
		// If the boneyard is empty, the player passes their turn and puts a marker at the end of their personal train
		noPlayableTiles(mex_train, yard, computer, mexOrphan);
	}
	else if(isHandElligibleTrain(mex_train) == true || isHandElligibleTrain(this->train) == true || 
		(isHandElligibleComputerTrain(computer.getTrain()) == true && computer.getMarker() == true))
	{
		// Check orphan double case first as orphan double must be played upon rather than allowing selection
		if (this->getOrphan() == true)
		{
			cout << "There is an Orphan Double on your train, you can only play to that train \n";
			if (isHandElligibleTrain(this->train) == false)
			{
				cout << "No playable tiles to the Orphan Double\n";
				noPlayableTiles(mex_train, yard, computer, mexOrphan);
			}
			else
			{
				// Can play a value to the orphan double
				string trainChoice = "2";
				playTile(pickTile(this->train), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);
				this->setMarker(false);
				this->setOrphan(false);
			}
		}
		else if (computer.getOrphan() == true)
		{
			cout << "There is an Orphan Double on the Computer's train, you can only play to that train \n";
			if (isHandElligibleComputerTrain(computer.getTrain()) == false)
			{
				cout << "No playable tiles to the Orphan Double\n";
				noPlayableTiles(mex_train, yard, computer, mexOrphan);
			}
			else
			{
				// Play Tile Function to let user pick their tile to play onto the train
				string trainChoice = "3";
				playTile(pickTileComputerTrain(computer.getTrain()), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);

				computer.setOrphan(false);
			}
		}
		else if (mexOrphan == true)
		{
			cout << "There is an Orphan Double on the Mexican train, you can only play to that train \n";
			if (isHandElligibleTrain(mex_train) == false)
			{
				cout << "No playable tiles to the Orphan Double\n";
				noPlayableTiles(mex_train, yard, computer, mexOrphan);
			}
			else
			{
				// Play Tile Function to let user pick their tile to play onto the train
				string trainChoice = "1";
				playTile(pickTile(mex_train), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);

				mexOrphan = false;
			}
		}
		else
		{
			// Prompt user for the train choice they would like from elligible trains
			string trainChoice = selectTrain(mex_train, computer);

			// Based on the train now ask them which tile to play from their hand, can only work with given train
			if (trainChoice == "1")
			{
				playTile(pickTile(mex_train), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);
			}
			else if (trainChoice == "2")
			{
				playTile(pickTile(this->train), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);
			}
			else if (trainChoice == "3")
			{
				playTile(pickTileComputerTrain(computer.getTrain()), trainChoice, mex_train, yard, computer, mexOrphan, gameEnd);
			}
		}
	}
	else if ((computer.getOrphan() == true && isHandElligibleComputerTrain(computer.train) == false) 
		|| (mexOrphan == true && isHandElligibleTrain(mex_train) == false) 
		|| (this->getOrphan() == true && isHandElligibleTrain(this->train) == false))
	{
		// If you cannot play to the orphan double, call noPlayableTiles
		noPlayableTiles(mex_train, yard, computer, mexOrphan);
	}

}// End of playTurn()


/* *********************************************************************
Function Name: playTile
Purpose: play a tile following the rules of the game logic
Parameters:
			tile, tile object passed by value. Is the tile being played
			trainChoice, passed by value. String value of the train the user selected.
			mexican_train<>, passed by reference. Has the tiles of the mexican_train
			yard<>, passed by reference. Has the tiles of the boneyard
			copmuter, passed by reference. Is the other player of the game, of class type Computer()
			mexOrphan, passed by reference. Boolean value to indicate mexican train has an orphan double
			gameEnd, passed by reference. Boolean value to flag whether or not the game needs to be ended
Return Value: void
Algorithm:
			1) Check all possible ways the passed tile can be played to the train indicated
			2) Determine the outcome of the tile being played via the game logic
Assistance Received: none
********************************************************************* */
void Human::playTile(Tile tile, string trainChoice, vector<Tile>& mex_train, vector<Tile>& yard,Computer& computer, bool& mexOrphan, bool& gameEnd)
{
	vector<Tile> played_train;
	// boolean value to keep track of if we played a double already
	bool playedDouble = false;

	// Set the temp train played_train equal to the train the user is playing to
	switch (stoi(trainChoice))
	{
	case 1:
		played_train = mex_train;
		break;
	case 2:
		played_train = this->train;
		break;
	case 3:
		played_train = computer.getTrain();
		reverse(played_train.begin(), played_train.end());
		break;
	}

	// Play a non double tile at the end of the elligible train
	if (tile.isDouble() == false)
	{
		played_train.push_back(tile);
		removeTileHand(tile);

		cout << "Played non double tile ";
		tile.printTile();
		cout << endl;

		// Assign the values that have been changed on our temp played_train back to the original train
		switch (stoi(trainChoice))
		{
		case 1:
			mex_train = played_train;
			break;
		case 2:
			this->train = played_train;
			setMarker(false);
			break;
		case 3:
			computer.train = played_train;
			reverse(computer.train.begin(), computer.train.end());
			break;
		}
	}
	if (tile.isDouble() == true)
	{
		// Push the double tile onto the train and remove it from the hand
		played_train.push_back(tile);
		removeTileHand(tile);

		cout << "Played double tile ";
		tile.printTile();
		cout << endl;

		playedDouble = true;

		// Assign the values that have been changed on our temp played_train back to the original train
		switch (stoi(trainChoice))
		{
		case 1:
			mex_train = played_train;
			break;
		case 2:
			this->train = played_train;
			setMarker(false);
			break;
		case 3:
			computer.train = played_train;
			reverse(computer.train.begin(), computer.train.end());
			break;
		}
	}
	if (tile.isDouble() == true && this->hand.size() == 1 && twoPlayableDoubles(mex_train, computer.train) == true)
	{
		// Continues the output from if above for this case to print 2 tiles
		cout << "Also played tile ";
		this->hand.at(0).printTile();
		cout << " as the last tile, Game Over\n";

		// Play the 2nd playable double and end the game
		if (isTilePlayable(this->hand.at(0), mex_train) == true)
		{
			addTileTrain(this->hand.at(0), mex_train);
			removeTileHand(this->hand.at(0));
		}
		else if (isTilePlayable(this->hand.at(0), this->train) == true)
		{
			addTileTrain(this->hand.at(0), this->train);
			removeTileHand(this->hand.at(0));
			// always set marker to false after playing to human train
			this->setMarker(false);
		}
		else if (isTilePlayableToComputer(this->hand.at(0), computer.train) == true)
		{
			addTileComputerTrain(this->hand.at(0), computer);
			removeTileHand(this->hand.at(0));
		}
		gameEnd = true;
	}else if (tile.isDouble() == true && this->hand.size() == 0)
	{
		// if played double and hand is empty end game
		gameEnd = true;
		tile.printTile();
		cout << " was played as last tile, Game Over\n";
	}
	else if (tile.isDouble() == true && ((isHandElligibleComputerTrain(computer.train) == true && computer.getMarker() == true)
		|| isHandElligibleTrain(mex_train) == true || isHandElligibleTrain(this->train) == true))
	{
		// If any a double is played and the hand is elligible to any train			

		cout << "You have a non double follow up, select a train to play it to, if it's a different train to the double it will create an orphan double\n";
		string newSelection = selectTrain(mex_train, computer);
		if (newSelection == "1")
		{
			// Selection 1 is for mexican train
			Tile tempSwitchTile = pickTile(mex_train);
			addTileTrain(tempSwitchTile, mex_train);
			removeTileHand(tempSwitchTile);
			cout << "Played tile ";
			tempSwitchTile.printTile();
			cout << " to mexican train\n";

		}
		else if (newSelection == "2")
		{
			// Selection 2 is for human train
			Tile tempSwitchTile = pickTile(this->train);
			addTileTrain(tempSwitchTile, this->train);
			removeTileHand(tempSwitchTile);
			this->setMarker(false);
			cout << "Played tile ";
			tempSwitchTile.printTile();
			cout << " to your train\n";
		}
		else if (newSelection == "3")
		{
			// Selection 3 for computer train
			Tile tempSwitchTile = pickTileComputerTrain(computer.train);
			addTileComputerTrain(tempSwitchTile, computer);
			removeTileHand(tempSwitchTile);
			cout << "Played tile ";
			tempSwitchTile.printTile();
			cout << " to computer's train\n";
		}

		if (newSelection != trainChoice && trainChoice == "1")
		{
			// If it's not the same train set the Orphan value to true
			mexOrphan = true;
		}
		else if (newSelection != trainChoice && trainChoice == "2")
		{
			this->setOrphan(true);
		}
		else if (newSelection != trainChoice && trainChoice == "3")
		{
			computer.setOrphan(true);
		}

	}
	else if (playedDouble == false && tile.isDouble() == true && (isHandElligibleComputerTrain(computer.train) == false && isHandElligibleTrain(mex_train) == false && isHandElligibleTrain(this->train) == false))
	{
		// Use playedDouble to avoid drawing after a case where the double tile is played and reevaluates the hands after being
		// removed causing to draw when user is not supposed to since they did sucessfully play a tile
		// Follow procedure for no tiles
		noPlayableTiles(mex_train, yard, computer, mexOrphan);
	}
}// End of playTile()

/* *********************************************************************
Function Name: twoPlayableDoubles
Purpose: determine if a two playable doubles case is possible
Parameters:
			mex_train, mexican train vector passed by value
			computer_train, computer train vector passed by value
			
Return Value: boolean value for whether or not a two playable doubles case is possible
Algorithm:
			1) determine if the hand.at(0) is a tile playable to the any of the passed
				trains or the local train
						if so return true
						if not return false
Assistance Received: none
********************************************************************* */
// Checks if the last value of hand is playable double
bool Human::twoPlayableDoubles(vector<Tile> mex_train, vector<Tile> computer_train)
{
	if (this->hand.at(0).isDouble() == true)
	{
		// if Checks that there are two double tiles playable to 2 elligible trains
		if ((isTilePlayable(this->hand.at(0), mex_train) == true 
			|| isTilePlayableToComputer(this->hand.at(0), computer_train) == true 
			|| isTilePlayable(this->hand.at(0), this->train)))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	return false;
}// End of twoPlayableDoubles()

/* *********************************************************************
Function Name: help
Purpose: give the user their playable tiles to help them determine a move
Parameters:
			mex_train, mexican train vector, passed by value
			computer, computer train vector, passed by value
			mexOrphan, mexican orphan double state boolean, passed by value

Return Value: boolean value for whether or not a two playable doubles case is possible
Algorithm:
			1) Get a vector of playable tiles to use by calling playableTiles()
			2) if orphan double is true delete all unplayable values from our vector
			3) output the amount of remaining tiles in playable
Assistance Received: none
********************************************************************* */
void Human::help(vector<Tile> mex_train, Computer computer, bool mexOrphan)
{
	vector<Tile> playable = playableTiles(mex_train, computer);
	if (mexOrphan == true)
	{
		for (unsigned int i = 0; i < playable.size(); i++)
		{
			if (isTilePlayable(playable.at(i), mex_train) == false)
			{
				// erase elements that are not playable to the only playable train
				playable.erase(playable.begin() + i);
			}	
		}
	}
	else if (computer.getOrphan() == true)
	{
		for (unsigned int i = 0; i < playable.size(); i++)
		{
			if (isTilePlayableToComputer(playable.at(i), computer.train) == false)
			{
				// erase elements that are not playable to the only playable train
				playable.erase(playable.begin() + i);
			}
		}
	}
	else if (getOrphan() == true)
	{
		for (unsigned int i = 0; i < playable.size(); i++)
		{
			if (isTilePlayable(playable.at(i), this->train) == false)
			{
				// erase elements that are not playable to the only playable train
				playable.erase(playable.begin() + i);
			}
		}
	}

	if (playable.size() != 0)
	{
		cout << "Your playable tiles are: ";
		for (unsigned int i = 0; i < playable.size(); i++)
		{
			playable.at(i).printTile();
			cout << " ";
		}
	}
	else
	{
		cout << "You have no playable tiles";
	}
}// End of help()

/* *********************************************************************
Function Name: playableTiles
Purpose: determine if a two playable doubles case is possible
Parameters:
			mex_train, mexican train vector passed by value
			computer, computer class object passed by value

Return Value: a vector of the playable tiles in the players hand to the availible trains
Algorithm:
			1) check using isTilePlayable() to each train and if yes we add to the vector we are returning 
			2) if getMarker() is true on the computer we check its values as well as they are playable values
Assistance Received: none
********************************************************************* */
vector<Tile> Human::playableTiles(vector<Tile> mex_train, Computer computer)
{
	vector<Tile> playable_tiles;
	playable_tiles.clear();
	for (unsigned int i = 0; i < this->hand.size(); i++)
	{
		if (computer.getMarker() == false)
		{
			if (isTilePlayable(this->hand.at(i), mex_train) == true ||
				isTilePlayable(this->hand.at(i), this->train) == true)
			{
				addTileTrain(this->hand.at(i), playable_tiles);
			}
		}
		else
		{
			if (isTilePlayable(this->hand.at(i), mex_train) == true ||
				isTilePlayable(this->hand.at(i), this->train) == true ||
				isTilePlayableToComputer(this->hand.at(i), computer.train) == true)
			{
				addTileTrain(this->hand.at(i), playable_tiles);
			}
		}
	}
	return playable_tiles;
}// End of playableTiles()

/* *********************************************************************
Function Name: selectTrain
Purpose: determines which train the user can play to and asks their selection
Parameters:
			mex_train, mexican train vector passed by value
			computer, computer class object passed by value

Return Value: a string of "1" mexican train "2" personal train or "3" computer train
Algorithm:
			1) check if hands are elligible to the trains and set booleans for if playable to true or false
			2) prompt user for input based on the value of the playable booleans
			3) validate inputs at every cin and return the string
Assistance Received: none
********************************************************************* */
// Has user select the train to play to
string Human::selectTrain(vector<Tile> mex_train, Computer computer)
{
	bool mexPlayable = false;
	bool humanPlayable = false;
	bool computerPlayable = false;

	cout << "Select a train to play on";
	// If a train is elligible ask the user the card they would like to play and onto which train
	if (isHandElligibleTrain(mex_train) == true)
	{
		cout << " (1) Mexican Train";
		mexPlayable = true;
	}
	if (isHandElligibleTrain(this->train) == true)
	{
		cout << " (2) Your Train";
		humanPlayable = true;
	}
	if ((isHandElligibleComputerTrain(computer.getTrain()) == true) && computer.getMarker() == true)
	{
		cout << " (3) Computers Train";
		computerPlayable = true;
	}
	cout << ": ";

	string temp = "";
	if (mexPlayable == true && humanPlayable == true && computerPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "1" || temp == "2" || temp == "3"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (mexPlayable == true && humanPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "1" || temp == "2"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (mexPlayable == true && computerPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "1" || temp == "3"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (humanPlayable == true && computerPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "2" || temp == "3"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (mexPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "1"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (humanPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "2"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}
	else if (computerPlayable == true)
	{
		getline(cin, temp);
		while (!(temp == "3"))
		{
			cout << "Please enter a one of the stated values: ";
			getline(cin, temp);
		}
	}

	return temp;
}// End of selectTrain()

/* *********************************************************************
Function Name: pickTileComputerTrain
Purpose: pick a tile from the member hand to play to the computer train
Parameters:
			computer_train, computer train passed by value

Return Value: a legal playable tile to be played onto the computers train
Algorithm:
			1) prompt user for input on tile they want to play
			2) if tile is in hand and it is playable to the computer train
					use flipTileForComputerTrain() and return tile
Assistance Received: none
********************************************************************* */
Tile Human::pickTileComputerTrain(vector<Tile> computer_train)
{
	if (computer_train.size() == 0)
	{
		cout << "Error at pickTileComputerTrain\n";
		exit(1);
	}

	string temp = "";
	// Don't start loop with no values in the users hand, should not even get here in that case but
	// check just in case it somehow gets through with no hand values
	while (true && this->hand.size() != 0)
	{
		cout << "Enter a tile from your hand you would like to play to the train: ";
		getline(cin, temp);
		Tile tempTile;
		// Don't attempt to access string out of range
		if (temp.length() >= 3)
		{
			int tempA = temp[0];
			int tempB = temp[2];
			tempTile.setTile(tempA - 48, tempB - 48);
		}
		// If tile is in hand and one of its ends matches the end of the train, we play the tile
		if (isTileInHand(tempTile) == true && (computer_train.front().getSideA() == tempTile.sideA || computer_train.front().getSideA() == tempTile.sideB))
		{
			flipTileForComputerTrain(tempTile, computer_train);
			return tempTile;
		}
		else if (isTileInHand(tempTile) == false)
		{
			continue;
		}
		else
		{
			cout << "Tile must be playable\n";
		}
	}
	cout << "No values in hand?\n";
	return Tile(0, 0);
}// End of pickTileComputerTrain()



/* *********************************************************************
Function Name: pickTile
Purpose: pick a tile from the member hand to play to the passed train
Parameters:
			passed_train, train passed by value

Return Value: a legal playable tile to be played onto the passed train
Algorithm:
			1) prompt user for input on tile they want to play
			2) if tile is in hand and it is playable to the passed train
					use flipTileForTrain() and return tile
Assistance Received: none
********************************************************************* */
Tile Human::pickTile(vector<Tile> passed_train)
{
	if (passed_train.size() > 0)
	{
		string temp = "";
		// Don't start loop with no values in the users hand, should not even get here in that case but
		// check just in case it somehow gets through with no hand values
		while (true && this->hand.size() != 0)
		{
			cout << "Enter a tile from your hand you would like to play to the train: ";
			getline(cin, temp);
			Tile tempTile;
			// Don't attempt to access string out of range
			if (temp.length() >= 3)
			{
				int tempA = temp[0];
				int tempB = temp[2];
				tempTile.setTile(tempA - 48, tempB - 48);
			}
			// If tile is in hand and one of its ends matches the end of the train, we play the tile
			if (isTileInHand(tempTile) == true && (passed_train.back().getSideB() == tempTile.sideA || passed_train.back().getSideB() == tempTile.sideB))
			{
				flipTileForTrain(tempTile, passed_train);
				return tempTile;
			}
			else if (isTileInHand(tempTile) == false)
			{
				continue;
			}
			else
			{
				cout << "Tile must be playable\n";
			}
		}
		cout << "No values in hand?\n";
		return Tile(0, 0);
	}
	else
	{
		cout << "Error in Class Human pickTile\n";
		exit(1);
	}

}// End of pickTile()


/* *********************************************************************
Function Name: noPlayableTiles
Purpose: case for when the user is unable to pick any tiles, determines the outcome of their turn
Parameters:
			mex_train, vector for mexican train passed by reference
			yard, vector for boneyard passed by reference
			computer, Computer player object passed by reference
			mexOrphan, boolean value for determining mexican train orphan double status passed by reference

Return Value: void
Algorithm:
			1) draw a tile depending on the size of the boneyard
			2) attempt to play to orphan double if it exists
				if it doesn't exist check playable trains for the tile drawn and select train
			3) if tile is unplayable mark train keep tile in hand
Assistance Received: none
********************************************************************* */
// Case for when we have determined the player has no playable tiles
void Human::noPlayableTiles(vector<Tile>& mex_train, vector<Tile>& yard, Computer& computer, bool& mexOrphan)
{
	// If the boneyard is empty, the player passes their turn and puts a marker at the end of their personal train
	if (yard.size() == 0)
	{
		setMarker(true);
		return;
	}
	else
	{
		bool mexPlayable = false;
		bool computerPlayable = false;
		bool humanPlayable = false;

		// If the boneyard is not empty, the player draws a tile from the boneyard and plays it immediately.
		this->hand.push_back(yard.front());
		yard.erase(yard.begin() + 0);
		
		cout << "Drew tile ";
		this->hand.back().printTile();
		cout << " from the boneyard\n";

		if (isTilePlayableToComputer(this->hand.back(), computer.getTrain()) == true && computer.getMarker() == true) { computerPlayable = true; }
		if (isTilePlayable(this->hand.back(), mex_train) == true) { mexPlayable = true; }
		if (isTilePlayable(this->hand.back(), this->train) == true) { humanPlayable = true; }

		// If orphan double, check only that condition as it takes full priority to the players available actions
		if (computer.getOrphan() == true)
		{
			if (computerPlayable == true)
			{
				// Flip tile/ Check if need to flip
				flipTileForComputerTrain(this->hand.back(), computer.getTrain());
				// Play tile immediately to computers train
				addTileComputerTrain(this->hand.back(), computer);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to the orphan double\n";
				// Remove tile from hand
				this->hand.pop_back();
				// Change status of computers orphan double
				computer.setOrphan(false);

				return;
			}
			else
			{
				// Player must add card to their hand pass turn and mark their train
				// note: card already added to hand above
				setMarker(true);
				cout << "Could not play tile ";
				hand.back().printTile();
				cout << " from the boneyard. It is now in your hand.\n";
				return;
			}
		}
		// Check this trains orphan double case
		if (this->getOrphan() == true)
		{
			if (humanPlayable == true)
			{
				// Flip tile for this train
				flipTileForTrain(this->hand.back(), this->train);
				// Play tile immediately to this train
				addTileTrain(this->hand.back(), this->train);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to the orphan double\n";
				// Remove tile from hand
				this->hand.pop_back();

				this->setOrphan(false);

				// When playing to personal train always set marker to false as playing to personal train removes markers
				this->setMarker(false);
				return;
			}
			else
			{
				// Player must add card to their hand pass turn and mark their train
				// note: card already added to hand above
				setMarker(true);
				cout << "Could not play tile ";
				hand.back().printTile();
				cout << " from the boneyard. It is now in your hand.\n";
				return;
			}
		}
		if (mexOrphan == true)
		{
			if (mexPlayable == true)
			{
				// Flip tile for mexican train
				flipTileForTrain(this->hand.back(), mex_train);
				// Play tile immediately to this train
				addTileTrain(this->hand.back(), mex_train);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to the orphan double\n";
				// Remove tile from hand
				this->hand.pop_back();
				// Set the played trains orphan to false
				mexOrphan = false;

				return;
			}
			else
			{
				// Player must add card to their hand pass turn and mark their train
				// note: card already added to hand above
				setMarker(true);
				cout << "Could not play tile ";
				hand.back().printTile();
				cout << " from the boneyard. It is now in your hand.\n";
				return;
			}
		}
		else if (computerPlayable == true || humanPlayable == true || mexPlayable == true)
		{
			// let user pick train to play it onto via select train method
			cout << "Select a train to play on";
			// If a train is elligible ask the user the card they would like to play and onto which train
			if (isTilePlayable(this->hand.back(), mex_train) == true)
			{
				cout << " (1) Mexican Train";
			}
			if (isTilePlayable(this->hand.back(), this->train) == true)
			{
				cout << " (2) Your Train";
			}
			if (isTilePlayableToComputer(this->hand.back(), computer.getTrain()) == true && computer.getMarker() == true)
			{
				cout << " (3) Computers Train";
			}
			cout << ": ";

			string temp = "";
			if (mexPlayable == true && humanPlayable == true && computerPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "1" || temp == "2" || temp == "3"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (mexPlayable == true && humanPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "1" || temp == "2"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (mexPlayable == true && computerPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "1" || temp == "3"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (humanPlayable == true && computerPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "2" || temp == "3"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (mexPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "1"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (humanPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "2"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}
			else if (computerPlayable == true)
			{
				getline(cin, temp);
				while (!(temp == "3"))
				{
					cout << "Please enter a one of the stated values: ";
					getline(cin, temp);
				}
			}

			if (temp == "1")
			{
				// Flip tile for mexican train
				flipTileForTrain(this->hand.back(), mex_train);
				// Play tile immediately to this train
				addTileTrain(this->hand.back(), mex_train);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to the mexican train\n";
				// Remove tile from hand
				this->hand.pop_back();
				// Set the played trains orphan to false
				mexOrphan = false;

				return;
			}
			else if(temp == "2")
			{
				// Flip tile for this train
				flipTileForTrain(this->hand.back(), this->train);
				// Play tile immediately to this train
				addTileTrain(this->hand.back(), this->train);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to your train\n";
				// Remove tile from hand
				this->hand.pop_back();

				this->setOrphan(false);

				// When playing to personal train always set marker to false as playing to personal train removes markers
				this->setMarker(false);
				return;
			}
			else if (temp == "3")
			{
				// Flip tile/ Check if need to flip
				flipTileForComputerTrain(this->hand.back(), computer.getTrain());
				// Play tile immediately to computers train
				addTileComputerTrain(this->hand.back(), computer);
				// Let player know what happened
				cout << "Played tile ";
				this->hand.back().printTile();
				cout << " from boneyard to the computer's train\n";
				// Remove tile from hand
				this->hand.pop_back();
				// Change status of computers orphan double
				computer.setOrphan(false);

				return;
			}
		}
		else
		{
			cout << "Could not play tile ";
			hand.back().printTile();
			cout << " from the boneyard. It is now in your hand.\n";
			setMarker(true);
		}
	}
}// End of noPlayableTiles()
// End of file Human.cpp