//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
#include "Round.h"

/*
====================================================================
							  Round
====================================================================
*/

// Constructor of Round class
Round::Round()
{
	this->turn = "";
	this->roundNum = 1;
	this->boneyard.clear();
	this->mexican_train.clear();
	this->mexTrainOrphanDouble = false;
	this->gameEnd = false;

	setUpRound();
	determineFirstTurn();
	gameplayLoop();
}

// Constructor to create round from an existing save game using the passed values to initialize the game
Round::Round(string loadTurn, int numRounds, Human p1, Computer p2, vector<Tile> load_mexican_train, vector<Tile> load_boneyard)
{

	if (loadTurn == "Human" || loadTurn == "Computer")
	{
		this->turn = loadTurn;
	}
	else
	{
		this->turn = "Error";
	}

	if (numRounds > 0)
	{
		this->roundNum = numRounds;
	}
	else
	{
		this->roundNum = 1;
	}

	this->hum = p1;
	this->comp = p2;

	this->boneyard.clear();
	this->boneyard = load_boneyard;

	this->mexican_train.clear();
	this->mexican_train = load_mexican_train;

	// Incremental integer to make sure no more than 1 orphan double is in play
	int orphanCheck = 0;

	// Check for orphan doubles on the trains last values
	if (mexican_train.size() >= 1 && mexican_train.at(mexican_train.size() - 1).isDouble() == true)
	{
		// Set orphan double on mexican train
		this->mexTrainOrphanDouble = true;
		orphanCheck++;
	}
	if (this->hum.getTrain().size() >= 2 && this->hum.getTrain().at(this->hum.getTrain().size() - 1).isDouble() == true)
	{
		// Set orphan double on humans train
		this->hum.setOrphan(true);
		orphanCheck++;
	}
	if (this->comp.getTrain().size() >= 2 && this->comp.getTrain().at(0).isDouble() == true)
	{
		// Note: for computer the end value is actually the first in the vector
		// Set orphan double on computers train
		this->comp.setOrphan(true);
		orphanCheck++;
	}
	if (orphanCheck > 1)
	{
		cout << "Error creating game: more than one orphan double in play";
		exit(1);
	}

	// The engineVal will always be the start of the human train on load
	// so we can use it to set our engine up
	int engineVal = hum.getTrain().at(0).getSideA();
	this->engine.setTile(engineVal, engineVal);

	gameplayLoop();
}

// Destructor of Round class
Round::~Round()
{

}

/* *********************************************************************
Function Name: setUpRound
Purpose: set up a new round
Parameters: none
Return Value: void
Algorithm: sets up a new round in order
			1) engine is determined based on the number of rounds played
			2) tiles are shuffled
			3) deal 16 tiles to human
			4) deal 16 tiles to computer
			5) place remaining tiles in boneyard
			6) set human and computer train to start with the current engine
Assistance Received: none
********************************************************************* */
void Round::setUpRound()
{
	// The engine for the round is determined from the rounds played
	Tile currentEngine = getEngine();
	setEngine(currentEngine);
	removeEngineFromDeck(currentEngine);
	this->mexican_train.push_back(currentEngine);

	// The remaining tiles are shuffled
	this->roundDeck.shuffleDeck();
		
	// The human player is dealt 16 tiles 
	this->roundDeck.popNumTiles(this->hum.hand, 16);
		// this->hum.take16(this->roundDeck); !ALEC prob don't need this funciton

	// The computer player is dealt 16 tiles
	this->roundDeck.popNumTiles(this->comp.hand, 16);

	// The remaining tiles are placed in the boneyard
	this->roundDeck.popNumTiles(this->boneyard, roundDeck.double_nine_set.size());

	// Starts the human and computers personal trains off with the current engine
	this->hum.addTileTrain(currentEngine, this->hum.train);
	this->comp.addTileComputerTrain(currentEngine);
}// End of setUpRound()

/* *********************************************************************
Function Name: displayBoard
Purpose: output the board and game values to the user in a readable manner
Parameters: none
Return Value: void
Algorithm: print all relevant values to the player through the output
Assistance Received: none
********************************************************************* */
void Round::displayBoard()
{
	// Round number
	cout << "Round: " << this->roundNum << endl;
	cout << "Turn: " << this->turn << endl;
	// Print Computer Score, hand
	cout << "Computer: ";
	if (comp.getOrphan() == true)
	{
		cout << " Orphan Double!";
	}
	cout << "\n\tScore: " << this->comp.score << endl << endl;
	cout << "\tHand: ";
	this->comp.printHand();
	cout << endl << endl;

			cout << "\t\t";
	// Print first number of engine
	string engineNum = "";
	for (int i = 0; i < getMenuWidth(); i++)
	{
		engineNum += " ";
	}
	// convert int to character with + '0'
	// account for displacement of engine by computer train marker
	if (comp.getMarker() == true)
	{
		engineNum += "  ";
	}
	engineNum += this->engine.getSideA() + '0';
	cout << engineNum << endl;


	cout << "\t\t";
	// Print Computer Train on left, Engine in the middle, Human Train on Right
	this->comp.printM();
	this->comp.printTrain(this->engine);
	cout << "| ";
	this->hum.printTrain(this->engine);
	this->hum.printM();
	cout << endl;

			cout << "\t\t";
	// Print second number of engine
	cout << engineNum << endl << endl;

	// Print mexican train below the players personal trains
	cout << "Mexican Train: ";
	printMexicanTrain();

	if (mexTrainOrphanDouble == true)
	{
		cout << "\n\t\tOrphan Double!";
	}

	cout << endl << endl; 
	cout << "Boneyard: ";
	this->printBoneyard();

	// Print Human Hand
	cout << "\nHuman: ";
	if (hum.getOrphan() == true)
	{
		cout << " Orphan Double!";
	}
	cout << "\n\tScore: " << this->hum.score << endl << endl;
	cout << "\tHand: ";
	this->hum.printHand();
	cout << endl << endl;
}// End of displayBoard()

/* *********************************************************************
Function Name: gameplayLoop
Purpose: display, menu and changing of turns
Parameters: none
Return Value: void
Algorithm: 
			1) display the board
			2) display menu and get input
			3) change turn after menu
			4) determine if game is still in a playable state
			5) end game if its not, loop if it is
Assistance Received: none
********************************************************************* */
void Round::gameplayLoop()
{
	gameEnd = false;
	while (gameEnd == false)
	{
		displayBoard();
		menu();
		if (this->turn == "Computer")
		{
			changeTurn();
		}
		else if (this->turn == "Human")
		{
			changeTurn();
		}
		else
		{
			cout << "Error in gameplayLoop with determining turn";
			exit(1);
		}

		if (comp.getOrphan() == true && boneyard.size() == 0 && hum.playableTilesToComputerTrain(comp.getTrain()).size() == 0
			&& comp.playableTilesToComputerTrain(comp.getTrain()).size() == 0)
		{
			cout << "No one can play a tile and the boneyard has emptied, the round must end\n";
			gameEnd = true;
		}
		else if (hum.getOrphan() == true && boneyard.size() == 0 && hum.playableTilesToTrain(hum.getTrain()).size() == 0
			&& comp.playableTilesToTrain(hum.getTrain()).size() == 0)
		{
			cout << "No one can play a tile and the boneyard has emptied, the round must end\n";
			gameEnd = true;
		}
		else if (mexTrainOrphanDouble == true && boneyard.size() == 0 && hum.playableTilesToTrain(mexican_train).size() == 0
			&& comp.playableTilesToTrain(mexican_train).size() == 0)
		{
			cout << "No one can play a tile and the boneyard has emptied, the round must end\n";
			gameEnd = true;
		}
		else if(hum.playableTiles(mexican_train, comp).size() == 0 &&
			comp.playableTiles(mexican_train, comp, mexTrainOrphanDouble).size() == 0
			&& boneyard.size() == 0)
		{
			cout << "No one can play a tile and the boneyard has emptied, the round must end\n";
			gameEnd = true;
		}

		if (gameEnd == true)
		{
			
			hum.addScore(hum.calculateTotalPips());
			comp.addScore(comp.calculateTotalPips());

			cout << "=======================================================================================================================\n";
			cout << "\t\t\tThe round has ended\n";
			cout << "Computer has score of: ";
			cout << comp.getScore();
			cout << endl;
			cout << "Human has a score of: ";
			cout << hum.getScore();
			cout << endl;
			cout << "=======================================================================================================================\n";

			string temp = "";
			while (!(temp == "1" || temp == "2"))
			{
				cout << "Would you like to play another round? (1) yes (2) no: ";
				getline(cin, temp);
			}

			if (temp == "1")
			{
				// Create new round but increase the numRounds value and bring over the players scores
				resetRound();
			}
			else if (temp == "2")
			{
				// Display the winner of the game based on score
				if (comp.getScore() == hum.getScore())
				{
					cout << "=======================================================================================================================\n";
					cout << "\t\t\tThe game is a draw\n";
					cout << "\tComputer score: " << comp.getScore() << endl;
					cout << "\tHuman score: " << hum.getScore() << endl;
					cout << "=======================================================================================================================\n";
				}
				else if (comp.getScore() > hum.getScore())
				{
					cout << "=======================================================================================================================\n";
					cout << "\t\t\tYou win!\n";
					cout << "\tComputer score: " << comp.getScore() << endl;
					cout << "\tHuman score: " << hum.getScore() << endl;
					cout << "=======================================================================================================================\n";
				}
				else if (comp.getScore() < hum.getScore())
				{
					cout << "=======================================================================================================================\n";
					cout << "\t\t\Computer wins!\n";
					cout << "\tComputer score: " << comp.getScore() << endl;
					cout << "\tHuman score: " << hum.getScore() << endl;
					cout << "=======================================================================================================================\n";
				}

				exit(1);
			}
		}
	}
}// End of gameplayLoop()

/* *********************************************************************
Function Name: menu
Purpose: determine the users actions based on int userChoice
Parameters: none
Return Value: void
Algorithm: 
			1) output options to user
			2) get users input on the options
			3) act based on users choice
				1 is writeSave
				2 is playTurn
				3 is help
				4 is exit
Assistance Received: none
********************************************************************* */
// Menu function which sets off different functionalities based on the number from getMenuInput()
void Round::menu()
{

	cout << "1: Save the game\n";
	// says continue if computers turn rather than letting user make move
	if (this->turn == "Human") { cout << "2: Make a move\n"; }
	else { cout << "2: Continue\n"; }	
	cout << "3: Ask for help\n";
	cout << "4: Quit the game\n";

	int userChoice = getMenuInput();

	if (userChoice == 1)
	{
		// Save the game
		writeSave();
	}
	else if (userChoice == 2)
	{
		// Determine which players turn based on this->turn
		if (this->turn == "Human")
		{
			// Human plays
			this->hum.playTurn(this->mexican_train, this->boneyard, this->comp, this->mexTrainOrphanDouble, this->gameEnd);
		}
		else if (this->turn == "Computer")
		{
			// Computer plays
			this->comp.playTurn(this->mexican_train, this->boneyard, this->hum, this->mexTrainOrphanDouble, this->gameEnd);
		}
		else
		{
			cout << "Error in determining turn";
			exit(1);
		}

		// Pause to read what happened
		system("pause");
	}
	else if (userChoice == 3)
	{
		// Help functionality

		if (this->turn == "Computer")
		{
			cout << "Cannot help you, it is currently the computers turn :)\n";
			menu();
		}
		else 
		{
			this->hum.help(mexican_train, comp, mexTrainOrphanDouble);
			cout << endl;
			menu();
		}
	}
	else if (userChoice == 4)
	{
		// Exit the game
		exit(0);
	}
}// End of menu()

/* *********************************************************************
Function Name: getMenuInput
Purpose: get the users input for what menu value they want to select
Parameters: none
Return Value: int
Algorithm: 
			1) loop to validate input for numbers 1 - 4
			2) return when a valid value is input
Assistance Received: none
********************************************************************* */
int Round::getMenuInput()
{
	string temp = " ";		

	cout << "Please input a number for one of the given options: ";
	while (!(temp == "1" || temp == "2" || temp == "3" || temp == "4"))
	{
		getline(cin, temp);
	}

	int input = stoi(temp);
	return input;
}// End of getMenuInput()

/* *********************************************************************
Function Name: getMenuWidth
Purpose: get the width to push the engine values out to in display
Parameters: none
Return Value: int
Algorithm: use train size * 4 to determine the distance the engine numbers need to
			be from the left side of the output
Assistance Received: none
********************************************************************* */
// Get the width of the menu for lining up the engine in the output
// Since tiles are 3 characters followed by a space this helps line up the engine
int Round::getMenuWidth()
{	
	return (this->comp.getTrain().size() * 4) - 4;	
}// End of getMenuWidth()

/* *********************************************************************
Function Name: getEngine
Purpose: determines the engine based on round number
Parameters: none
Return Value: Tile
Algorithm: use roundNum % 10 to get a number 0-9 for the engine
			return a tile with the number obtained on both sides
Assistance Received: none
********************************************************************* */
// Determines the current engine from a double nine set
Tile Round::getEngine()
{
	int engineVal = -1;

	// Determine the last digit of the round number to get the current engine
	switch (this->roundNum % 10)
	{
	case 0: engineVal = 0;
		break;
	case 1: engineVal = 9;
		break;
	case 2: engineVal = 8;
		break;
	case 3: engineVal = 7;
		break;
	case 4: engineVal = 6;
		break;
	case 5: engineVal = 5;
		break;
	case 6: engineVal = 4;
		break;
	case 7: engineVal = 3;
		break;
	case 8: engineVal = 2;
		break;
	case 9: engineVal = 1;
		break;
	default: engineVal = -1;
		break;

	}

	// Set up the tile of the current engine engineVal-engineVal
	Tile engine(engineVal, engineVal);
	return engine;
}// End of getEngine()

/* *********************************************************************
Function Name: setEngine
Purpose: set the member engine to the passed tile
Parameters: eng, Tile to assign to engine
Return Value: void
Algorithm: check that eng is a double
			assign eng to engine
Assistance Received: none
********************************************************************* */
// Fuction to change the current engine to a new value (to be used mainly with loading saves)
void Round::setEngine(Tile eng)
{
	// Check for equivalent sides on the engine, then set engine
	if (eng.getSideA() == eng.getSideB())
	{
		this->engine = eng;
	}
}//End of setEngine()

/* *********************************************************************
Function Name: removeEngineFromDeck
Purpose: remove the engine tile passed from the deck
Parameters: eng, tile to search through the roundDeck and remove
Return Value: void
Algorithm: search through the roundDeck and remove the tile that matches
			eng in the deck
Assistance Received: none
********************************************************************* */
// Fucntion to remove the current engine from the deck so it is not in play
void Round::removeEngineFromDeck(Tile eng)
{
	for (int i = 0; i < roundDeck.DOUBLE_NINE_SIZE; i++)
	{
		int tempSideA = this->roundDeck.double_nine_set.at(i).getSideA();
		int tempSideB = this->roundDeck.double_nine_set.at(i).getSideB();

		// If condition for matching engine tile (i.e. Tile eng 0-0 and tempA and tempB are 0-0)
		if (tempSideA == eng.getSideA() && tempSideB == eng.getSideB())
		{
			// Remove the engine tiles matching tile from the roundDeck
			this->roundDeck.double_nine_set.erase(this->roundDeck.double_nine_set.begin() + i);
			break;
		}
	}
}// End of removeEngineFromDeck()

/* *********************************************************************
Function Name: determineFirstTurn
Purpose: determines which player gets to play first
Parameters: none
Return Value: void
Algorithm: if human score or computer score is lower, they play first
			otherwise they call the coin flip for first turn
Assistance Received: none
********************************************************************* */
void Round::determineFirstTurn()
{
	if (this->comp.score == this->hum.score)
	{
		// Flip a coin for first turn
		bool userCoin = getUsersCoin();
		bool flippedCoin = flipCoin(userCoin);
		printCoin(flippedCoin);

		if ( userCoin == flippedCoin )
		{
			this->turn = "Human";
		}
		else
		{
			this->turn = "Computer";
		}
	}
	else if (this->comp.score > this->hum.score)
	{
		// Human has lower score, goes first
		this->turn = "Human";
	}
	else if (this->comp.score < this->hum.score)
	{
		// Computer has lower score, goes first
		this->turn = "Computer";
	}
	else
	{
		cout << "ERROR in determineFirstTurn(): could not determine turn\n";
		exit(1);
	}

	printFirstTurn();
}// End of determineFirstTurn()

/* *********************************************************************
Function Name: getUsersCoin
Purpose: get the users coin value
Parameters: none
Return Value: bool
Algorithm: ask the user for a side of the coin, return 0 if they choose heads return
			1 if they choose tails
Assistance Received: none
********************************************************************* */
// Get users choice for the coin toss
bool Round::getUsersCoin()
{
	string input = "";
	do
	{
		cout << "Pick a side of the coin to flip, enter (H) for heads or (T) for tails: ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "h") { return 0; }
		if (input == "t") { return 1; }
	} while (true);	
	// Had to do the while condition like this due to bool issues with string comparison

	return 0;
}// End of getUsersCoin()

/* *********************************************************************
Function Name: flipCoin
Purpose: flips the coin returning 1 for tails or 0 for heads
Parameters: none
Return Value: void
Algorithm: seed random number generator, call rand(), if random is 1 set
			value of our coin face to tails, else if its 2 set it to 0
Assistance Received: http://www.cplusplus.com/forum/beginner/1304/
********************************************************************* */
// Flip the coin randomly, return 0 for heads, 1 for tails
bool Round::flipCoin(bool userVal)
{
	bool face = 0;
	int random = 0;
	srand(time(NULL));
	random = rand() % 2 + 1;
	if (random == 1)
	{	
		// value is tails
		face = 1; 
	}
	else if (random == 2)
	{
		// value is heads
		face = 0;
	}

	return face;
}// End of flipCoin()

/* *********************************************************************
Function Name: printMexicanTrain
Purpose: prints the mexican train to output
Parameters: none
Return Value: void
Algorithm: output all values of the mexican train except for the engine
Assistance Received: none
********************************************************************* */
// Prints the values of the local mexican train in round one by one
void Round::printMexicanTrain()
{
	for (unsigned int i = 0; i < this->mexican_train.size(); i++)
	{
		// Skip displaying the engine in the mexican train
		if ((mexican_train.at(i).getSideA() == this->engine.getSideA())
			&& (mexican_train.at(i).getSideB() == this->engine.getSideB()))
		{
			continue;
		}
		this->mexican_train.at(i).printTile();
		cout << " ";
	}
}

/* *********************************************************************
Function Name: printBoneyard
Purpose: prints the boneyard to output
Parameters: none
Return Value: void
Algorithm: output all values of the boneyard
Assistance Received: none
********************************************************************* */
// Prints the boneyard and the amount of tiles remaining if boneyard has values
void Round::printBoneyard()
{
	if (this->boneyard.size() > 0)
	{
		this->boneyard.at(0).printTile();
		cout << " (" << this->boneyard.size() << " tiles remaining)\n";
	}
}// End of printBoneyard()

/* *********************************************************************
Function Name: printCoin
Purpose: prints the value of a boolean we treat as a coin
Parameters: none
Return Value: void
Algorithm: output heads for 0, tails for 1
Assistance Received: none
********************************************************************* */
// Prints the boolean value of our "coin" as heads or tails
void Round::printCoin(bool coin)
{
	if (coin == 0)
	{
		cout << "Coin is heads\n";
	}
	else if (coin == 1)
	{
		cout << "Coin is tails\n";
	}
}// End of printCoin()

/* *********************************************************************
Function Name: printFirstTurn
Purpose: prints the first turn based on the Round member turn
Parameters: none
Return Value: void
Algorithm: output the first turn
Assistance Received: none
********************************************************************* */
// Prints which player goes first based on local turn value of round
void Round::printFirstTurn()
{
	cout << this->turn << " goes first\n";
}// End of printFirstTurn()

/* *********************************************************************
Function Name: writeSave
Purpose: writes a save file to the format of readSave
Parameters: none
Return Value: void
Algorithm: write all our values to sfile and save
Assistance Received: none
********************************************************************* */
// Writes a current round as a save game then exits
void Round::writeSave()
{
	vector<Tile> temp_tiles;

	ofstream sfile;
	string filename = writeSaveInput();
	sfile.open(filename);

	sfile << "Round: ";
	sfile << roundNum << endl << endl;

	sfile << "Computer: " << endl;
	sfile << "\tScore: ";
	sfile << this->comp.getScore();
	sfile << endl;

	sfile << "\tHand: ";
	temp_tiles.clear();
	temp_tiles = comp.getHand();
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	sfile << endl;
	
	sfile << "\tTrain: ";
	temp_tiles.clear();
	temp_tiles = comp.getTrain();
	// For computer marker goes on the end
	if (comp.getMarker() == true) {	sfile << "M "; } 
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	sfile << endl << endl;

	sfile << "Human: " << endl;
	sfile << "\tScore: ";
	sfile << this->hum.getScore();
	sfile << endl;

	sfile << "\tHand: ";
	temp_tiles.clear();
	temp_tiles = hum.getHand();
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	sfile << endl;

	sfile << "\tTrain: ";
	temp_tiles.clear();
	temp_tiles = hum.getTrain();
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	// For human marker goes on the end
	if (hum.getMarker() == true) { sfile << "M "; }	
	sfile << endl << endl;

	sfile << "Mexican Train: ";
	temp_tiles.clear();
	temp_tiles = this->mexican_train;
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	sfile << endl << endl;

	sfile << "Boneyard: ";
	temp_tiles.clear();
	temp_tiles = this->boneyard;
	for (unsigned int i = 0; i < temp_tiles.size(); i++)
	{
		string tempTile = temp_tiles.at(i).stringTile();
		sfile << temp_tiles.at(i).stringTile() + " ";
	}
	sfile << endl << endl;

	sfile << "Next Player: ";
	sfile << this->turn << endl;

	sfile.close();

	exit(0);
}// End of writeSave()

/* *********************************************************************
Function Name: writeSaveInput()
Purpose: gets the users input for what to name the save file
Parameters: none
Return Value: string
Algorithm: prompt user for input, validate that they entered something, then add .txt
Assistance Received: none
********************************************************************* */
string Round::writeSaveInput()
{
	string filename = "";
	while (filename == "")
	{
		cout << "Enter a name for the file, afterwards the program will close: ";
		cin >> filename;
	}
	filename += ".txt";

	return filename;
}// End of writeSaveInput()

/* *********************************************************************
Function Name: changeTurn()
Purpose: swap the users turn based on current turn
Parameters: none
Return Value: void
Algorithm: changes turn to human if computer, computer if human
Assistance Received: none
********************************************************************* */
void Round::changeTurn()
{
	if (this->turn == "Human")
	{
		this->turn = "Computer";
	}
	else if (this->turn == "Computer")
	{
		this->turn = "Human";
	}
	else
	{
		cout << "Error changing turn";
		exit(1);
	}
}// End of changeTurn()

/* *********************************************************************
Function Name: resetRound()
Purpose: setup a new round carrying over score and round number from last round
Parameters: none
Return Value: void
Algorithm: clear all values except for the users score and the round number
			start new gameplayLoop
Assistance Received: none
********************************************************************* */
void Round::resetRound()
{
	this->roundNum++;
	this->turn = "";
	this->boneyard.clear();
	this->mexican_train.clear();
	this->mexTrainOrphanDouble = false;
	this->gameEnd = false;

	this->hum.newRoundReset();
	this->comp.newRoundReset();

	setUpRound();
	determineFirstTurn();
	gameplayLoop();
}
// End of file Round.cpp