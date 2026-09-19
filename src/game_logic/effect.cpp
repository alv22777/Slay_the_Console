#include "game_logic/effect.h"
#include "game_logic/power.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"
#include <windows.h>



bool Condition::check(Game* game, Character* target){
    Enemy* e = dynamic_cast<Enemy*>(target);
    Player* p = dynamic_cast<Player*>(target);

    switch(predicate){
        case Predicate::target_has_power:{
            int count = target->countPower(power);
            if(count > 0){return true;}else{return false;}
        }
        case Predicate::target_intents_to_attack:{
            if(!e){return false;}
            return e->isAttacking();
        }
        default: return true;
    }
}

Effect::Effect(EID t, int m, TID tar)
    :type(t), magnitude(m), target_type(tar), condition(Condition()){}

EffectReport Effect::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){
    EffectReport results; return results;
}

EID Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
Condition Effect::getCondition(){return condition;}
TID Effect::getTarget(){return target_type;}
bool Effect::isSingleTarget(){
    if(target_type == TID::self || target_type == TID::enemy || target_type == TID::player){return true;}
    else{return false;}
}

void Effect::setMagnitude(int n){magnitude = n;}

std::string Effect::log(std::deque<Character*> target, Character* source, EffectReport report){
    if(target.empty()){return "";}
    std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(abs(magnitude));
    bool single_target = target_type == TID::player   || target_type == TID::random_enemy || 
                         target_type == TID::enemy    || target_type == TID::self;

    //Default conditions
    if(single_target){who = color(target[0]->getColor(), target[0]->getName());}
    else{who = (target_type == TID::enemy_all)? "All enemies":"All players";}
    to_who = "";

    switch(type){
        case EID::damage:{

            
            who = color(source->getColor(),source->getName());
            

            if(single_target){
                how_much = std::to_string(abs(report.damage_dealt));
                to_who  = color(target[0]->getColor(), target[0]->getName());
                if(report.damage_dealt == 0){return to_who + " blocked " + std::to_string(magnitude) + " damage.";}
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
            CardTransfer* e = dynamic_cast<CardTransfer*>(this);
            if(e){
                switch(e->getTargetPile()){
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

            PowerManip* e = dynamic_cast<PowerManip*>(this);
            if(e){
                what = ((magnitude>0)? " gained ":" lost " ) + how_much +" "+Power::IDtoString(e->getPID(), true)+".";
            }
        break;}

        case EID::expertise:{
            if(report.cards_drawn==0){return "";}
            how_much = std::to_string(abs(report.cards_drawn));
            what = " drew " + how_much + " card" + ((report.cards_drawn>1)? "s.":".");
        break;}

        case EID::add_card_top:
        case EID::add_card_bot:
        case EID::shuffleCard:{
            CreateCard* e = dynamic_cast<CreateCard*>(this);
            if(e){
                if(report.cards_added == 0){return "";}
                how_much = std::to_string(abs(report.cards_added));
                what = " created " + how_much + " card" + ((report.cards_added>1)? "s.":".");
            }
            break;
        }
        default:{ return ""; break; }

    }
        
    log = who + what + to_who;

    return log;
}


CombatAction::CombatAction(EID t, int m, TID tar):
    Effect(t,m,tar) {}

CombatAction::CombatAction(EID t, int m, TID tar, Condition cond):
    Effect(t,m,tar) {condition = cond;}

EffectReport CombatAction::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){
    EffectReport report;


    for(Character* c: target){
        if(check){
            if(!condition.check(&game, check)){continue;}
        }
        
        if(!c->isAlive()){continue;}
        Player* p = dynamic_cast<Player*>(c); 
        Enemy*  e = dynamic_cast<Enemy*>(c);

        switch(type){
            case EID::damage: 
            {
                int32_t damage = magnitude;
                damage = source->modOutDamage(damage);
                damage = c->modIncDamage(damage);
                report.damage_dealt += c->takeDamage(damage); 
                c->onHit(source, game);
                if(report.damage_dealt > 0){source->onUnblockedAttack(c, game);}
            }
            break;

            case EID::hp: 
            {
                report.hp_delta += c->changeAttribute(Attribute::hp,magnitude);
            }
            break;
            case EID::block:  
            {
                int32_t block = magnitude;
                block = c->modBlockGain(block);
                report.block_gained += c->gainBlock(block);  
            }
            break;    
            //Player specific behavior
            case EID::energy:{
                if(p){p->changeAttribute(Attribute::energy,magnitude);} 
            }
            break;

            case EID::draw:{
                if(p){report.cards_drawn += p->drawCards(magnitude,game);}
            }
            break;

            case EID::expertise:{
                if(p){report.cards_drawn += p->drawCards(magnitude - p->getPlayerPileSize(PileID::hand), game);}
            }
            break;

            default: Effect::apply(target,source,game, check);  break;     
        }
    }
    return report;
}

RunAction::RunAction(EID t, int m):
    Effect(t,m, TID::player){}

RunAction::RunAction(EID t, int m, Condition cond):
    Effect(t,m, TID::player){condition = cond;}
      
EffectReport RunAction::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){

    EffectReport report;
 
    for(Character* c: target){//For every character in selected targets
        if(check){
            if(!condition.check(&game, check)){continue;}
        }
        if(!c->isAlive()){continue;}
        //Preventive programming for Player/Enemy specific behavior.
        Player* p = dynamic_cast<Player*>(c); 
        switch(type){ 
            case EID::max_hp: 
                c->changeAttribute(Attribute::max_hp, magnitude);
            break;
            default: Effect::apply(target,source,game,check); break;
        }
    }

    return report;
}

CreateCard::CreateCard(int m, CID c, PileID tar_p, Position pos):
    Effect(EID::none, m, TID::player), target_pile(tar_p), position(pos), card(c){
        switch(position){
            case Position::top:
                type = EID::add_card_top;
            break;
            case Position::bottom:
                type = EID::add_card_bot;
            break;
            case Position::random:
                type = EID::shuffleCard;
            break;     
        }
    }

CreateCard::CreateCard(int m, CID c, PileID tar_p, Position pos, Condition cond):
    Effect(EID::none, m, TID::player), target_pile(tar_p), position(pos), card(c){
        switch(position){
            case Position::top:
                type = EID::add_card_top;
            break;
            case Position::bottom:
                type = EID::add_card_bot;
            break;
            case Position::random:
                type = EID::shuffleCard;
            break;     
        }
        condition = cond;
    }

CID CreateCard::getCID(){return card;}
PileID CreateCard::getTargetPile(){return target_pile;}

EffectReport CreateCard::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){
    EffectReport report;

    for(Character* c: target){
        if(check){
            if(!condition.check(&game, check)){continue;}
        }
        
        if(!c->isAlive()){continue;}
        
        Player* p = dynamic_cast<Player*>(c); 
        if(!p){return report;}
        
        switch(type){
            case EID::add_card_top:{
                Card add = createCard(card);
                for(int i = 0;i<magnitude;i++){ p->addToPile(target_pile, add, false); }
            }
            break;
            case EID::add_card_bot:{
                Card add = createCard(card);
                for(int i = 0;i<magnitude;i++){ p->addToPile(target_pile, add, true); }
            }
            break;
            case EID::shuffleCard:{
                Card add = createCard(card);
                for(int i = 0; i<magnitude;i++){p->shuffleIntoDraw(add, game);}
            }
            break;
            default: Effect::apply(target,source,game,check); break;     
        }
    }
    report.cards_added = magnitude;
    return report;
}

CardTransfer::CardTransfer(EID t, int m, PileID src_p, PileID tar_p):
    Effect(t,m, TID::player), source_pile(src_p), target_pile(tar_p){}

CardTransfer::CardTransfer(EID t, int m, PileID src_p, PileID tar_p, Condition cond):
    Effect(t,m, TID::player), source_pile(src_p), target_pile(tar_p) {condition = cond;}

PileID CardTransfer::getSourcePile(){return source_pile;}
PileID CardTransfer::getTargetPile(){return target_pile;}

EffectReport CardTransfer::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){
    EffectReport report;

    for(Character* c: target){

        if(check){
            if(!condition.check(&game, check)){continue;}
        }

        if(!c->isAlive()){continue;}
        Player* p = dynamic_cast<Player*>(c); 
        if(!p){return report;}
        
        switch(type){
            case EID::discard:{
                report.cards_transferred += p->transferCardsManual(PileID::hand, PileID::discard, magnitude, false, game);
            }
            break;
            case EID::exhaust:{
                report.cards_transferred += p->transferCardsManual(PileID::hand, PileID::exhaust, magnitude, false, game); 
            }
            break;
            case EID::random_card_transfer:{
                std::deque<int> choices = p->randomCards(source_pile, magnitude, game);
                report.cards_transferred += p->transferCardsAuto(source_pile, target_pile, choices, true, game);
            }
            break;
            
            case EID::cards_bottom:{
                p->transferCardsManual(source_pile, target_pile, magnitude, true, game);
            }  
            break;
            case EID::cards_top:{
                p->transferCardsManual(source_pile, target_pile, magnitude, false, game);               
            }
            break;    

            default: Effect::apply(target,source,game, check); break; 
        }
    }
    return report;
}



PowerManip::PowerManip(EID t, int m, TID tar, PID p):
    Effect(t,m, tar), power(p){}
PowerManip::PowerManip(EID t, int m, TID tar, PID p, Condition cond):
    Effect(t,m, tar), power(p){condition = cond;}


PID PowerManip::getPID(){return power;}

EffectReport PowerManip::apply(std::deque<Character*> target, Character* source, Game& game, Character* check){

    EffectReport report;
 
    for(Character* c: target){//For every character in selected targets
        if(check){
            if(!condition.check(&game, check)){continue;}
        }
        if(!c->isAlive()){continue;}
        //Preventive programming for Player/Enemy specific behavior.
        Player* p = dynamic_cast<Player*>(c); 
        Enemy*  e = dynamic_cast<Enemy*>(c);
        
        switch(type){ 
            
            
            case EID::gain:{
                report.power_gained = power;
                c->addPower(power, magnitude);
            }
            break;
            case EID::lose:{
                report.power_gained = power;
                c->addPower(power, -magnitude);
            }
            break;
            default: Effect::apply(target,source,game,check); break;
        }
    }

    return report;
}
