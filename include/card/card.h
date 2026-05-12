#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<vector>
#include"game_logic/effect.h"
#include "ui/colors.h"
//This class defines a Card object. It is the unit that forms piles.
class Player;


//Certain cards can only have certain targets. which are the following:

enum class CardType {attack, skill, power, status, curse};
enum class CardRarity {starter, common, uncommon, rare, status, curse};

class Card{
    Color character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	std::string name; //The card's name.
	CardType type; //ATK, SKL, POW, CUR, STS
	int energy_cost; //if energy_cost = -1, card is unplayable, -2 indicates X cost cards.
	CardRarity rarity; //How rare the card is 
	std::string card_text;
    std::vector<Effect> effects; //The effects this card applies when played.   
    bool exhaust;
public:
    Card(Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex);
    void display();    
    int getEnergyCost();
    
    std::string getName();
    std::string getCardType();
    std::string getCardRarity();
    void applyEffects(Player& source, Game& game, int pos);

};


#endif
