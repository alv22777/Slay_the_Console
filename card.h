#ifndef CARD_H
#define CARD_H

#include<iostream>
#include "effect.h"
#include<vector>
#include<random>
#include<deque>
//This class defines a Card object. It is the unit that forms decks in this game.
//It's what Piles (another class) are composed of. 


//Certain cards can only have certain targets. which are the following:
enum class targetType{ally, enemy, all_enemies, random_enemy, none};
enum class CardType {attack, skill, power, status, curse};
enum class CardRarity {starter, common, uncommon, rare, status, curse};

class Card{
    int character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	std::string name; //The card's name.
	CardType type; //ATK, SKL, POW, CUR, STS
	int energy_cost; //if energy_cost = -1, card is unplayable
	CardRarity rarity; //How rare the card is 
	std::string card_text;
    std::vector<Effect> effects; //The effects this card applies when played.   
    targetType target; //The type of target this card can be played on (self, enemy, all_enemies, random_enemy).
public:
    Card(int c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, targetType tar);
    void display();    
    int getEnergyCost();
    targetType getTargetType();
    std::string getName();
    std::string getCardType();
    std::string getCardRarity();
    
    void applyEffects(std::deque<Character*>& target, Character& source, Game& game);


};


#endif
