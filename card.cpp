#include "card.h"
#include "effect.h"
#include "character.h"
#include "rng.h"

#include<iostream>

class Game; //Forward declaration to avoid circular dependency with `game.h`


//Creates a Card and initializes it's values with the given arguments.
Card::Card(int c, std::string n, std::string t, int cost, std::string r, std::string text, std::vector<Effect> e, targetType tar)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e), target(tar){}   
    
//Display this card on the terminal.	
void Card::display(){std::cout<<name<<"("<<energy_cost<<" NRG, "<<type<<"):"<<card_text<<'\n';}

int Card::getEnergyCost(){return energy_cost;}

std::string Card::getName(){return name;}

targetType Card::getTargetType(){return target;}


void Card::applyEffects(std::deque<Character*>& targets, Character& source, Game& game){
    for(Effect e : effects){
        for(int i = 0; i<targets.size();i++){
            e.apply(targets[i], source, game);
        }
    }
}

