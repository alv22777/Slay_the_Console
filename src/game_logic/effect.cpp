#include "game_logic/effect.h"
#include "game_logic/power.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EffectType t, int m, TargetType tar)
    :type(t), magnitude(m), target_type(tar){}

Effect::Effect(EffectType t, int m, TargetType tar, PID p)
    :type(t), magnitude(m), target_type(tar), power(p){}

Effect::Effect(EffectType t, int m, TargetType tar, CID c)
    :type(t), magnitude(m), target_type(tar), card(c){}
    

EffectReport Effect::apply(std::deque<Character*> target, Character* source, Game& game){

    EffectReport report;

    for(Character* c: target){//For every character in selected targets

        //Preventive programming for Player/Enemy specific behavior.
        Player* p = dynamic_cast<Player*>(c); 
        Enemy*  e = dynamic_cast<Enemy*>(c);
        
        switch(type){
            //General behavior
            case EffectType::damage: 
            {
                int32_t damage = magnitude;

                damage = source->modOutDamage(damage);
                damage = c->modIncDamage(damage);
                report.damage_dealt += c->takeDamage(damage); 
                
                break;
            }
            case EffectType::hp: 
            {
                report.hp_delta += c->changeAttribute(Attribute::hp,magnitude);
                break;
            }
            case EffectType::block:  
            {
                int32_t block = magnitude;
                block = c->modBlockGain(block);
                report.block_gained += c->gainBlock(block);  
                break;
            }    
            //Player specific behavior
            case EffectType::energy:{
                if(p){p->changeAttribute(Attribute::energy,magnitude);} 
                break;}
            case EffectType::draw:{
                if(p){report.cards_drawn += p->drawCards(magnitude,game);}
                break; }
            case EffectType::discard:{
                if(p){report.cards_discarded += p->transferCardsManual(PileID::hand, PileID::discard, magnitude, false, game);}
                break;}
            case EffectType::exhaust:{
                if(p){report.cards_exhausted += p->transferCardsManual(PileID::hand, PileID::exhaust, magnitude, false, game);} 
                break;}
            case EffectType::exhume:{
                if(p){p->transferCardsManual(PileID::exhaust,PileID::hand, magnitude, true, game);} 
                break;}
            case EffectType::hologram:{
                if(p){p->transferCardsManual(PileID::discard,PileID::hand, magnitude, true, game);} 
                break;}
            case EffectType::seek:{
                if(p){p->transferCardsManual(PileID::draw,   PileID::hand, magnitude, true,game);} 
                break;}
            case EffectType::headbutt:{
                if(p){p->transferCardsManual(PileID::discard,PileID::draw, magnitude, false, game);} 
                break;}
            case EffectType::forethought:{
                if(p){p->transferCardsManual(PileID::hand,   PileID::draw, magnitude, true, game);} 
                break;}
            case EffectType::expertise:{
                if(p){report.cards_drawn += p->drawCards(magnitude - p->getPlayerPileSize(PileID::hand), game);}
                break;}
            case EffectType::gain:{
                report.power_gained = *power;
                c->addPower(Power::createPower(*power, magnitude, c));
                break;
            }
            case EffectType::addCard:{
                if(p){
                    p->addToPile(PileID::hand, p->getPlayed(), false);
                }
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
    if(target_type == TargetType::self || target_type == TargetType::enemy || target_type == TargetType::player){return true;}
    else{return false;}
}

std::string Effect::log(std::deque<Character*> target, Character* source, EffectReport report){

    if(target.empty()){return "";}
    
    std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(abs(magnitude));
    bool single_target = target_type == TargetType::player   || target_type == TargetType::random_enemy || 
                         target_type == TargetType::enemy    || target_type == TargetType::self;

    //Default conditions
    if(single_target){who = color(target[0]->getColor(), target[0]->getName());}
    else{who = (target_type == TargetType::enemy_all)? "All enemies ":"All players ";}
    to_who = "";


    switch(type){
        case EffectType::damage:{
            who = color(source->getColor(),source->getName());
            
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