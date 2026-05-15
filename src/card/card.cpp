#include "card/card.h"
#include "game_logic/game.h"
#include "character/player.h"
#include "game_logic/effect.h"
#include "ui/colors.h"
#include<iostream>
#include<vector>



//Creates a Card and initializes it's values with the given arguments.
Card::Card(Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e), exhaust(ex){}   
    
//Display this card
void Card::display(){
    std::string cost;
    std::string card_type;
    
    switch(energy_cost){
        case -2: cost = color(character, "(X)"); break;
        case -1: cost = color(character, "(-)"); break;
        default: cost = color(character, "("+std::to_string(energy_cost)+") "); break;
    }
    switch(type){
        case CardType::attack: card_type = color(character, u8" ▲ "); break;
        case CardType::skill: card_type = color(character, u8" ■ "); break;
        case CardType::power: card_type = color(character, u8" ● "); break;
        case CardType::status: card_type = color(Color::status,u8"  ꩜ "); break;
        case CardType::curse: card_type = color(Color::curse,u8"  ⛦ "); break;
        default: card_type="none"; break; 
    }

    std::cout<<cost<<card_type<<color(rarityColor(rarity), name)<<": "<<card_text;
    if(exhaust){std::cout<<color(Color::exhaust," Exhaust.");}
}

int Card::getEnergyCost(){return energy_cost;}

std::string Card::getName(){return name;}

Color Card::rarityColor(CardRarity r){
    switch(r){
        case CardRarity::common: return Color::common;
        case CardRarity::uncommon: return Color::uncommon;
        case CardRarity::rare: return Color::rare;
        case CardRarity::status: return Color::status;
        case CardRarity::starter: return Color::common;
        case CardRarity::curse: return Color::curse;
        default: return Color::common;
    }
}

std::string Card::getCardTypeText(){
    switch(type){
        case CardType::attack: return "Attack";
        case CardType::skill: return "Skill";
        case CardType::power: return "Power";
        case CardType::status: return "Status";
        case CardType::curse: return "Curse";
        default: return "none";
    }
}

CardType Card::getCardType(){
    return type;
}
std::string Card::getCardRarity(){
        switch(rarity){
        case CardRarity::starter: return "Starter"; break;
        case CardRarity::common: return "Common"; break;
        case CardRarity::uncommon: return "Uncommon"; break;
        case CardRarity::rare: return "Rare"; break;
        case CardRarity::status: return "Status"; break;
        case CardRarity::curse: return "Curse"; break;
        default: return "none"; break;
    }
}

void Card::applyEffects(Player& source, Game& game, int pos){

    if(effects.empty()){return;}
    std::deque<Character*> targets = game.selectTargets(effects[0].getTarget(), &source);
    TargetType prev_target = effects[0].getTarget();


    if(!targets.empty()){ //If valid target
        
        source.removeFromPlayerPile(PileType::hand, pos); //Card is now "hovering" (not on any player pile).
        source.changeAttribute(Attribute::energy,-source.getPlayed().getEnergyCost()); //Pay energy cost.
        bool originalTargetDied = false;

        for(Effect e: effects){         //Iterate through every effect in the card.
            if( //Retarget if needed
                prev_target!=e.getTarget() || 
                e.getTarget() == TargetType::ally_all || 
                e.getTarget() == TargetType::enemy_all ||
                e.getTarget() == TargetType::random_enemy
            )
            {targets = game.selectTargets(e.getTarget(), &source);}
            else{if(originalTargetDied){continue;}} //Otherwise, if this effect would hit a single target that has died, don't resolve.

            prev_target = e.getTarget(); 
            e.apply(targets,source,game); //apply effects

            game.event_log.receive(e.log(targets,source));

            if((e.getTarget() == TargetType::ally || e.getTarget() == TargetType::enemy) && !targets[0]->isAlive()){originalTargetDied = true;}

            game.removeDeadCharacters(); //Do cleanup
        }
        //Post resolution
        if(exhaust){source.addToPile(PileType::exhaust, source.getPlayed(), false);}
        else{source.addToPile(PileType::discard, source.getPlayed(), false);}
    }
}

//Determines if a card can be played. Defaults to true, overrides
//for special cases depending on player/gamestate parameters.
bool Card::canPlay(Player& source, Game& game){
    bool able = true;
    if(name == "Clash"){ 
        able = source.findIndexes(PileType::hand, CardType::attack, false).size() == 0;
    }
    else if (name == "Grand Finale"){
        able = source.getPlayerPileSize(PileType::draw) == 0;
    }
    return able;
}

