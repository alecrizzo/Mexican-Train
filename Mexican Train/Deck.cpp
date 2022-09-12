//************************************************************
//* Name:  Alec Rizzo
//* Project : Mexican Train C++
//* Class : Organization of Programming Languages - CMPS 366-01 
//* Date : 10/20/2021
//************************************************************
#include "deck.h"

/*
====================================================================
							  Deck
====================================================================
*/


// Constructs the deck as a double nine set for use in the game
Deck::Deck()
{
	Tile tile_1(0, 0), tile_2(0, 1), tile_3(0, 2), tile_4(0, 3), tile_5(0, 4), tile_6(0, 5), tile_7(0, 6), tile_8(0, 7), tile_9(0, 8), tile_10(0, 9),
		tile_11(1, 1), tile_12(1, 2), tile_13(1, 3), tile_14(1, 4), tile_15(1, 5), tile_16(1, 6), tile_17(1, 7), tile_18(1, 8), tile_19(1, 9),
		tile_20(2, 2), tile_21(2, 3), tile_22(2, 4), tile_23(2, 5), tile_24(2, 6), tile_25(2, 7), tile_26(2, 8), tile_27(2, 9),
		tile_28(3, 3), tile_29(3, 4), tile_30(3, 5), tile_31(3, 6), tile_32(3, 7), tile_33(3, 8), tile_34(3, 9),
		tile_35(4, 4), tile_36(4, 5), tile_37(4, 6), tile_38(4, 7), tile_39(4, 8), tile_40(4, 9),
		tile_41(5, 5), tile_42(5, 6), tile_43(5, 7), tile_44(5, 8), tile_45(5, 9),
		tile_46(6, 6), tile_47(6, 7), tile_48(6, 8), tile_49(6, 9),
		tile_50(7, 7), tile_51(7, 8), tile_52(7, 9),
		tile_53(8, 8), tile_54(8, 9),
		tile_55(9, 9);

	double_nine_set = 
	{ 
		tile_1, tile_2, tile_3, tile_4, tile_5, tile_6, tile_7, tile_8, tile_9, tile_10,
		tile_11, tile_12, tile_13, tile_14, tile_15, tile_16, tile_17, tile_18, tile_19,
		tile_20, tile_21, tile_22, tile_23, tile_24, tile_25, tile_26, tile_27,
		tile_28, tile_29, tile_30, tile_31, tile_32, tile_33, tile_34,
		tile_35, tile_36, tile_37, tile_38, tile_39, tile_40,
		tile_41, tile_42, tile_43, tile_44, tile_45,
		tile_46, tile_47, tile_48, tile_49,
		tile_50, tile_51, tile_52,
		tile_53, tile_54,
		tile_55
	};
	
}


/* *********************************************************************
Function Name: printDeck
Purpose: print the entire deck after shuffling
Parameters:
Return Value: void
Algorithm:
			1) shuffle deck
			2) print deck
Assistance Received: none
********************************************************************* */
void Deck::printDeck()
{
	shuffleDeck();
	for (int i = 0; i < DOUBLE_NINE_SIZE; i++)
	{
		Tile temp = this->double_nine_set.at(i);
		temp.printTile();
		cout << endl;
	}
}// End of printDeck()

/* *********************************************************************
Function Name: shuffleDeck
Purpose: shuffle the double nine set
Parameters:
Return Value: void
Algorithm:
			1) get time based seed
			2) shuffle based on the rng from the seed
Assistance Received: Got help from: https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
********************************************************************* */
void Deck::shuffleDeck() 
{
	// Time based seed to shuffle pieces in the set
	unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rng(time);
	shuffle(begin(this->double_nine_set), end(this->double_nine_set), rng);
}// End of shuffleDeck()

/* *********************************************************************
Function Name: popNumTiles
Purpose: pop the number of tiles equal to int num to the vector passed
Parameters:
			stack, vector of tiles passed by reference
			num, integer of how many tiles to pop passed by value
Return Value: void
Algorithm:
			1) pop the tiles and push them to the passed vector if the 
				deck has enough tiles left
Assistance Received: none
********************************************************************* */
void Deck::popNumTiles(vector<Tile> & stack, int num)
{
	if (!(this->double_nine_set.size() < num))
	{
		for (int i = 0; i < num; i++)
		{
			stack.push_back(this->double_nine_set.back());
			this->double_nine_set.pop_back();
		}
	}
}// End of popNumTiles()
// End of file Deck.cpp
