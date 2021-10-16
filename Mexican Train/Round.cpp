// Alec Rizzo - arizzo3@ramapo.edu

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

	setUpRound();
	determineFirstTurn();
	gameplayLoop();
}

// !ALEC - need to make human and computer work with serialization here. 
// |-> function to create human and computer from save, then use this
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

	// The engineVal will always be the start of the human train
	int engineVal = hum.getTrain().at(0).getSideA();
	this->engine.setTile(engineVal, engineVal);

	gameplayLoop();
}


// Destructor of Round class
Round::~Round()
{

}


// Set up the board for a new round
void Round::setUpRound()
{
	// The engine for the round is determined from the rounds played
	Tile currentEngine = getEngine();
	setEngine(currentEngine);
	removeEngineFromDeck(currentEngine);

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
	this->hum.addTileTrain(currentEngine);
	this->comp.addTileTrain(currentEngine);
}

// Display the current state of the gameboard
void Round::displayBoard()
{
	// Round number
	cout << "Round: " << this->roundNum << endl;
	cout << "Turn: " << this->turn << endl;
	// Print Computer Score, hand
	cout << "Computer:\n\tScore: " << this->comp.score << endl;
	cout << "\tHand: ";
	this->comp.printHand();
	cout << endl << endl;

	cout << "\t\t";
	// Print first number of engine
	string engineNum = "";
	for (unsigned int i = 0; i < getMenuWidth(); i++)
	{
		engineNum += " ";
	}
	// convert int to character with + '0'
	engineNum += this->engine.getSideA() + '0';
	cout << engineNum << endl;

	cout << "\t\t";
	// Print Computer Train on left, Engine in the middle, Human Train on Right
	this->comp.printTrain(this->engine);
	cout << "| ";
	this->hum.printTrain(this->engine);
	cout << endl;

	cout << "\t\t";
	// Print second number of engine
	cout << engineNum << endl << endl;

	// Print mexican train below the players personal trains
	cout << "Mexican Train: ";
	printMexicanTrain();

	cout << endl << endl; 
	cout << "Boneyard: ";
	this->printBoneyard();

	// Print Human Hand
	cout << "Human:\n\tScore: " << this->hum.score << endl;
	cout << "\tHand: ";
	this->hum.printHand();
	cout << endl << endl;
}

// Gameplay loop for round
void Round::gameplayLoop()
{
	displayBoard();
	menu();
}

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
		// Either allow user to play turn or continue computers turn based on this->turn
	}
	else if (userChoice == 3)
	{
		// Help functionality
	}
	else if (userChoice == 4)
	{
		// Exit the game
		exit(0);
	}
}

// Get user input for the menu options
int Round::getMenuInput()
{
	string temp = " ";
	// Needed to "flush" cin buffer because cout was printing twice
	// https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
																   
	while (!(temp == "1" || temp == "2" || temp == "3" || temp == "4"))
	{
		cout << "Please input a number for one of the given options: ";
		getline(cin, temp);
	}


	int input = stoi(temp);
	return input;
}

// Get the width of the menu for lining up the engine in the output
// Since tiles are 3 characters followed by a space this helps line up the engine
int Round::getMenuWidth()
{	
	return (this->comp.getTrain().size() * 4) - 4;	
}

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
}

// Fuction to change the current engine to a new value (to be used mainly with loading saves)
void Round::setEngine(Tile eng)
{
	// Check for equivalent sides on the engine, then set engine
	if (eng.getSideA() == eng.getSideB())
	{
		this->engine = eng;
	}
}

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
}

// Determines which player gets to play first
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
		//exit(1);
	}

	printFirstTurn();
}

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
}

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
}

void Round::printMexicanTrain()
{
	for (unsigned int i = 0; i < this->mexican_train.size(); i++)
	{
		this->mexican_train.at(i).printTile();
		cout << " ";
	}
}

void Round::printBoneyard()
{
	this->boneyard.at(0).printTile();
	cout << " (" << this->boneyard.size() << " tiles remaining)\n";
}

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
}

void Round::printFirstTurn()
{
	cout << this->turn << " goes first\n";
}

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
	
	// !ALEC - make sure this works once gameplay is implemented fully
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

	// !ALEC - make sure this works once gameplay is implemented fully
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

	// !ALEC - close game here
	exit(0);
}

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
}


// End of file Round.cpp