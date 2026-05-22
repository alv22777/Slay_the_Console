#include "card/card.h"
#include "game_logic/game.h"
#include "character/player.h"
#include "game_logic/effect.h"
#include "ui/colors.h"
#include "ui/formatting.h"
#include<iostream>
#include<vector>



//Creates a Card and initializes it's values with the given arguments.
Card::Card(CID i, Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e), exhaust(ex), id(i){}   
    
//Display this card
void Card::display(){
    std::string cost = color(Color::keyword, to_energy(energy_cost));
    
    std::string card_type;
    switch(type){
        case CardType::attack: card_type = color(character, u8" ▲ "); break;
        case CardType::skill: card_type = color(character, u8" ■ "); break;
        case CardType::power: card_type = color(character, u8" ● "); break;
        case CardType::status: card_type = color(Color::status,u8"  ꩜ "); break;
        case CardType::curse: card_type = color(Color::curse,u8"  ⛦ "); break;
        default: card_type="none"; break; 
    }

    std::cout<<cost<<card_type<<color(rarityColor(), name)<<": "<<card_text;
    if(exhaust){std::cout<<color(Color::exhaust," Exhaust.");}
}

int Card::getEnergyCost(){return energy_cost;}

CID Card::getID(){return id;}
std::string Card::getName(){return name;}

Color Card::rarityColor(){
    switch(rarity){
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

CardType Card::getCardType(){return type;}
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

    if(effects[0].isSingleTarget()||game.hasValidTargets(effects[0].getTarget(),  source)){
        source.removeFromPlayerPile(PileType::hand, pos); //Card is now "hovering" (not on any player pile).
        source.changeAttribute(Attribute::energy,-source.getPlayed().getEnergyCost()); //Pay energy cost.
    }
    
    game.resolveEffects(source,effects);

    if(exhaust){source.addToPile(PileType::exhaust, source.getPlayed(), false);}
    else{source.addToPile(PileType::discard, source.getPlayed(), false);}

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

