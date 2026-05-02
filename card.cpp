#include "card.h"
#include "effect.h"
#include<iostream>
#include<vector>
class Game; //Forward declaration to avoid circular dependency with `game.h`
//Creates a Card and initializes it's values with the given arguments.
Card::Card(int c, std::string n, std::string t, int cost, std::string r, std::string text, std::vector<Effect> e)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e){}   
    
//Display this card on the terminal.	
void Card::display(){std::cout<<name<<"("<<energy_cost<<" NRG, "<<type<<"):"<<card_text<<'\n';}

int Card::getEnergyCost(){return energy_cost;}

std::string Card::getName(){return name;}

void Card::applyEffects(Character& target, Character& source, Game& game){
    for(Effect e : effects){
        e.apply(target, source, game);
    }
}