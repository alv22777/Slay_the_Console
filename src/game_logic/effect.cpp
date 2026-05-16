#include "game_logic/effect.h"

#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EffectType t, int m, TargetType tar)
    :type(t), magnitude(m), target_type(tar){}

void Effect::apply(std::deque<Character*> target, Character& source, Game& game){

    Player* player; Enemy* enemy;
    
    for(Character* c: target){//For every character in selected targets

        //Preventive programming for Player/Enemy specific behavior.
        player = dynamic_cast<Player*>(c); 
        enemy = dynamic_cast<Enemy*>(c);
        
        switch(type){
            //General behavior
            case EffectType::damage: {c->takeDamage(magnitude); break;}
            case EffectType::hp: {c->changeAttribute(Attribute::hp,magnitude); break;}
            case EffectType::block:  {c->gainBlock(magnitude);  break;}    
            //Player specific behavior
            case EffectType::draw:{ if(player){player->drawCards(magnitude,game);} break; }

            case     EffectType::discard:{if(player){player->transferCardsManual(PileType::hand,   PileType::discard, magnitude, false);} break;}
            case     EffectType::exhaust:{if(player){player->transferCardsManual(PileType::hand,   PileType::exhaust, magnitude, false);} break;}
            case      EffectType::exhume:{if(player){player->transferCardsManual(PileType::exhaust,PileType::hand,    magnitude, true);} break;}
            case    EffectType::hologram:{if(player){player->transferCardsManual(PileType::discard,PileType::hand,    magnitude, true);} break;}
            case        EffectType::seek:{if(player){player->transferCardsManual(PileType::draw,   PileType::hand,    magnitude, true);} break;}
            case    EffectType::headbutt:{if(player){player->transferCardsManual(PileType::discard,PileType::draw,    magnitude, false);} break;}
            case EffectType::forethought:{if(player){player->transferCardsManual(PileType::hand,   PileType::draw,    magnitude, true );} break;}

            case EffectType::energy: {if(player){player->changeAttribute(Attribute::energy,magnitude);} break;}
            default: {std::cout<<"No implementation yet!\n"; break;}
        }
    }
}

EffectType Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
TargetType Effect::getTarget(){return target_type;}
bool Effect::isSingleTarget(){
    if(target_type == TargetType::self || target_type == TargetType::enemy || target_type == TargetType::ally){return true;}
    else{return false;}
}

std::string Effect::log(std::deque<Character*> target, Character& source){
    
    if(target.empty()){return "";}
    
    std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(abs(magnitude));
    bool single_target = target_type == TargetType::ally   || target_type == TargetType::random_enemy || 
                         target_type == TargetType::enemy  || target_type == TargetType::self;

    //Default conditions
    if(single_target){who  = color(target[0]->getColor(), target[0]->getName());}
    else{who = (target_type == TargetType::enemy_all)? "All enemies ":"All allies ";}
    to_who = "";

    switch(type){
        case EffectType::damage:
            who = color(source.getColor(),source.getName());
            what = " dealt " + how_much + " damage to ";
            if(single_target){to_who  = color(target[0]->getColor(), target[0]->getName());}
            else{to_who = (target_type == TargetType::enemy_all)? " all enemies.":" all allies.";} 
        break;
        case EffectType::block:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " block.";
        break;
        case EffectType::energy:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " energy.";
        break;
        case EffectType::hp:
            what = ((magnitude>0)? " gained ":" lost " )+ how_much + " HP.";
        break;
        case EffectType::draw:
            what = " drew " + how_much + " card" + ((magnitude>1)? "s.":".");
        break;

        case EffectType::discard:
            what = " discarded " + how_much + " card" +((magnitude>1)? "s.":".");
        break;

        case EffectType::exhaust:
            what = " exhausted " + how_much + " card" +((magnitude>1)? "s.":".");
        break;
        case EffectType::strength:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " Strength.";
        break;

        case EffectType::dexterity:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " Dexterity.";
        break;

        case EffectType::weak:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " Weak.";
        break;
        case EffectType::vulnerable:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " Vulnerable.";
        break;
        case EffectType::frail:
            what = ((magnitude>0)? " gained ":" lost " ) + how_much + " Frail.";
        break;
        default: return "";

    }
    
        
    log = who + what + to_who;

    return log;

}