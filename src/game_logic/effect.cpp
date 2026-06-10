#include "game_logic/effect.h"
#include "game_logic/power.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"
#include <windows.h>

Effect::Effect(EID t, int m, TID tar)
    :type(t), magnitude(m), target_type(tar){}

Effect::Effect(EID t, int m, TID tar, PID p)
    :type(t), magnitude(m), target_type(tar), power(p){}

Effect::Effect(EID t, int m, CID c, PileID tar_p) //Add cards can only be done to a player
    :type(t), magnitude(m), target_type(TID::player), card(c), target_pile(tar_p){}
    
Effect::Effect(EID t, int m, PileID src_p, PileID tar_p)
    :type(t), magnitude(m), target_type(TID::player), source_pile(src_p), target_pile(tar_p){}

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
                c->onHit(source, game);
                
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
                if(p){report.cards_transferred += p->transferCardsManual(PileID::hand, PileID::discard, magnitude, false, game);}
                break;}
            case EID::exhaust:{
                if(p){report.cards_transferred += p->transferCardsManual(PileID::hand, PileID::exhaust, magnitude, false, game);} 
                break;} 

            case EID::random_card_transfer:{
                if(p){
                    std::deque<int> choices = p->randomCards(*source_pile, magnitude, game);
                    report.cards_transferred += p->transferCardsAuto(*source_pile, *target_pile, choices, true);
                }
                break;
            }
            
            case EID::cards_bottom:{
                if(p && source_pile && target_pile && card){
                    p->transferCardsManual(*source_pile, *target_pile, magnitude, true, game);
                }
                else{throw std::runtime_error("Invalid Effect configuration: cardsBottom effect requires source and target piles, and a card ID.");}
                break;
            }  
            case EID::cards_top:{
                if(p && source_pile && target_pile && card){
                    p->transferCardsManual(*source_pile, *target_pile, magnitude, false, game);
                }
                else{throw std::runtime_error("Invalid Effect configuration: cardsTop effect requires source and target piles, and a card ID.");}
                break;
            }
            case EID::expertise:{
                if(p){report.cards_drawn += p->drawCards(magnitude - p->getPlayerPileSize(PileID::hand), game);}
                break;}
            case EID::gain:{
                report.power_gained = *power;
                c->addPower(*power, magnitude);
                break;
            }
            case EID::addCard:{
                if(p){
                    Card add = createCard(*card);
                    for(int i = 0;i<magnitude;i++){ p->addToPile(*target_pile, add, true); }
                }
                break;
            }
            case EID::shuffleCard:{
                if(p){
                    Card add = createCard(*card);
                    for(int i = 0; i<magnitude;i++){p->shuffleIntoDraw(add, game);}
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
            else{to_who = (target_type == TID::enemy_all)? "all enemies.":"all players.";} 

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
            what = " drew " + how_much + " card" + ((report.cards_drawn>1)? "s.":".");
        break;}
        case EID::discard:{
            if(report.cards_transferred == 0){return "";}
            how_much = std::to_string(abs(report.cards_transferred));
            what = " discarded " + how_much + " card" +((report.cards_transferred>1)? "s.":".");
        break;}

        case EID::exhaust:{
            if(report.cards_transferred == 0){return "";}
            how_much = std::to_string(abs(report.cards_transferred));
            what = " exhausted " + how_much + " card" +((report.cards_transferred>1)? "s.":".");
        break;}

        case EID::random_card_transfer:{
            std::string where;
            if(target_pile.has_value()){
                switch(*target_pile){
                    case PileID::exhaust: where = " exhausted "; break;
                    case PileID::discard: where = " discarded "; break;
                    default: where = " transferred "; break;
                }
            }
            
            if(report.cards_transferred == 0){return "";}
            how_much = std::to_string(abs(report.cards_transferred));
            what = where + how_much + " card" + ((report.cards_transferred>1)? "s.":".");
            break;
        }   
        case EID::gain:{
            if(magnitude == 0){return "";}
            what = ((magnitude>0)? " gained ":" lost " ) + how_much +" "+Power::IDtoString(*power, true)+".";
        break;}

        case EID::expertise:{
            if(report.cards_drawn==0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((report.cards_drawn>1)? "s.":".");
        break;}

        default:{ return ""; break; }

    }
        
    log = who + what + to_who;

    return log;
}