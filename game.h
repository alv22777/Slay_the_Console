#ifndef GAME_H
#define GAME_H
#include<random>
#include<algorithm>
#include "character.h"
#include "rng.h"

class Game{
	std::deque<Character>& player;
	std::deque<Character>& enemies;

	public:
	RNG rng;
	Game(std::deque<Character> &p, std::deque<Character>&e, uint32_t s);
	
	void displayGameState(int floor, int turn);
	
    std::deque<Character>& getEnemies();
	std::deque<Character>& getPlayers();

	void run();
	void gameOver();
	std::deque<Character*> selectTargets(targetType target);

	void fight(int& floor);
	void startTurn();
	void endTurn();
};
#endif