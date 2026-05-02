#include"character.h"
#include"game.h"
#include <iostream>
#include "constants.h"

	Game::Game(Character &p, std::mt19937& s)
		:player(p),seed(s){}

	void Game::displayGameState(int floor, int turn){
		system("cls"); // Clear screen
		
		std::cout<<"Floor "<<floor<<" - Turn "<<turn<<"\n";

		player.displayStatus();
		std::cout<<"Draw    (A): "<<player.getPlayerPileSize(PileType::draw)<<" Card(s)\n";
		std::cout<<"Discard (D): "<<player.getPlayerPileSize(PileType::discard)<<" Card(s)\n";
		std::cout<<"Exhaust (X): "<<player.getPlayerPileSize(PileType::exhaust)<<" Card(s)\n";	
		std::cout<<"Hand: \n";
		
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
		int turn = 1;
		int floor = 1;

		while(player.getAttribute(PlayerAttribute::HP)>0){	
			
			while(choice != 'E'){
				
				displayGameState(floor, turn);
				
				player.displayPlayerPile(PileType::hand);
				
				std::cout<<"E: End turn\n";
				
				std::cin>>choice;
				//Check if the input is a number, if not, clear the input and ask again.
				if(std::cin.fail()){std::cin.clear();std::cin.ignore(10000,'\n'); std::cerr<<"Not a number.\n";continue;}
				
				
				//Player tries to play a card from hand. 
				if(48<=choice&&choice<=57){//if input is a number, check if it's a valid card choice. If it is, play the card.
					choice-=48;//Convert char to int
					if(choice>=0&&choice<player.getPlayerPileSize(PileType::hand)){player.playCardFromHand(choice);}
					else{std::cout<<"You don't have at least this many cards in hand! Try again.\n";}
					Sleep(1000); continue;
				}
				


				//Player wishes to do other actions, such as viewing the draw or discard pile, or ending the turn.
				switch(choice){

					case 'A': //Display draw pile
						/*
						Which cards are on the draw pile should not be hidden information, since that can be 
						deduced from cards in other piles (Discard, hand, exhaust). However, ther order of those
						cards should be. Therefore, when the player chooses to view the draw pile, they can see the 
						cards in the pile but not their order. Should probably add card ID numbers, then display them sorted by ID.
						Card ID is fine for now, but would not support modding or make changing the card pool harder.
						Will look into it in the future, for now, just display the cards in the order they are in the pile.
						*/
						std::cout<<"Draw Pile:\n";
						player.displayPlayerPile(PileType::draw);
						std::cout<<"Press any key to return...\n";
						system("pause>nul");
						continue;


					case 'D': //Display discard pile. This information is public.
						std::cout<<"Discard Pile:\n";
						player.displayPlayerPile(PileType::discard);
						std::cout<<"Press any key to return...\n";
						system("pause>nul");
						continue;

					case 'X': //Display exhaust pile. This information is public.
						std::cout<<"Exhaust Pile:\n";
						player.displayPlayerPile(PileType::exhaust);
						std::cout<<"Press any key to return...\n";
						system("pause>nul");
						continue;

					case 'E': //End turn
						player.discardHand();
						std::cout<<"Turn ended. Hand discarded.\n";
						Sleep(1000);
						std::cout<<"Enemy turn...\n";
						Sleep(1000);
						std::cout<<"Start of turn...\n";
						Sleep(1000);

						player.setAttribute(PlayerAttribute::energy, player.getAttribute(PlayerAttribute::max_energy));
						player.setAttribute(PlayerAttribute::block, 0);
						player.drawCards(5,seed);
						
						choice = ' '; //Reset choice so that the next turn can start.
						turn++;
						continue;
						
					default:
						std::cout<<"Not a valid choice. Please try again!\n";
						Sleep(1000);
						continue;
						
				}


				Sleep(1000);
				continue;
			} 
			
			

		

		}

		//Player has 0 or less HP, they lose. Offer to replay or quit.
		std::cout<<"You lost! go again?(y/n)\n";
		char replay;
		std::cin>>replay;	
		if(replay=='y'||replay=='Y'){start();}
		else{std::cout<<"Thanks for playing!\n";}

	}
