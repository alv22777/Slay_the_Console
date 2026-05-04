#include "card.h"
#include "effect.h"
#include "character.h"
#include "rng.h"
#include "game.h"
#include<iostream>


//Creates a Card and initializes it's values with the given arguments.
Card::Card(int c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, targetType tar)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e), target(tar){}   
    
//Display this card
void Card::display(){std::cout<<name<<"("<<energy_cost<<" NRG, "<<getCardType()<<"):"<<card_text<<'\n';}

int Card::getEnergyCost(){return energy_cost;}

std::string Card::getName(){return name;}

targetType Card::getTargetType(){return target;}

std::string Card::getCardType(){
    switch(type){
        case CardType::attack: return "Attack";
        case CardType::skill: return "Skill";
        case CardType::power: return "Power";
        case CardType::status: return "Status";
        case CardType::curse: return "Curse";
        default: return "none";
    }
}
std::string Card::getCardRarity(){
        switch(rarity){
        case CardRarity::starter: return "Starter";
        case CardRarity::common: return "Common";
        case CardRarity::uncommon: return "Uncommon";
        case CardRarity::rare: return "Rare";
        case CardRarity::status: return "Status";
        case CardRarity::curse: return "Curse";
        default: return "none";
    }
}
void Card::applyEffects(Character& source, Game& game){
    
    bool isFirstEffect = true;

    for(Effect e : effects){
        //Select card's targets
        
        std::deque <Character*> targets = game.selectTargets(this->getTargetType());
        //If a valid target was selected
        if(!targets.empty()){
            //Pay the energy cost of the card.
            if(isFirstEffect){source.changeAttribute(PlayerAttribute::energy,-source.getPlayed().getEnergyCost());}

            for(int i = 0; i<targets.size();i++){

                //IF the card deals damage to a random enemy, we redefine the targets.
                if(source.getPlayed().getTargetType() == targetType::random_enemy){targets = game.selectTargets(this->getTargetType());}
                
                //apply corresponding effect in effect vector.
                e.apply(targets[i], source, game);
            }
            //After all effects have been applied, this card is added to the player's discard pile.
            source.addToPlayerPile(PileType::discard, source.getPlayed());
        }
        else{ //Then an invalid target was selected, so we don't deduct energy or apply effects.
            std::cout<<"Invalid target, card not played!\n";
            source.addToPlayerPile(PileType::hand, source.getPlayed());
        }

        isFirstEffect = false;
        game.removeDeadCharacters();
       
    }
}

