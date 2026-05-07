#ifndef GAME_H
#define GAME_H

class Player; class Enemy; class Character; enum class targetType;
#include<deque>
#include"game_logic/rng.h"

class Game{
	std::deque<Player>& player;
	std::deque<Enemy>& enemies;

	public:
	RNG rng;

	Game(std::deque<Player> &p, std::deque<Enemy>&e, uint32_t s);
	
	void displayGameState(int floor, int turn);
	
	void run();
	void gameOver();
	bool removeDeadCharacters();

	std::deque<Character*> selectTargets(targetType target);

	void fight(int& floor);
	void startTurn();
	void endTurn();
	bool isCombatOver();

	void endOfCombat();
};
#endif