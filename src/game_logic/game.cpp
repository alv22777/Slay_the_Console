#include"game_logic/game.h"
#include"game_logic/rng.h"
#include"game_logic/effect.h"
#include"character/player.h"
#include"character/enemy.h"
#include"data/constants.h"
#include"card/card.h"
#include"ui/input.h"
#include <iostream>
#include "stdint.h"



//Takes in a deque of Player objects, an RNG uint32_t seed and an integer size for the game's event log.
Game::Game(std::deque<Player> &p, uint64_t s, int l):player(p), enemies(), rng(s), event_log(EventLog(l)), floor(0), turn(0){
}

//Display game state. later will be split into displayGameState(); and displayCombatState();
void Game::displayGameState(){
	system("cls"); // Clear screen
	std::cout<<"========================================\n";
	std::cout<<"FLOOR "<<floor<<" - TURN "<<turn<<"  seed: "<<rng.base36()<<"\n";

	//Show game and player status.
	for(Player& p: player){p.displayStatus();}
	std::cout<<"Enemies:\n";
	for(size_t i = 0; i<enemies.size();i++){std::cout<<i<<") "; enemies[i].displayStatus();}
	std::cout<<"----------------------------------------\n";

	player[0].displayPlayerPile(PileType::hand, true, 10, false);	
	std::cout<<    "Draw [A]: "<<player[0].getPlayerPileSize(PileType::draw);
	std::cout<<" Discard [D]: "<<player[0].getPlayerPileSize(PileType::discard);
	std::cout<<" Exhaust [X]: "<<player[0].getPlayerPileSize(PileType::exhaust);
	std::cout<<" End Turn [E]\n";
	std::cout<<"========================================\n";
	event_log.broadcast();

	std::cout<<"Last Played: ";
	if(player[0].getPlayed().getName() != blank_card.getName()){player[0].getPlayed().display();}

	std::cout<<"\nChoice > ";
}

void Game::run(){
	floor = 0;
	while(!player.empty()){
		floor++;
		fight(floor); //This will be dependent on the floor type, for now, it's always a fight.	
	}
	gameOver();

}



//The player has lost the game
//Things like calculating score and awarding feats will go here in the future.
void Game::gameOver(){
	enemies.clear();	
	std::cout<<"You lost! go again?(y/n)\n";
	char replay = inputChar();
	if(replay=='y'||replay=='Y'){
		rng.setSeed(rng.nextInt(SEED_MIN,SEED_MAX));
		int choice = characterSelect();
		player.push_back(Player::createPlayer(choice));
		event_log.clear();
		run();
	}
	else{std::cout<<"Thanks for playing!\n";}
}


void Game::endTurn(){
	pushLog("---------- End of turn ----------",0);
	//endOfTurnEffects();
	player[0].discardHand();
}

std::deque<Character*> Game::selectTargets(TargetType target, Character* source){
	
	int choice = 0;
    std::deque<Character*> targets;
	
	switch(target){
		
		case TargetType::ally:
		if(player.size()==1){targets.push_back(&player[0]);}
		else if (player.size()==0){std::cout<<"No allies to target!\n"; break;}
		else{
			std::cout<<" Choose an ally > ";
			choice = inputInt(0,player.size(), true);
			targets.push_back(&player[choice]);
		}
		
		
		break;
		case TargetType::enemy:
		
		if(enemies.size()==1){targets.push_back(&enemies[0]);}
		else if (enemies.size()==0){std::cout<<"No enemies to target!\n"; targets.clear(); break;}
		else{
			std::cout<<"Choose an enemy > ";
			choice = inputInt(0,player.size(), true);
			targets.push_back(&enemies[choice]);
		}
		break;
		case TargetType::enemy_all:	
		if(!enemies.empty()){for(Character &e :enemies){targets.push_back(&e);} }
		else{std::cout<<"No enemies to target!\n";}
		break;
		
		case TargetType::random_enemy:
		if(!enemies.empty()){targets.push_back(&enemies[rng.nextInt(0,enemies.size()-1)]);}
		else{std::cout<<"No enemies to target!\n";}
		break;
		
		case TargetType::self: targets.push_back(source); break;
		
		default: std::cout<<"Invalid target type!\n"; break;
	}
    return targets;
	
}


//Combat Logic
bool Game::isCombatOver(){
	if(enemies.empty()||player.empty()){return true;}
	return false;
}
bool Game::hasValidTargets(TargetType t, Character& source){
	switch(t){
		case TargetType::ally:
			return player.empty();
		case TargetType::enemy:
		case TargetType::random_enemy:
			return enemies.empty();
		case TargetType::self:
			return source.isAlive();
		default: return true;
	}
}

void Game::startTurn(){
	pushLog("----------- Start of turn -----------", 0);
	//startOfTurnEffects();
	for(Player& p: player){
		p.setAttribute(Attribute::energy, p.getAttribute(Attribute::max_energy));
		p.setAttribute(Attribute::block,0);
		p.drawCards(5,*this);
	}
}

void Game::enemyTurn(){
	pushLog("----------- Enemy turn -----------",0);
	enemyActions();
	enemyPlanning();
}

void Game::endOfCombat(){
	pushLog("---------- End of combat -----------",0);
	for(Player& p:player){
		p.endCombat();
	}
}

void Game::resolveEffects(Character& source, std::vector<Effect>& effects){

	std::deque<Character*> targets;
	if(effects.empty()){NO_EFFECT.apply({},source,*this); return;}
	std::vector<EffectReport> results;

    //Initial conditions
    TargetType prev = effects[0].getTarget();
    bool is_single_target = effects[0].isSingleTarget();
    if(is_single_target){ 
		targets = selectTargets(prev, &source);
	}
    bool target_died = false;
	
	displayGameState( );

	for(size_t i = 0; i<effects.size();i++){
		//Target validation and selection
		TargetType current = effects[i].getTarget();
		is_single_target = effects[i].isSingleTarget();
		// Retarget if needed
		if(prev != current || !is_single_target){ targets = selectTargets(current, &source); }
		else if(target_died){continue;}
		prev = current;

		if(targets.empty()){continue;}

		results.push_back(effects[i].apply(targets,source,*this));

		pushLog(effects[i].log(targets, source, results[i]), 1);

		if(!source.isAlive()){removeDeadCharacters(); break;}
		target_died = is_single_target && !targets.empty() && !targets[0]->isAlive();
		
		
		// Check whether reused single target died
		displayGameState( );
		removeDeadCharacters(); //Cleanup
	}
}

//This method will handle the combat loop, including player and enemy turns.
void Game::fight(int& floor){
	

	for(Player &p: player){p.StartCombat(*this);}
	pushLog("---------- Start of combat ---------", 0);
	
	player[0].addPower( std::make_unique<Weak>(2, &player[0]) );
	player[0].addPower( std::make_unique<Vulnerable>(2, &player[0]) );
	
	//Placeholder enemy, will be replaced with actual enemies in the future.
	Enemy GreenLouse("Green Louse",10, Color::green, 
		{
			Intent({ Effect(EffectType::damage,3,TargetType::ally), Effect(EffectType::damage,3,TargetType::ally) }), 
			Intent({ Effect(EffectType::damage,2,TargetType::ally) })
		}
	);

	Enemy RedLouse("Red Louse",10, Color::red,
		{
			Intent({ Effect(EffectType::damage, 2, TargetType::ally)})
		}
	);

	enemies.push_back(std::move(GreenLouse)); enemies.push_back(std::move(RedLouse));
	
	char choice = ' ';
	turn = 1;
	
	//while player hasn't chosen to end turn, or the combat hasn't ended
	while(!isCombatOver()){
		choice = ' ';

		while(choice != 'E'){

			
			
			if(!isCombatOver()){ //If combat isn't over, we take user input


				displayGameState();
								
				choice = inputChar();

				//Player tries to play a card from hand. 
				if('0'<=choice&&choice<='9'){//if input is a number, check if it's a valid card choice. If it is, play the card.
					choice-=48;//Convert char to int
					
					if(choice<player[0].getPlayerPileSize(PileType::hand)){
						player[0].playCardFromHand(choice, *this);					
					}
					else{std::cout<<"You don't have at least this many cards in hand! Try again.\n";}
					continue;
				}
			}
			else{choice = 'E';} //Otherwise just end the turn (which will end the combat).

			//Player wishes to do other actions, such as viewing the draw or discard pile, or ending the turn.
			switch(choice){
				//Allow the player to view cards in the draw, discard and exhaust piles, as well as the deck.
				case 'a': 
					player[0].displayPlayerPile(PileType::draw, false, 0, true);
					std::cout<<"Press any key to return...\n";
					system("pause>nul"); 
				break;

				case 'k': 
					player[0].displayPlayerPile(PileType::deck, false, 0, false);
					std::cout<<"Press any key to return...\n";
					system("pause>nul"); 
				break;
				case 'd': 
					player[0].displayPlayerPile(PileType::discard, false, 0, false);
					std::cout<<"Press any key to return...\n";
					system("pause>nul"); 
				break;
				case 'x': 
					player[0].displayPlayerPile(PileType::exhaust, false, 0,false);
					std::cout<<"Press any key to return...\n";
					system("pause>nul"); 
				break;
				case 'e': //End turn 

					//If combat's over, end the combat, otherwise end the turn.
					if(isCombatOver()){
						if(!player.empty()){endOfCombat();}
						break;
					}
					else{
						endTurn();
						enemyTurn(); 
						turn++; choice = ' '; 
						//endOfEnemyTurn();
						startTurn(); break;
					}
					
				default: continue;
					
			}
		}
		

	}
	
	endOfCombat();
}

//method to check whether combat has ended. Return true if ALL enemies are dead, or the player is dead.



//Enemy logic
void Game::enemyActions(){
	for(Enemy& e: enemies){
		e.act(*this);
		if(isCombatOver()){break;}
	}
}
void Game::enemyPlanning(){
	for(Enemy& e: enemies){
		e.chooseIntent(*this);
	}	
}

//Game flow actions

//This method checks the list of characters in play. If any are dead, they are removed.
bool Game::removeDeadCharacters(){
	bool death = false;
	enemies.erase(
		std::remove_if(enemies.begin(),enemies.end(),
			[&](Character& e){
				if(!e.isAlive()){pushLog( color(e.getColor(),e.getName())+ " died.", 0 ); death = true; return true;}
				else{return false;}
			}
		),enemies.end());
	
	player.erase(
		std::remove_if(player.begin(),player.end(),
			[&](Character& p){
				if(!p.isAlive()){pushLog( color(p.getColor(),p.getName())+ " died.", 0); death = true; return true;}
				else{return false;}
				
			}
		),player.end());
	return death;
}

void Game::pushLog(std::string s, uint8_t level){
	std::string indentation = "";
	for(int i = 0; i<level;i++){ indentation += "---"; }
	if(!s.empty()){event_log.receive(indentation + s);}
}