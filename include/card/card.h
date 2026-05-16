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
    Color character; 
	std::string name;
	CardType type;
	int energy_cost; // -2: X cost, -1: unplayable
	CardRarity rarity;
	std::string card_text;
    std::vector<Effect> effects;  
    bool exhaust;
public:
    Card(Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex);
    void display();    
    int getEnergyCost();
    std::string getName();
    Color rarityColor(CardRarity r);
    CardType getCardType();
    std::string getCardTypeText();
    std::string getCardRarity();
    void applyEffects(Player& source, Game& game, int pos);
    bool canPlay(Player& source, Game& game);
};


#endif
