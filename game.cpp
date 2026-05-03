#include"character.h"
#include"game.h"
#include <iostream>
#include "constants.h"
#include "rng.h"

Game::Game(std::deque<Character> &p, std::deque<Character>&e, uint32_t s)
	:player(p), enemies(e), rng(s){}

void Game::displayGameState(int floor, int turn){
	system("cls"); // Clear screen
	
	//Show game and player status.
	for(Character& p: player){
		std::cout<<"Floor "<<floor<<" - Turn "<<turn<<"\n";
		p.displayStatus();
		std::cout<<"Draw     (A): "<<p.getPlayerPileSize(PileType::draw)<<" Card(s)\n";
		std::cout<<"Discard  (D): "<<p.getPlayerPileSize(PileType::discard)<<" Card(s)\n";
		std::cout<<"Exhaust  (X): "<<p.getPlayerPileSize(PileType::exhaust)<<" Card(s)\n";	
	}
	
	std::cout<<"End Turn (E)\n";
	
}


void Game::run(){
	int floor = 1;
	fight(floor); //This will be dependent on the floor type, for now, it's always a fight.	
	//Player has 0 or less HP, they lose, triggering game over sequence.
	
	if(player[0].getAttribute(PlayerAttribute::HP)<=0){gameOver();}

}



//The player has lost the game
//Things like calculating score and awarding feats will go here in the future.
void Game::gameOver(){
	std::cout<<"You lost! go again?(y/n)\n";
	char replay;
	std::cin>>replay;	
	if(replay=='y'||replay=='Y'){run();}
	else{std::cout<<"Thanks for playing!\n";
	}
}

void Game::endTurn(){
	player[0].discardHand();
	std::cout<<"Turn ended. Hand discarded.\n";
	Sleep(1000);
	std::cout<<"Enemy turn...\n";
	Sleep(1000);

}

void Game::startTurn(){
	std::cout<<"Start of turn...\n";
	Sleep(1000);
	player[0].setAttribute(PlayerAttribute::energy, player[0].getAttribute(PlayerAttribute::max_energy));
	player[0].setAttribute(PlayerAttribute::block, 0);
	player[0].drawCards(5,*this);
}

std::deque<Character*> Game::selectTargets(targetType target){

	int choice = 0;
    std::deque<Character*> targets;

	switch(target){
		case targetType::ally:
			std::cout<<"This card can target allies!\n";
			std::cout<<"Choose an ally:\n";
			for(size_t i = 0; i<player.size();i++){std::cout<<i<<". "<<player[i].getName()<<'\n';}
			std::cin>>choice;
			//This should have secure input handling.
			if(choice>=0 && choice<player.size()){
				std::cout<<"You targeted "<<player[choice].getName()<<"!\n";
				targets.push_back(&player[choice]);
			}else{std::cout<<"Invalid target! Try again.\n"; }

		break;
		case targetType::enemy:

			std::cout<<"This card can target enemies!\n";
			for(size_t i = 0; i<enemies.size();i++){std::cout<<i<<". "<<enemies[i].getName()<<'\n';}
			std::cin>>choice;
			//This should have secure input handling.
			if(choice>=0 && choice<enemies.size()){
				std::cout<<"You targeted "<<enemies[choice].getName()<<"!\n";
				targets.push_back(&enemies[choice]);
			}else{std::cout<<"Invalid target! Try again.\n"; }
			
		break;
		case targetType::all_enemies:
			std::cout<<"This card targets all enemies!\n";	
		
			for(Character &e :enemies){
				targets.push_back(&e);
			}


		break;

		case targetType::random_enemy:
			std::cout<<"This card targets a random enemy!\n";
			if(!enemies.empty()){
				targets.push_back(&enemies[rng.nextInt(0,enemies.size()-1)]);
			}
			else{std::cout<<"No enemies to target!\n";}
            
		break;
        
		default: std::cout<<"Invalid target type!\n"; break;

	}
    return targets;

}

//This method will handle the combat loop, including player and enemy turns (Future implementation will include enemy actions as well, for now it is just a placeholder),
// and checking for end of combat conditions. For now, it is all handled in the Game::start() method, but it would be cleaner to separate it into its own method.	
void Game::fight(int& floor){
	
	
	player[0].StartCombat(*this);

	
	//Placeholder enemy, will be replaced with actual enemies in the future.
	Character LouseA  = Character("Louse A",10,10,0,0,0,empty_deck,blank_card);
	Character LouseB  = Character("Louse B",10,10,0,0,0,empty_deck,blank_card);

	this->enemies.clear(); enemies.push_back(LouseA); enemies.push_back(LouseB);
	

	char choice = ' ';
	int turn = 1;
	
	while(player[0].getAttribute(PlayerAttribute::HP)>0){		
		choice=' ';
		while(choice != 'E'){//while player hasn't chosen to end turn, keep asking for input and responding to it.
			

			displayGameState(floor, turn);
			
			player[0].displayPlayerPile(PileType::hand);
			
			//Display enemies status, should display intents in the future.
			for(Character &enemy : enemies){enemy.displayStatus();}
			

			std::cout<<"Your choice?\n";				
			std::cin>>choice;
			//Check if the input is a number, if not, clear the input and ask again.
			if(std::cin.fail()){std::cin.clear();std::cin.ignore(10000,'\n'); std::cerr<<"Not a number.\n";continue;}
			
			
			//Player tries to play a card from hand. 
			if(48<=choice&&choice<=57){//if input is a number, check if it's a valid card choice. If it is, play the card.
				choice-=48;//Convert char to int
				
				if(choice>=0&&choice<player[0].getPlayerPileSize(PileType::hand)){

					if(std::cin.fail()){std::cin.clear();std::cin.ignore(10000,'\n'); std::cerr<<"Not a number.\n";continue;}

					player[0].playCardFromHand(choice, *this);
				
				}
				else{std::cout<<"You don't have at least this many cards in hand! Try again.\n";}
				Sleep(1000); continue;
			}

		
			//Player wishes to do other actions, such as viewing the draw or discard pile, or ending the turn.
			switch(choice){
				//Allow the player to view cards in the draw, discard and exhaust piles, as well as the deck.
				case 'A': player[0].displayPlayerPile(PileType::draw); continue;
				case 'K': player[0].displayPlayerPile(PileType::deck); continue;
				case 'D': player[0].displayPlayerPile(PileType::discard); continue;
				case 'X': player[0].displayPlayerPile(PileType::exhaust); continue;
				case 'E': //End turn
					endTurn();	
					choice = ' '; 
					turn++;
					Sleep(1000);

					startTurn();
					continue;
					
				default:
					std::cout<<"Not a valid choice. Please try again!\n";
					Sleep(1000);
					continue;
					
			}
		}

}
}