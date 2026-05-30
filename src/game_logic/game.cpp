#include"game_logic/game.h"
#include"game_logic/rng.h"
#include"game_logic/power.h"
#include"game_logic/effect.h"
#include"character/player.h"
#include"character/enemy.h"
#include"data/constants.h"
#include"card/card.h"
#include"ui/input.h"
#include"ui/formatting.h"
#include <iostream>
#include "stdint.h"


//Takes in a deque of Player objects, an RNG uint32_t seed and an integer size for the game's event log.
Game::Game(std::unique_ptr<Player>& p, std::deque<std::unique_ptr<Enemy>>& e, uint64_t s, int l):
player(p), enemies(e), rng(s), event_log(EventLog(l)), floor(0), turn(0){}


//RUN FLOW
void Game::run(){
	floor = 0;
	while(player){
		floor++;
		fight(); //This will be dependent on the floor type, for now, it's always a fight.	
	}
	
}


bool Game::gameOver(){
	enemies.clear();	
	std::cout<<"You lost! go again?(y/n)\n";
	
	char replay;
	do{
		replay = inputChar();
	}while(!(replay== 'y' || replay == 'n'));
	
	if(replay=='y'){
		rng.setSeed(rng.nextInt(SEED_MIN,SEED_MAX));
		int choice = characterSelect();
		player = Player::createPlayer(choice);
		event_log.clear();
		return true;
	}
	else{std::cout<<"Thanks for playing!\n"; return false;}
}

//COMBAT FLOW

void Game::fight(){
	startOfCombat();
	char choice;
	turn = 1;
	
	initEnemies();
	//while player hasn't chosen to end turn, or the combat hasn't ended
	while(!isCombatOver()){
		choice = ' ';

		while(choice != 'e'){


			if(isCombatOver()){choice = 'e'; continue;}

			displayGameState();
							
			choice = inputChar();

			//Player tries to play a card from hand. 
			if('0'<=choice&&choice<='9'){//if input is a number, check if it's a valid card choice. If it is, play the card.
				choice-=48;//Convert char to int
				if(choice<player->getPlayerPileSize(PileID::hand)){ player->playCardFromHand(choice, *this); }
				else{std::cout<<"You don't have at least this many cards in hand! Try again.\n";}
				continue;
			}

			//Player wishes to do other actions, such as viewing the draw or discard pile, or ending the turn.
			switch(choice){
				case 'a': player->displayPlayerPile(PileID::draw, false, 0, true); break;
				case 'k': player->displayPlayerPile(PileID::deck, false, 0, false); break;
				case 'd': player->displayPlayerPile(PileID::discard, false, 0, false); break;
				case 'x': player->displayPlayerPile(PileID::exhaust, false, 0,false); break;
				case 'e': continue; //End turn 
				default: continue;
					
			}
			std::cout<<"Press any key to return...\n";
			system("pause>nul"); 
		}

		//If combat's over, end the combat, otherwise end the turn.
		if(isCombatOver()){ if(player){endOfCombat();} }
		else{
			endPlayerTurn();
			enemyTurn(); 
			turn++; choice = ' '; 
			startPlayerTurn();
		}

	}
	endOfCombat();
}

void Game::initEnemies(){

	//Placeholder enemies, will be replaced with actual enemies in the future.
	enemies.push_back(std::make_unique<Enemy>(
		"Green Louse",9,Color::green,
		std::deque<Intent>{
			Intent({ Effect(EffectType::damage,3,TargetType::player), Effect(EffectType::damage,3,TargetType::player) }), 
			Intent({ Effect(EffectType::damage,2,TargetType::player) })
		}
	));
	enemies.push_back(std::make_unique<Enemy>(
		"Red Louse", 9, Color::red, 
		std::deque<Intent>{
			Intent({ Effect(EffectType::damage, 2, TargetType::player)})
		}
	));
	enemies.push_back(std::make_unique<Enemy>(
		"Cultist", 30 ,Color::blue,
		std::deque<Intent>{
			Intent({ Effect(EffectType::gain,   1, TargetType::self, PID::ritual)}),
			Intent({ Effect(EffectType::damage, 2, TargetType::player)})
		}
	));
}
void Game::startOfCombat(){
	player->StartCombat(*this);
	pushLog("---------- Start of combat ---------", 0);
}
void Game::startPlayerTurn(){
	pushLog("----------- Start of turn ----------", 0);
	//startOfTurnEffects();
	
	if(player){
		player->setAttribute(Attribute::energy, player->getAttribute(Attribute::max_energy));
		player->setAttribute(Attribute::block,0);
		player->drawCards(5,*this);
		
		for(auto& pw: player->getPowers()){
			pw->onTurnStart();
		}
		
		player->removeInvalidPowers();
	}
}

void Game::endPlayerTurn(){
	pushLog("----------- End of turn ------------",0);


	for(auto& pw: player->getPowers()){
		pw->onTurnEnd();
	}
	player->removeInvalidPowers();
	player->discardHand();
}

void Game::enemyTurn(){
	pushLog("------------ Enemy turn ------------",0);
	startEnemyTurn();
	enemyActions();
	endEnemyTurn();
}

void Game::startEnemyTurn(){
	for(auto& e: enemies){
		for(auto& pw: e->getPowers()){
			pw->onTurnStart();
		}
		e->removeInvalidPowers();
	}
}

void Game::enemyActions(){
	for(auto& e: enemies){
		e->act(*this);
		if(isCombatOver()){break;}
	}
}

void Game::endEnemyTurn(){
	enemyPlanning();

	for(auto& e: enemies){
		for(auto& pw: e->getPowers()){
			pw->onTurnEnd();
		}
		e->removeInvalidPowers();
	}
}

void Game::enemyPlanning(){
	for(auto& e: enemies){
		e->chooseIntent(*this);
	}	
}

void Game::endOfCombat(){
	pushLog("---------- End of combat -----------",0);
	if(player){player->endCombat();}
}

//COMBAT LOGIC

bool Game::isCombatOver(){
	if(player == nullptr){return true;}
	if(enemies.empty() || !player){return true;}
	return false;
}


//TARGET ENFORCING / EFFECT RESOLUTION

std::deque<Character*> Game::selectTargets(TargetType target, Character* source){
	
	int choice = 0;
    std::deque<Character*> targets;
	

	switch(target){
		
		case TargetType::player:
			if(player){targets.push_back(player.get());}
			else{std::cout<<"No player to target!\n";}		
		break;

		case TargetType::enemy:
		
		if(enemies.size()==1){targets.push_back(enemies[0].get());}
		else if (enemies.size()==0){std::cout<<"No enemies to target!\n"; targets.clear(); break;}
		else{
			std::cout<<"Choose an enemy > ";
			choice = inputInt(0,enemies.size()-1, true);
			targets.push_back(enemies[choice].get());
		}
		break;
		
		case TargetType::enemy_all:	
		if(!enemies.empty()){for(auto &e :enemies){targets.push_back(e.get());} }
		else{std::cout<<"No enemies to target!\n";}
		break;
		
		case TargetType::random_enemy:
		if(!enemies.empty()){targets.push_back(enemies[rng.nextInt(0,enemies.size()-1)].get());}
		else{std::cout<<"No enemies to target!\n";}
		break;
		
		case TargetType::self: targets.push_back(source); break;
		
		default: std::cout<<"Invalid target type!\n"; break;
	}

    return targets;
	
}

bool Game::hasValidTargets(TargetType t, Character& source){
	switch(t){
		case TargetType::player:
			return (player != nullptr);
		case TargetType::enemy:
		case TargetType::random_enemy:
			return enemies.empty();
		case TargetType::self:
			return source.isAlive();
		default: return true;
	}
}

void Game::resolveEffects(Character& source, std::vector<Effect>& effects){

	std::deque<Character*> targets;
	if(effects.empty()){NO_EFFECT.apply({}, &source,*this); return;}
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

		results.push_back(effects[i].apply(targets, &source,*this));

		pushLog(effects[i].log(targets, &source, results[i]), 1);

		// Check whether reused single target died
		if(!source.isAlive()){removeDeadCharacters(); break;}
		target_died = is_single_target && !targets.empty() && !targets[0]->isAlive();
		
		displayGameState( );
		removeDeadCharacters(); //Cleanup
	}
}

//UI

void Game::displayGameState(){
	clearScreen();

	std::cout<<"========================================\n";
	std::cout<<"FLOOR "<<floor<<" - TURN "<<turn<<"  seed: "<<rng.base36()<<"\n";

	//Show game and player status.
	player->displayStatus();
	std::cout<<"Enemies:\n";
	for(size_t i = 0; i<enemies.size();i++){std::cout<<i<<") "; enemies[i]->displayStatus();}
	std::cout<<"----------------------------------------\n";

	player->displayPlayerPile(PileID::hand, true, 10, false);	
	std::cout<<    "Draw [A]: "<<player->getPlayerPileSize(PileID::draw);
	std::cout<<" Discard [D]: "<<player->getPlayerPileSize(PileID::discard);
	std::cout<<" Exhaust [X]: "<<player->getPlayerPileSize(PileID::exhaust);
	std::cout<<" End Turn [E]\n";
	std::cout<<"========================================\n";
	event_log.broadcast();

	std::cout<<"Last Played: ";
	if(player->getPlayed().getName() != blank_card.getName()){player->getPlayed().display();}

	std::cout<<"\nChoice > ";
}

void Game::pushLog(std::string s, uint8_t level){
	std::string indentation = "";
	for(int i = 0; i<level;i++){ indentation += "---"; }
	if(!s.empty()){event_log.receive(indentation + s);}
}


//CLEANUP

bool Game::removeDeadCharacters(){
	bool death = false;
	enemies.erase(
		std::remove_if(enemies.begin(),enemies.end(),
			[&](std::unique_ptr<Enemy>& e){
				if(!e->isAlive()){pushLog( color(e->getColor(),e->getName())+ " died.", 0 ); death = true; return true;}
				else{return false;}
			}
		),enemies.end());
	
	if(!player->isAlive()){
		player.reset();
		death = true;
	}

	return death;
}

void Game::removeInvalidPowers(){
	player->removeInvalidPowers();
	for(auto& e: enemies){ e->removeInvalidPowers(); }
}

