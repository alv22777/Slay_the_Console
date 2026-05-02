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

	//Start method is getting a little too bloated, should probably split it into smaller methods
	//Choice handling could potentially be its own method, but it needs to interact with the game loop, so it would require some refactoring to work. For now, will just leave it as is, but will look into refactoring it in the future.
	


	//Renamed start to run, since it felt more appropriate and less confusing with the gameOver method.
	void Game::run(){

		int floor = 1;

		fight(floor); //This will be dependent on the floor type, for now, it's always a fight.
	
		//Player has 0 or less HP, they lose, triggering game over sequence.
		if(player.getAttribute(PlayerAttribute::HP)<=0){gameOver();}

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

	void Game::fight(int& floor){
		//This method will handle the combat loop, including player and enemy turns (Future implementation will include enemy actions as well, for now it is just a placeholder),
		// and checking for end of combat conditions. For now, it is all handled in the Game::start() method, but it would be cleaner to separate it into its own method.
		char choice = ' ';
		player.StartCombat(seed);
		
		int turn = 1;

		while(player.getAttribute(PlayerAttribute::HP)>0){	
					
			while(choice != 'E'){//while player hasn't chosen to end turn, keep asking for input and responding to it.
				
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
					//Wonder how to refactor this to be more elegant. Pile class could have improved display methods.

					case 'A': //Display draw pile
						/*
						Which cards are on the draw pile should not be hidden information, since that can be 
						deduced from cards in other piles (Discard, hand, exhaust). However, ther order of those
						cards should be. Therefore, when the player chooses to view the draw pile, they can see the 
						cards in the pile but not their order. Should probably add card ID numbers, then display them sorted by ID.
						Card ID is fine for now, but would not support modding or make changing the card pool harder.
						Will look into it in the future, for now, just display the cards in the order they are in the pile.
						*/
						player.displayPlayerPile(PileType::draw);
						continue;
					case 'K': //Display combat deck. This information is public, since the player can see which cards are in the combat deck by looking at the other piles.
						player.displayPlayerPile(PileType::deck); //Display master deck.
						continue;

					case 'D': //Display discard pile. This information is public.
						player.displayPlayerPile(PileType::discard);
						continue;

					case 'X': //Display exhaust pile. This information is public.
						player.displayPlayerPile(PileType::exhaust);
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
}