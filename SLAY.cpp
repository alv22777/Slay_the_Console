#include "card.h"
#include "pile.h"
#include "character.h"
#include <deque>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>

using std::string; using std::cout; using std::deque; using std::cin; using std::random_shuffle;	


const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;
/*
	Glossary:
	ICL: The Ironclad
	SLT: The Silent
	DEF: The Defect
	WAT: The Watcher
	CLS: Colorless cards
	HP: Hit Points. If it becomes 0, you instantly die and lose the game.
	NRG: Energy. It's used to play cards.
	BLK: Block. If an enemy attacking would reduce your HP, lose that amount of block instead.
	ATK: An Attack. Deals damage to an/ALL enemies. Sometimes has other effects.
	SKL: Skill. Usually gives you block and/or other useful efects like card draw.
	POW: Power. Gives you a continuous (useful) effect throughout combat.
	CUR: Curse. Has negative effects. Obtained through events and certain relics.
	EXH: Exhaust. When this card is played, remove it from your deck until end of combat. 
*/

std::mt19937 seed(std::time(nullptr));// Better random number generator


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card ICL_Strike = {0, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card ICL_Defend = {0, "Defend", "SKL", 1, "Starter", "YOU: 5 BLK"};
Card ICL_Bash = {0, "Bash", "ATK", 2,  "Starter", "ENY: 8 DMG, 2 VUL"};

Card blank_card = {0,"None","None",0,"None","None"};
Pile ICL_STARTER_DECK;
Pile empty_deck;


////////////////////CARD REWARDS//////////////////
Card IC_Card_Rewards[] ={
	{0, "Clothesline", "ATK", 2, "Common", "ENY: 12 DMG, 2 WKN"},
	{0, "Power Through", "SKL", 2, "Uncommon", "YOU: 15 BLK, HAND: 2 WND"},
	{0, "Reckless Charge", "ATK", 1, "Uncommon","ENY: 7 DMG DRW: 1 DZD"},
	{0, "Demon Form", "POW", 3, "Rare", "TURN: YOU: +3 STR"}
};

////////////////////CARD REWARDS//////////////////


bool change = 1;
Character player = Character("NOPLAYER", 0, 0, 0, 0, 0, empty_deck, blank_card);

int main(){ 
	for(int i =0; i<9;i++){
		(i<5)? ICL_STARTER_DECK.addCardToPile(ICL_Strike):ICL_STARTER_DECK.addCardToPile(ICL_Defend);
	}
	ICL_STARTER_DECK.addCardToPile(ICL_Bash);
	
	
	// set seed
	//std::mt19937 g(12314);
	 

	
	int choice = 0;
	while(choice>4||choice<1){cout<<"Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n"; cin>>choice;}
	
	switch(choice){
		case 1: 
			player = Character("The Ironclad", ICL_STARTING_MAX_HP, ICL_STARTING_MAX_HP, STARTING_ENERGY, STARTING_ENERGY, STARTING_BLOCK, ICL_STARTER_DECK, blank_card);
			cout<<"YOU SELECTED "<<player.getName()<<"\nStarting max HP: "<<player.getMaxHP()<<"\nHP: "<<player.getHP()<<"\nMax Energy: "<<player.getMaxEnergy()<<"\nEnergy: "<<player.getEnergy()<<"\nSTARTER DECK:\n";
			player.getDeck().displayPile();
			break;
		
		case 2:break;
	}
	
	cout<<"COMBAT SIMULATION"<<'\n';
	
	player.StartCombat(seed);


	while(1){

		if(change==1){
			system("cls");
		}

			change=0;			
			player.displayStatus();
			cout<<"Hand:\n";
			player.getHand().displayPile();
			//STATUS BAR


			do{
				cout<<"CARD TO PLAY?\n";
				cin>>choice;
				if(cin.fail()){cin.clear(); cin.ignore(1000, '\n');cout<<"NOT A NUMBER\n";choice=100;continue;}
				if(choice<player.getHand().getCards().size()&&choice>=0){if(player.getHand().getCards()[choice].getEnergyCost()>player.getEnergy()){cout<<"NOT ENOUGH ENERGY.\n";}}

			}while((choice>player.getHand().getCards().size()-1||choice<0)||(player.getHand().getCards()[choice].getEnergyCost()>player.getEnergy())||cin.fail());
			
			Card Played = player.getHand().getCards()[choice];
			player.playCardFromHand(choice);

			Sleep(1000);

			change = 1;
	}
	
	return 0;
}

