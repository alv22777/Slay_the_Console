#include "game_logic/effect.h"
#include "game_logic/power.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EID t, int m, TID tar)
    :type(t), magnitude(m), target_type(tar){}

Effect::Effect(EID t, int m, TID tar, PID p)
    :type(t), magnitude(m), target_type(tar), power(p){}

Effect::Effect(EID t, int m, TID tar, CID c)
    :type(t), magnitude(m), target_type(tar), card(c){}
    

EffectReport Effect::apply(std::deque<Character*> target, Character* source, Game& game){

    EffectReport report;

    for(Character* c: target){//For every character in selected targets

        //Preventive programming for Player/Enemy specific behavior.
        Player* p = dynamic_cast<Player*>(c); 
        Enemy*  e = dynamic_cast<Enemy*>(c);
        
        switch(type){
            //General behavior
            case EID::damage: 
            {
                int32_t damage = magnitude;
                damage = source->modOutDamage(damage);
                damage = c->modIncDamage(damage);
                report.damage_dealt += c->takeDamage(damage); 
                
                break;
            }
            case EID::hp: 
            {
                report.hp_delta += c->changeAttribute(Attribute::hp,magnitude);
                break;
            }
            case EID::block:  
            {
                int32_t block = magnitude;
                block = c->modBlockGain(block);
                report.block_gained += c->gainBlock(block);  
                break;
            }    
            //Player specific behavior
            case EID::energy:{
                if(p){p->changeAttribute(Attribute::energy,magnitude);} 
                break;}
            case EID::draw:{
                if(p){report.cards_drawn += p->drawCards(magnitude,game);}
                break; }
            case EID::discard:{
                if(p){report.cards_discarded += p->transferCardsManual(PileID::hand, PileID::discard, magnitude, false, game);}
                break;}
            case EID::exhaust:{
                if(p){report.cards_exhausted += p->transferCardsManual(PileID::hand, PileID::exhaust, magnitude, false, game);} 
                break;}
            case EID::exhume:{
                if(p){p->transferCardsManual(PileID::exhaust,PileID::hand, magnitude, true, game);} 
                break;}
            case EID::hologram:{
                if(p){p->transferCardsManual(PileID::discard,PileID::hand, magnitude, true, game);} 
                break;}
            case EID::seek:{
                if(p){p->transferCardsManual(PileID::draw,   PileID::hand, magnitude, true,game);} 
                break;}
            case EID::headbutt:{
                if(p){p->transferCardsManual(PileID::discard,PileID::draw, magnitude, false, game);} 
                break;}
            case EID::forethought:{
                if(p){p->transferCardsManual(PileID::hand,   PileID::draw, magnitude, true, game);} 
                break;}
            case EID::setup:{
                if(p){p->transferCardsManual(PileID::draw,   PileID::hand, magnitude, false, game);} 
                break;}    
            case EID::expertise:{
                if(p){report.cards_drawn += p->drawCards(magnitude - p->getPlayerPileSize(PileID::hand), game);}
                break;}
            case EID::gain:{
                report.power_gained = *power;
                c->addPower(Power::createPower(*power, magnitude, c));
                break;
            }
            case EID::addCard:{
                if(p){
                    Card add = createCard(*card);
                    for(int i = 0;i<magnitude;i++){ p->addToPile(PileID::hand, add, true); }
                }
            }
            
            default: {std::cout<<"No implementation yet!\n"; break;}
        }
    }

    return report;
}


EID Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
TID Effect::getTarget(){return target_type;}
bool Effect::isSingleTarget(){
    if(target_type == TID::self || target_type == TID::enemy || target_type == TID::player){return true;}
    else{return false;}
}

std::string Effect::log(std::deque<Character*> target, Character* source, EffectReport report){

    if(target.empty()){return "";}
    
    std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(abs(magnitude));
    bool single_target = target_type == TID::player   || target_type == TID::random_enemy || 
                         target_type == TID::enemy    || target_type == TID::self;

    //Default conditions
    if(single_target){who = color(target[0]->getColor(), target[0]->getName());}
    else{who = (target_type == TID::enemy_all)? "All enemies ":"All players ";}
    to_who = "";

    switch(type){
        case EID::damage:{
            who = color(source->getColor(),source->getName());
            
            if(single_target){
                how_much = std::to_string(abs(report.damage_dealt));
                to_who  = color(target[0]->getColor(), target[0]->getName());
            }
            else{to_who = (target_type == TID::enemy_all)? " all enemies.":" all players.";} 

            what = " dealt " + how_much + " damage to ";

        break;}
        case EID::block:{
            if(report.block_gained == 0){return "";}
            how_much = std::to_string(abs(report.block_gained));
            what = ((report.block_gained>0)? " gained ":" lost " ) + how_much + " block.";
        break;}
        case EID::energy:{
            if(report.energy_gained == 0){return "";}        
            how_much = std::to_string(abs(report.energy_gained));
            what = ((report.energy_gained>0)? " gained ":" lost " ) + how_much + " energy.";
        break;}
        case EID::hp:{
            if(report.hp_delta == 0){return "";}
            how_much = std::to_string(abs(report.hp_delta));
            what = ((report.hp_delta>0)? " gained ":" lost " )+ how_much + " HP.";
        break;}
        case EID::draw:{
            if(report.cards_drawn == 0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((magnitude>1)? "s.":".");
        break;}

        case EID::discard:{
            if(report.cards_discarded == 0){return "";}
            how_much = std::to_string(abs(report.cards_discarded));
            what = " discarded " + how_much + " card" +((magnitude>1)? "s.":".");
        break;}

        case EID::exhaust:{
            if(report.cards_exhausted == 0){return "";}
            how_much = std::to_string(abs(report.cards_exhausted));
            what = " exhausted " + how_much + " card" +((magnitude>1)? "s.":".");
        break;}
        case EID::gain:{
            if(magnitude == 0){return "";}
            what = ((magnitude>0)? " gained ":" lost " ) + how_much +" "+Power::IDtoString(*power, true)+".";
        break;}

        case EID::expertise:{
            if(report.cards_drawn==0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((magnitude>1)? "s.":".");
        break;}

        default:{ return ""; break; }

    }
    
        
    log = who + what + to_who;

    return log;
}