#ifndef GAME_H
#define GAME_H

class Player; class Enemy; class Character; enum class TID; class Pile; enum class CID;

#include<deque>
#include"game_logic/rng.h"
#include"character/enemy.h"
#include"game_logic/eventhandler.h"
#include"ui/eventlog.h"

#include<memory>

class Game{
	std::unique_ptr<Player>& player;
	std::deque<std::unique_ptr<Enemy>>& enemies;
	int turn; int floor;
	EventLog event_log;
	EventHandler event_handler;
	
	public:
	RNG rng;

	Game(std::unique_ptr<Player>& p, std::deque<std::unique_ptr<Enemy>>& e, uint64_t s, int l);
	
	//RUN FLOW

    void run();
	bool gameOver();
	
	//COMBAT FLOW

	void fight();	
		void initEnemies();
		void startOfCombat();
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

	std::deque<Character*> selectTargets(TID target, Character* source);
    bool hasValidTargets(TID t, Character& source);
    void resolveEffect(Character& source, Effect& effect, std::deque<Character*> targets);
	//EVENT HANDLER INTERACTION
	void enqueueEvent(Event e);
	void resolveQueue();

	//REWARDS
	Pile generateCards(std::vector<CID>* common, std::vector<CID>* uncommon, std::vector<CID>* rare, int amount);
	void cardReward();
	//UI

	void displayGameState();
	int32_t calculateIntentDamage(int32_t base, Enemy* source);
    void pushLog(std::string s, uint8_t level);

	//CLEANUP
	void cleanup();
	bool removeDeadCharacters();
	void removeInvalidPowers();
	
};
#endif
