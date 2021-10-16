// Alec Rizzo - arizzo3@ramapo.edu
#include "rules.h"

/*
====================================================================
							  Rules
====================================================================
*/
// Print function to allow player to choose if they want to see the rules
// Intended to be used at the start of the program
void printRules()
{
	// rulechoice is string to use getline to avoid cin getting repeat values on input (i.e. 32 == 2 after first loop)
	string rulechoice = " ";
	cout << "Welcome to the game Mexican Train, would you like to see the rules?\n";
	while (!(rulechoice == "1" || rulechoice == "2"))
	{
		cout << "(1) Yes - (2) No \n";
		cout << "Select an option: ";
		getline(cin, rulechoice);
	}

	if (rulechoice == "1")
	{
		cout << "========================================================================================================================\n";
		cout << "Basics:\n\t Mexican Train is a domino game played by 2 players (one being you, the player, the other being the computer) \n";
		cout <<		"\t in which the main objective is to score the fewest points after all the rounds\n\n";
				
		cout << "Setup:\n\t The game uses one double-nine set. A double-nine set contains 55 tiles. Each tile has two ends, each\n";
		cout <<		"\t end containing 0-9 pips. A double-nine set contains tiles with the following combination of pips:\n\n";

		cout <<		"\t 0-0, 0-1, 0-2, 0-3, 0-4, 0-5, 0-6, 0-7, 0-8, 0-9,\n";
		cout <<		"\t 1-1, 1-2, 1-3, 1-4, 1-5, 1-6, 1-7, 1-8, 1-9,\n";
		cout <<		"\t 2-2, 2-3, 2-4, 2-5, 2-6, 2-7, 2-8, 2-9,\n";
		cout <<		"\t 3-3, 3-4, 3-5, 3-6, 3-7, 3-8, 3-9,\n";
		cout <<		"\t 4-4, 4-5, 4-6, 4-7, 4-8, 4-9,\n";
		cout <<		"\t 5-5, 5-6, 5-7, 5-8, 5-9,\n";
		cout <<		"\t 6-6, 6-7, 6-8, 6-9,\n";
		cout <<		"\t 7-7, 7-8, 7-9,\n";
		cout <<		"\t 8-8, 8-9,\n";

		cout <<		"\t 9-9\n\n";

		cout <<		"\t In the first round of the game, 9-9 is the engine or starting tile. In the next round, 8-8 is the starting \n";
		cout <<		"\t tile and so on till 0-0 for the 10th round and back to 9-9 for the eleventh round.Once the engine for a \n";
		cout <<		"\t round is placed on the Table, the rest of the dominoes are shuffled before being dealt to the players.\n\n";

		cout <<	"Table:\n\t The engine for the round will be top to bottom with the players train on the right and the computers \n";
		cout <<		"\t on the left. e.g., in the following snapshot of the first round when 9-9 is the engine, the human \n";
		cout <<		"\t has played 9-5 and the computer has played 3-9:\n\n";

		cout <<			"\t\t9\n";
		cout <<	  "\t    3-9 | 9-5\n";
		cout <<			"\t\t9\n\n";

		cout <<		"\tThe Boneyard which is the remainder of shuffled tiles after having been dealt, will be left on the table.\n\n";

		cout << "A Round:\n\t A round starts in the following order:\n\n";
		cout <<		"\t First: the engine is placed on the Table.\n";
		cout <<		"\t Second: the remaining tiles are shuffled.\n";
		cout <<		"\t Third: the human player is dealt 16 tiles, then the computer player is dealt 16 tiles.\n";
		cout <<		"\t Fourth: the remaining tiles are placed into the Boneyard.\n\n";

		cout <<		"\t The first player is determined by who has the lowest score, if scores are even it is a coin flip.\n";
		cout <<		"\t Thereafter the players alternate turns until either of the players plays their last tile, or the game is\n";
		cout <<		"\t blocked because the bone yard is empty and both players pass their turns.\n";

		cout << "A Turn:\n\t A player plays at the end of an elligible train following the following logic:\n\n";
		cout <<		"\t If either player has left an orphan double tile at the end of a train, it is the only eligible train until\n";
		cout <<		"\t the double tile has been played against by either player. Otherwise elligible trains are:\n";
		cout <<			"\t\t Players personal train: to the right of the engine for the human\n";
		cout <<			"\t\t Mexican train: once it has been started. Either player can start the Mexican train with a tile from \n";
		cout <<				"\t\t\t their hand that matches the engine. It is advantageous to start the Mexican train \n";
		cout <<				"\t\t\t as early as possible to increase the number of eligible trains for all subsequent turns\n";
		cout <<				"\t\t\t Once the Mexican train has been started, tiles can only be added to its tail end, i.e., \n";
		cout <<				"\t\t\t the side of the starting tile that does not match the engine.\n";
		cout <<			"\t\t Opponent's personal train if it has a marker at its end.\n\n";

		cout <<		"\t A player can play a tile from his/her hand by matching the number of pips at one end of the tile with the \n";
		cout <<		"\t	number of pips at the open end of an eligible train. A player plays as follows:\n\n";

		cout <<			"\t\t No playable tiles: If the player does not have a tile that can be played at the end of a train:\n";
		cout <<				"\t\t\t If the boneyard is empty, the player passes their turn \n";
		cout <<				"\t\t\t and puts a marker at the end of their personal train.\n";
		cout <<				"\t\t\t If the boneyard is not empty, the player draws a\n";
		cout <<				"\t\t\t tile from the boneyard and plays it immediately.\n";
		cout <<					"\t\t\t\t If the player cannot play the drawn tile, the player\n";
		cout <<					"\t\t\t\t must add it to their hand, pass their turnand put a\n";
		cout <<					"\t\t\t\t marker at the end of their personal train.\n\n";

		cout <<			"\t\t Once the player's personal train has a marker at the end:\n";
		cout <<				"\t\t\t The opponent can play on the player's personal train\n";
		cout <<				"\t\t\t as long as the marker is present. The marker is removed\n";
		cout <<				"\t\t\t only when the player plays a tile at the end of their\n";
		cout <<				"\t\t\t own personal train. On subsequent turns, the player\n";
		cout <<				"\t\t\t can play on the Mexican train or opponent's personal\n";
		cout <<				"\t\t\t train with a marker even if there is a marker on their\n"; 
		cout <<				"\t\t\t own personal train.\n\n";

		cout <<			"\t\t If the player has a tile that they can play, they must play it as follows:\n";
		cout <<				"\t\t\t A non-double tile at the end of one of the eligible trains.\n";
		cout <<				"\t\t\t A double tile at the end of an eligible train, followed by\n";
		cout <<				"\t\t\t a non-double follow-up tile in the same turn:\n";
		cout <<					"\t\t\t\t If the player's hand is exhausted, i.e., the player has no more\n";
		cout <<					"\t\t\t\t tiles in the player's hand after playing the double, the game ends.\n";
		cout << "\t\t\t\t If the player's hand is not exhausted, but the player does not \n";
		cout << "\t\t\t\t have a non-double tile that can be played as a follow-up tile,\n";
		cout << "\t\t\t\t he player follows the procedure above for No playable tiles.\n";
		cout << "\t\t\t\t If the player has a tile that can be played as a follow-up tile,\n";
		cout << "\t\t\t\t  the player can play it as follows:\n";
		cout << "\t\t\t\t\t Next to the double the player just played.\n";
		cout << "\t\t\t\t\t At the end of any other eligible train. If so,\n";
		cout << "\t\t\t\t\t the double the player just played becomes an orphan\n";
		cout << "\t\t\t\t\t double. Once an orphan double is created, no trains\n";
		cout << "\t\t\t\t\t are eligible for either player until the orphan\n";
		cout << "\t\t\t\t\t double is played against by either player.\n";
		cout << "\t\t\t Two double tiles at the end of two eligible trains if (and only if):\n";
		cout << "\t\t\t\t The player will exhaust the player's hand after playing\n";
		cout << "\t\t\t\t the two doubles, ending the game, or\n";
		cout << "\t\t\t\t The player can play an additional third non-double tile from the player's hand\n";
		cout << "\t\t\t\t (without drawing from the boneyard). This could lead to one or both the played\n";
		cout << "\t\t\t\t double tiles becoming orphan doubles. But, the player will have played three\n";
		cout << "\t\t\t\t tiles in one turn.\n\n";

		cout << "Score:\n";
		cout << "\t When the game ends, each player gets round points equal to the sum of pips on all the tiles left in their hand.\n";
		cout << "\t For the player who empties their hand, this sum is 0. The round points of each player are added to the game \n";
		cout << "\t score of the player. Once the last round has ended, the winner of the game is the player with the lowest game\n";
		cout << "\t score. If both the players have the same game score, the game is a draw.\n";
		cout << "========================================================================================================================\n";
	}
	else
	{
		cout << "========================================================================================================================\n";
	}
}

// End of file Rules.cpp