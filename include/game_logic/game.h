#ifndef GAME_H
#define GAME_H

class Player; class Enemy; class Character; enum class TargetType;

#include<deque>
#include"game_logic/rng.h"
#include"character/enemy.h"
#include"ui/eventlog.h"
#include<memory>

class Game{
	std::unique_ptr<Player>& player;
	std::deque<std::unique_ptr<Enemy>>& enemies;
	int turn; int floor;
	EventLog event_log;
	public:
	RNG rng;

	Game(std::unique_ptr<Player>& p, std::deque<std::unique_ptr<Enemy>>& e, uint64_t s, int l);
	
	//RUN FLOW

    void run();
	void gameOver();
	
	//COMBAT FLOW

	void fight(int& floor);	

		void startPlayerTurn();
		void endPlayerTurn();
	
		void enemyTurn();
			void startEnemyTurn();
			void enemyActions();
			void endEnemyTurn();
				void enemyPlanning();
				
		void endOfCombat();

	//COMBAT LOGIC
	
	bool isCombatOver();
		
	//TARGET ENFORCEMENT / EFFECT RESOLUTION

	std::deque<Character*> selectTargets(TargetType target, Character* source);
    bool hasValidTargets(TargetType t, Character& source);
    void resolveEffects(Character& source, std::vector<Effect>& effects);

	//UI

	void displayGameState();
    void pushLog(std::string s, uint8_t level);

	//CLEANUP

	bool removeDeadCharacters();
	void removeInvalidPowers();
};
#endif
