//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
#include "Game.h"

/*
====================================================================
							  Game
====================================================================
*/

// Constructor of Game class
Game::Game()
{
	loadOrRound();
}

// Destructor of Game class
Game::~Game()
{
}

/* *********************************************************************
Function Name: loadOrRound
Purpose: to let the user load a save or start a new round
Parameters: none
Return Value: void
Algorithm:
			1) ask user to load game or start round
			2) create round based on their input
Assistance Received: none
********************************************************************* */
void Game::loadOrRound()
{
	cout << "Would you like to load a save or start a new round? \n";
	string input = "";
	do
	{
		cout << "Enter (1) to load game (2) to create new round: ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "1") { break; }
		if (input == "2") { break; }
	} while (true);	
	// Had to do the while condition like this due to bool issues with string comparison
	if (input == "1"){	Round gameRound = readSave(); }
	else if (input == "2"){	 Round singleRound; }
}// End of loadOrRound()


/* *********************************************************************
Function Name: readSaveInput
Purpose: get the users input for the name of the save file to load
Parameters: none
Return Value: string for file name
Algorithm:
			1) ask user the name of the file
			2) write the name of the file to file
			3) add .txt to the end of the string
Assistance Received: none
********************************************************************* */
string Game::readSaveInput()
{
	string file;
	do
	{
		cout << "Enter the name of the file you would like to read: ";
		cin >> file;
	} while (file == "");

	file += ".txt";
	return file;
}// End of readSaveInput()

/* *********************************************************************
Function Name: readSave
Purpose: lets the user load a savegame into a round
Parameters: none
Return Value: Round object
Algorithm:
			1) call readSaveInput() to get the filename we need to load
			2) go through line by line and assign values to temporary vectors
			3) read through the lines until the semicolons while assigning the values
			4) at the end we initialize all the temporary values into our actual members and objects
				that we will use for a round
Assistance Received: none
********************************************************************* */
Round Game::readSave()
{
	int i = 0, roundNum = 0;
	string temp = "", temp2 = "", line = "", turn = "";
	Computer computer;
	Human human;

	vector<Tile> mexican_train;
	vector<Tile> boneyard;
	vector<Tile> computer_hand;
	vector<Tile> computer_train;
	vector<Tile> human_hand;
	vector<Tile> human_train;

	// Default constructor value sets to 0-0
	Tile tempTile;	

	// Prompt for user input on save name
	string filename = readSaveInput();
	ifstream sfile(filename);

	if (sfile.is_open())
	{
		while (getline(sfile, line))
		{
			// Condition for if line is empty, don't increase i to keep
			// the switch logic in check for next fetched line
			if (line == "")
			{
				continue;
			}
			else
			{
				switch (i)
				{
				// Round number
				case 0:	
					for (int z = line.length(); z > 5; z--)
					{
						// Reads if no space is with the first character read
						if (z == line.length() && line[z] != ' ')
						{
							temp = line[z];
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
							continue;
						}
						if (line[z] == ':') { break; }
						// Gathers string between 2 space characters
						if (line[z] == ' ')
						{
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
						}
					}
					// Set the round number to the integer value of temp string (convert string to int)
					roundNum = stoi(temp);
					temp = "";
					break;
				// Computer
				case 1:	
					break;
				// C Score
				case 2:
					for (int z = line.length(); z > 6; z--)
					{
						// reads if no space is with the first character read
						if (z == line.length() && line[z] != ' ')
						{
							temp = line[z];
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
							continue;
						}
						if (line[z] == ':') { break; }
						// gathers string between 2 space characters
						if (line[z] == ' ')
						{
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
						}
					}
					// Write score to a computer player
					computer.setScore(stoi(temp));
					temp = "";

					break;
				// C Hand
				case 3:
					// Loops until z is == to the start of the line, "Hand:"
					for (int z = line.length(); z > 5; z--)
					{
						// If we hit the : we know thats the end of the relevant data in the file
						if (line[z] == ':') { break; }

						// If we hit a '-' in the line, get the values on each side as a tile and push to hand
						if (line[z] == '-')
						{
							// Would have done this in 1 line but the compiler did not like that so I had to set
							// temp variables to use string to int here
							temp = line[z - 1];
							temp2 = line[z + 1];

							tempTile.setTile(stoi(temp), stoi(temp2));
							computer_hand.push_back(tempTile);

							temp = "";
							temp2 = "";
						}
					}

					break;
				// C Train
				case 4:
					for (int z = line.length(); z > 6; z--)
					{
						if (line[z] == 'M')
						{
							computer.setMarker(true);
						}
						else
						{
							// If we hit the : we know thats the end of the relevant data in the file
							if (line[z] == ':') { break; }

							// If we hit a '-' in the line, get the values on each side as a tile and push to hand
							if (line[z] == '-')
							{
								// Would have done this in 1 line but the compiler did not like that so I had to set
								// temp variables to use string to int here
								temp = line[z - 1];
								temp2 = line[z + 1];

								tempTile.setTile(stoi(temp), stoi(temp2));
								computer_train.push_back(tempTile);

								temp = "";
								temp2 = "";
							}
						}
					}
					break;
				// Human
				case 5:	
					break;
				// H Score
				case 6:
					for (int z = line.length(); z > 6; z--)
					{
						// reads if no space is with the first character read
						if (z == line.length() && line[z] != ' ')
						{
							temp = line[z];
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
							continue;
						}
						if (line[z] == ':') { break; }
						// gathers string between 2 space characters
						if (line[z] == ' ')
						{
							int r = 1;
							while (line[z - r] != ' ' && line[z - r] != ':')
							{
								temp = line[z - r] + temp;
								r++;
							}
						}
					}
					// Write score to a human player
					human.setScore(stoi(temp));
					temp = "";

					break;
				// H Hand
	   			case 7:	
					// Loops until z is == to the start of the line, "Hand:"
					for (int z = line.length(); z > 5; z--)
					{
						// If we hit the : we know thats the end of the relevant data in the file
						if (line[z] == ':') { break; }

						// If we hit a '-' in the line, get the values on each side as a tile and push to hand
						if (line[z] == '-')
						{
							// Would have done this in 1 line but the compiler did not like that so I had to set
							// temp variables to use string to int here
							temp = line[z - 1];
							temp2 = line[z + 1];

							tempTile.setTile(stoi(temp), stoi(temp2));
							human_hand.push_back(tempTile);

							temp = "";
							temp2 = "";
						}
					}
					break;
				// H Train
				case 8:	
					for (int z = line.length(); z > 6; z--)
					{
						if (line[z] == 'M')
						{
							human.setMarker(true);
						}
						else
						{
							// If we hit the : we know thats the end of the relevant data in the file
							if (line[z] == ':') { break; }

							// If we hit a '-' in the line, get the values on each side as a tile and push to hand
							if (line[z] == '-')
							{
								// Would have done this in 1 line but the compiler did not like that so I had to set
								// temp variables to use string to int here
								temp = line[z - 1];
								temp2 = line[z + 1];

								tempTile.setTile(stoi(temp), stoi(temp2));
								human_train.push_back(tempTile);

								temp = "";
								temp2 = "";
							}
						}
					}
					break;
				// Mexican Train
				case 9:	
					for (int z = line.length(); z > 14; z--)
					{
						// If we hit the : we know thats the end of the relevant data in the file
						if (line[z] == ':') { break; }

						// If we hit a '-' in the line, get the values on each side as a tile and push to hand
						if (line[z] == '-')
						{
							// Would have done this in 1 line but the compiler did not like that so I had to set
							// temp variables to use string to int here
							temp = line[z - 1];
							temp2 = line[z + 1];

							tempTile.setTile(stoi(temp), stoi(temp2));
							mexican_train.push_back(tempTile);

							temp = "";
							temp2 = "";
						}
					}
					break;
				// Boneyard
				case 10:
					for (int z = line.length(); z > 9; z--)
					{
						// If we hit the : we know thats the end of the relevant data in the file
						if (line[z] == ':') { break; }

						// If we hit a '-' in the line, get the values on each side as a tile and push to hand
						if (line[z] == '-')
						{
							// Would have done this in 1 line but the compiler did not like that so I had to set
							// temp variables to use string to int here
							temp = line[z - 1];
							temp2 = line[z + 1];

							tempTile.setTile(stoi(temp), stoi(temp2));
							boneyard.push_back(tempTile);

							temp = "";
							temp2 = "";
						}
					}
					break;
				// Next player
				case 11:
					if (line[13] == 'C')
					{
						turn = "Computer";
					}
					else if (line[13] == 'H')
					{
						turn = "Human";
					}
					break;
				default:
					break;
				}
			}
			i++;
		}
	}
	else
	{
		cout << "File could not open";
		exit(0);
	}

	// Flip the values of all vectors to have beginning and end swapped 
	// (note: they are read from file in the wrong order)
	reverse(mexican_train.begin(), mexican_train.end());
	reverse(human_hand.begin(), human_hand.end());
	reverse(computer_hand.begin(), computer_hand.end());
	reverse(human_train.begin(), human_train.end());
	reverse(computer_train.begin(), computer_train.end());
	reverse(boneyard.begin(), boneyard.end());

	human.setHand(human_hand);
	human.setTrain(human_train);
	computer.setHand(computer_hand);
	computer.setTrain(computer_train);	

	// Return a round created with the values we loaded
	return Round(turn, roundNum, human, computer, mexican_train, boneyard);

}// End of readSave()
// End of file Game.cpp
