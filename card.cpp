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

    targetType target_type = source.getPlayed().getTargetType(); bool targetDied = false;
    std::deque <Character*> targets = game.selectTargets(this->getTargetType());    

    if(!targets.empty()){ //If valid target
        source.changeAttribute(PlayerAttribute::energy,-source.getPlayed().getEnergyCost()); //Pay energy cost.
        for(Effect e: effects){
            for(size_t i=0;i<targets.size();i++){e.apply(targets[i],source,game);} //Apply to all targets.
            targetDied=game.removeDeadCharacters(); //Remove any target that died

            //IF card has a single target that died, then stop.
            if(targetDied && (target_type==targetType::enemy || target_type==targetType::ally)){break;}
            // IF this card targets a random enemy or all enemies, valid target list may have changed, so select targets again.            
            if(target_type==targetType::random_enemy||target_type==targetType::all_enemies){targets = game.selectTargets(target_type);}
            if(targets.empty()){break;} //all valid targets died   
        }
        source.addToPlayerPile(PileType::discard,source.getPlayed()); //Go into discard
    }
    else{std::cout<<"Not a valid target!\n"; source.addToPlayerPile(PileType::hand, source.getPlayed());}//No effects resolved, go into hand.
}

