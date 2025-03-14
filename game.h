#ifndef GAME_H
#define GAME_H
#include<random>
#include<algorithm>
#include "character.h"

class Game{
	Character& player;
	std::mt19937 seed; 
	public:
	Game(Character &p, std::mt19937& s);

	void displayGameState();
    
	//Get the player's choice from a pile p.
	int getPlayerChoice();


	void start();
};
#endif