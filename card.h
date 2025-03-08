#ifndef CARD
#define CARD

#include<iostream>

//This class defines a Card object. It is the unit that forms decks in this game.
//It's what Piles (another class) are composed of. 
class Card{
    int character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	std::string name; //The card's name.
	std::string type; //ATK, SKL, POW, CUR, STS
	int energy_cost; //if energy_cost = -1, card is unplayable
	std::string rarity; //How rare the card is 
	std::string card_text;
    
public:
    Card(int c, std::string n, std::string t, int cost, std::string r, std::string text);
    void display();    
    int getEnergyCost();
    std::string getName();
};

#endif
