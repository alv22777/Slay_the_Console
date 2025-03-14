#include"character.h"
#include"game.h"
#include <iostream>
#include "constants.h"

	Game::Game(Character &p, std::mt19937& s)
		:player(p),seed(s){}

	void Game::displayGameState() {
		system("cls"); // Clear screen
		player.displayStatus();
	}
	//Get the player's choice from a pile p.
	int Game::getPlayerChoice(){
		int choice;
		do{
			std::cout<<"Card to play?\n";
			std::cin>>choice;

			if(std::cin.fail()){std::cin.clear();std::cin.ignore(1000,'\n'); std::cerr<<"Not a number.\n";continue;}
			if(choice>=0&&choice<player.getPlayerPileSize(PileType::hand)){return choice;}

			std::cout<<"Not in valid range. Please try again!\n";
		}
		while(1);
	}

	void Game::start(){

		int choice = 0;
		player.StartCombat(seed);

		while(player.getAttribute(PlayerAttribute::HP)>0){	
			displayGameState();
			player.displayPlayerPile(PileType::hand);

			choice = getPlayerChoice();
			
			player.playCardFromHand(choice);
			Sleep(1000);
		}
	}
