// Alec Rizzo - arizzo3@ramapo.edu
// Header file for polymorphic computer player
#pragma once

#include "Player.h"

class Computer : private Player
{
public:
	Computer();
	~Computer();

protected:
	friend class Round;
	friend class Game;


private:
};

// End of file Computer.h