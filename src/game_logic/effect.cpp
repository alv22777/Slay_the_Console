#include "game_logic/effect.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EffectType t, int m, TargetType tar, std::optional<PID> p)
    :type(t), magnitude(m), target_type(tar), power(p){}

EffectReport Effect::apply(std::deque<Character*> target, Character& source, Game& game){

    Player* player; Enemy* enemy;
    EffectReport report;

    for(Character* c: target){//For every character in selected targets

        //Preventive programming for Player/Enemy specific behavior.
        player = dynamic_cast<Player*>(c); 
        enemy  = dynamic_cast<Enemy*>(c);
        
        switch(type){
            //General behavior
            case EffectType::damage: 
            {
                report.damage_dealt += c->takeDamage(magnitude); 
                break;
            }
            case EffectType::hp: 
            {
                report.hp_delta += c->changeAttribute(Attribute::hp,magnitude);
                break;
            }
            case EffectType::block:  
            {
                report.block_gained += c->gainBlock(magnitude);  
                break;
            }    
            //Player specific behavior
            case EffectType::energy:{
                if(player){player->changeAttribute(Attribute::energy,magnitude);} 
                break;}
            case EffectType::draw:{
                if(player){report.cards_drawn += player->drawCards(magnitude,game);}
                break; }
            case EffectType::discard:{
                if(player){report.cards_discarded += player->transferCardsManual(PileType::hand, PileType::discard, magnitude, false, game);}
                break;}
            case EffectType::exhaust:{
                if(player){report.cards_exhausted += player->transferCardsManual(PileType::hand, PileType::exhaust, magnitude, false, game);} 
                break;}
            case EffectType::exhume:{
                if(player){player->transferCardsManual(PileType::exhaust,PileType::hand, magnitude, true, game);} 
                break;}
            case EffectType::hologram:{
                if(player){player->transferCardsManual(PileType::discard,PileType::hand, magnitude, true, game);} 
                break;}
            case EffectType::seek:{
                if(player){player->transferCardsManual(PileType::draw,   PileType::hand, magnitude, true,game);} 
                break;}
            case EffectType::headbutt:{
                if(player){player->transferCardsManual(PileType::discard,PileType::draw, magnitude, false, game);} 
                break;}
            case EffectType::forethought:{
                if(player){player->transferCardsManual(PileType::hand,   PileType::draw, magnitude, true, game);} 
                break;}
            case EffectType::expertise:{
                if(player){report.cards_drawn += player->drawCards(magnitude - player->getPlayerPileSize(PileType::hand), game);}
                break;}
            case EffectType::gain:{
                report.power_gained = *power;
                c->addPower(Power::createPower(*power, magnitude, c));
                break;
            }
            
            default: {std::cout<<"No implementation yet!\n"; break;}
        }
    }

    return report;
}


EffectType Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
TargetType Effect::getTarget(){return target_type;}
bool Effect::isSingleTarget(){
    if(target_type == TargetType::self || target_type == TargetType::enemy || target_type == TargetType::ally){return true;}
    else{return false;}
}

std::string Effect::log(std::deque<Character*> target, Character& source, EffectReport report){

    if(target.empty()){return "";}
    
    std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(abs(magnitude));
    bool single_target = target_type == TargetType::ally   || target_type == TargetType::random_enemy || 
                         target_type == TargetType::enemy  || target_type == TargetType::self;

    //Default conditions
    if(single_target){who  = color(target[0]->getColor(), target[0]->getName());}
    else{who = (target_type == TargetType::enemy_all)? "All enemies ":"All players ";}
    to_who = "";


    switch(type){
        case EffectType::damage:{
            who = color(source.getColor(),source.getName());
            
            if(single_target){
                how_much = std::to_string(abs(report.damage_dealt));
                to_who  = color(target[0]->getColor(), target[0]->getName());
            }
            else{to_who = (target_type == TargetType::enemy_all)? " all enemies.":" all players.";} 

            what = " dealt " + how_much + " damage to ";

        break;}
        case EffectType::block:{
            if(report.block_gained == 0){return "";}
            how_much = std::to_string(abs(report.block_gained));
            what = ((report.block_gained>0)? " gained ":" lost " ) + how_much + " block.";
        break;}
        case EffectType::energy:{
            if(report.energy_gained == 0){return "";}        
            how_much = std::to_string(abs(report.energy_gained));
            what = ((report.energy_gained>0)? " gained ":" lost " ) + how_much + " energy.";
        break;}
        case EffectType::hp:{
            if(report.hp_delta == 0){return "";}
            how_much = std::to_string(abs(report.hp_delta));
            what = ((report.hp_delta>0)? " gained ":" lost " )+ how_much + " HP.";
        break;}
        case EffectType::draw:{
            if(report.cards_drawn == 0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((magnitude>1)? "s.":".");
        break;}

        case EffectType::discard:{
            if(report.cards_discarded == 0){return "";}
            how_much = std::to_string(abs(report.cards_discarded));
            what = " discarded " + how_much + " card" +((magnitude>1)? "s.":".");
        break;}

        case EffectType::exhaust:{
            if(report.cards_exhausted == 0){return "";}
            how_much = std::to_string(abs(report.cards_exhausted));
            what = " exhausted " + how_much + " card" +((magnitude>1)? "s.":".");
        break;}
        case EffectType::gain:{
            if(magnitude == 0){return "";}
            what = ((magnitude>0)? " gained ":" lost " ) + how_much +" "+Power::IDtoString(*power, true)+".";
        break;}

        case EffectType::expertise:{
            if(report.cards_drawn==0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((magnitude>1)? "s.":".");
        break;}

        default:{ return ""; break; }

    }
    
        
    log = who + what + to_who;

    return log;
}