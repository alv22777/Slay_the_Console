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
	int turn; int floor;
	public:
	RNG rng;
	EventLog event_log;

	Game(std::deque<Player> &p, uint64_t s, int l);
	
	void displayGameState();
	
	void run();
	void gameOver();
	bool removeDeadCharacters();

    void pushLog(std::string s, uint8_t evel);

    std::deque<Character*> selectTargets(TargetType target, Character* source);
	void enemyPlanning();
	void enemyActions();
	void fight(int& floor);
	void startTurn();
	void endTurn();
	bool isCombatOver();
    bool hasValidTargets(TargetType t, Character& source);
    void enemyTurn();
    void resolveEffects(Character& source, std::vector<Effect>& effects);


	void endOfCombat();
};
#endif