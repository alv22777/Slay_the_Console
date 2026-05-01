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
	//Get the player's choice from a pile p. This is deprecated, as player choices are now handled in the Game::start() method.
	int Game::getCardChoice(){
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

		char choice = ' ';
		player.StartCombat(seed);

		while(player.getAttribute(PlayerAttribute::HP)>0){	
			displayGameState();
			player.displayPlayerPile(PileType::hand);
			
			std::cout<<"E: End turn\n";
			std::cin>>choice;
			//Check if the input is a number, if not, clear the input and ask again.
			if(std::cin.fail()){std::cin.clear();std::cin.ignore(10000,'\n'); std::cerr<<"Not a number.\n";continue;}



			if(48<=choice&&choice<=57){
				choice-=48;//Convert char to int if possible.. 48 = '0', 57 = '9', otherwise, keep as char for switch statement.
				if(choice>=0&&choice<player.getPlayerPileSize(PileType::hand)){
					player.playCardFromHand(choice); //Play card from hand if choice is 0-9. Otherwise, check for letter options.
				}
				else{std::cout<<"No card selected. Please try again!\n";}
				Sleep(2000);
				continue;
			} 

			switch(choice){
				case 'E': //End turn
					player.discardHand();
					std::cout<<"Turn ended. Hand discarded.\n";
					Sleep(1000);
					std::cout<<"Enemy turn...\n";
					Sleep(2000);
					std::cout<<"Start of turn...\n";
					Sleep(2000);

					player.setAttribute(PlayerAttribute::energy, player.getAttribute(PlayerAttribute::max_energy));
					player.setAttribute(PlayerAttribute::block, 0);
					player.drawCards(5,seed);
					
					continue;
				default:
					std::cout<<"Not a valid choice. Please try again!\n";
					Sleep(2000);
					continue;
			}
			
			Sleep(1000);
		}
		std::cout<<"You lost!\n";
		Sleep(2000);
	}
