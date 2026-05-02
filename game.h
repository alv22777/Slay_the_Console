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

	void displayGameState(int floor, int turn);
    
	//Get the player's choice from a pile p.
	int getCardChoice();


	void run();
	void gameOver();
	void fight(int& floor);
	void startTurn(std::mt19937& seed);
	void endTurn();
};
#endif