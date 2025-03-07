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
	int Game::getPlayerChoice(Pile& p){
		int choice;
		while(1){
			std::cout<<"Card to play?\n";
			std::cin>>choice;

			if(std::cin.fail()){std::cin.clear(); std::cin.ignore(1000,'\n'); std::cerr<<"Not a number.\n"; continue;}
			else if (choice>player.getHandSize()-1||choice<0){std::cout<<"choice not in valid range\n";continue;}
			else{
				player.setPlayed(player.getCardFromHand(choice));
				if(player.getPlayed().getEnergyCost()>player.getEnergy()){
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
            player.setName("The Ironclad"); player.setMaxHP(ICL_STARTING_MAX_HP); player.setHP(ICL_STARTING_MAX_HP); player.setMaxEnergy(STARTING_ENERGY); player.setEnergy(STARTING_ENERGY);player.getDeck().addPileToSelf(ICL_STARTER_DECK); player.setPlayed(blank_card);
            break;
		case 2:
            player.setName("The Silent"); player.setMaxHP(SLT_STARTING_MAX_HP); player.setHP(SLT_STARTING_MAX_HP); player.setMaxEnergy(STARTING_ENERGY); player.setEnergy(STARTING_ENERGY); player.getDeck().addPileToSelf(SLT_STARTER_DECK); player.setPlayed(blank_card);
			break;
		}

	}
	void Game::start(){

		int choice = 0;
		player.StartCombat(seed);

		while(1){	
			displayGameState(player);
			player.getHand().displayPile();

			choice = getPlayerChoice(player.getHand());

			player.playCardFromHand(choice);
			Sleep(1000);
		}
	}
