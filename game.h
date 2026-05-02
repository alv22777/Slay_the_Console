#ifndef GAME_H
#define GAME_H
#include<random>
#include<algorithm>
#include "character.h"
#include "rng.h"

class Game{
	Character& player;


	public:
	RNG rng;
	Game(Character &p, RNG& r);
	
	void displayGameState(int floor, int turn);
    
	//Get the player's choice from a pile p.
	int getCardChoice();


	void run();
	void gameOver();
	void fight(int& floor);
	void startTurn();
	void endTurn();
};
#endif