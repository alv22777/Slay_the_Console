#include"character.h"
#include"game.h"
#include <iostream>
#include "constants.h"

	Game::Game(Character p, std::mt19937 s)
		:player(p),seed(s){}

	void Game::displayGameState(Character& p) {
		system("cls"); // Clear screen
		p.displayStatus();
	}
	//Get the player's choice from a pile p.
	int Game::getPlayerChoice(){
		int choice;
		while(1){
			std::cout<<"Card to play?\n";
			std::cin>>choice;

			if(std::cin.fail()){std::cin.clear(); std::cin.ignore(1000,'\n'); std::cerr<<"Not a number.\n"; continue;}
			else if (choice>player.getHandSize()-1||choice<0){std::cout<<"choice not in valid range\n";continue;}
			else{
				player.setPlayed(player.getCardFromHand(choice));
				if(player.getCardFromHand(choice).getEnergyCost()>player.getEnergy()){
					std::cout<< "You don't have enough energy to play " << player.getCardFromHand(choice).getName()<<"!\n";
				}
				else{
					return choice;
				}
			}

		}
	}
	void Game::setupPlayer(int choice){
		switch(choice){
		case 1:
            player.setName("The Ironclad"); 
			player.setMaxHP(ICL_STARTING_MAX_HP); player.setHP(ICL_STARTING_MAX_HP); 
			player.setMaxEnergy(STARTING_ENERGY); player.setEnergy(STARTING_ENERGY);
			for(int i=0;i<ICL_STARTER_DECK.getSize();i++){player.addToDeck(ICL_STARTER_DECK.getCard(i));}
			player.setPlayed(blank_card);
            break;
		case 2:
			player.setName("The Silent"); 
			player.setMaxHP(SLT_STARTING_MAX_HP); player.setHP(SLT_STARTING_MAX_HP); 
			player.setMaxEnergy(STARTING_ENERGY); player.setEnergy(STARTING_ENERGY);
			for(int i=0;i<SLT_STARTER_DECK.getSize();i++){player.addToDeck(SLT_STARTER_DECK.getCard(i));}
			player.setPlayed(blank_card);
			break;
		}

	}
	void Game::start(){

		int choice = 0;
		player.StartCombat(seed);

		while(1){	
			displayGameState(player);
			player.displayHand();

			choice = getPlayerChoice();

			player.playCardFromHand(choice);
			Sleep(1000);
		}
	}
