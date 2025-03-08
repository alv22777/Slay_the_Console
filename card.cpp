#include "card.h"
#include<iostream>


//Creates a Card and initializes it's values with the given arguments.
Card::Card(int c, std::string n, std::string t, int cost, std::string r, std::string text)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text){}   
    
//Display this card on the terminal.	
void Card::display(){std::cout<<name<<"("<<energy_cost<<" NRG, "<<type<<"):"<<card_text<<'\n';}

int Card::getEnergyCost(){return energy_cost;}

std::string Card::getName(){return name;}
