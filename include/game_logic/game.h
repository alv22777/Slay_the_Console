#ifndef GAME_H
#define GAME_H

class Player; class Enemy; class Character; enum class TargetType;

#include<deque>
#include"game_logic/rng.h"
#include"character/enemy.h"
#include"ui/eventlog.h"

class Game{
	std::deque<Player>& player;
	std::deque<Enemy> enemies;
	public:
	RNG rng;
	EventLog event_log;

	Game(std::deque<Player> &p, uint32_t s, int l);
	
	void displayGameState(int floor, int turn);
	
	void run();
	void gameOver();
	bool removeDeadCharacters();

	std::deque<Character*> selectTargets(TargetType target, Character* source);
	void enemyPlanning();
	void enemyActions();
	void fight(int& floor);
	void startTurn();
	void endTurn();
	bool isCombatOver();
	void enemyTurn();
	

	void endOfCombat();
};
#endif