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
            case EffectType::damage: {c->takeDamage(magnitude); break;}
            case EffectType::block:  {c->gainBlock(magnitude);  break;}    
            case EffectType::draw:{ if(player){player->drawCards(magnitude,game);} break; }
            case EffectType::discard:{ std::cout<<"DISCARDING!!!\n"; break; }
            case EffectType::energy: {c->changeAttribute(Attribute::energy,magnitude); break;}
            case EffectType::hp: {c->changeAttribute(Attribute::hp,magnitude); break;}
            default: {std::cout<<"No effect!\n"; break;}
        }
        

        
    }
    
}

EffectType Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
TargetType Effect::getTarget(){return target_type;}

std::string Effect::log(std::deque<Character*> target, Character& source){
   std::string log; std::string who; std::string what; std::string to_who; std::string how_much = std::to_string(magnitude);

    who = color(source.getColor(), source.getName());
    
    if(target.size()==1&& target_type != TargetType::self){to_who = color(target[0]->getColor(), target[0]->getName()) +"." ;}
    else{
        switch(target_type){
            case TargetType::ally_all : to_who = "all players."; break;
            case TargetType::enemy_all: to_who = "all enemies."; break;        
        }
    }


    switch(type){
            case EffectType::damage: 
                what = " dealt " + how_much + " damage to "; 
            break;
            
            case EffectType::block:
                if(target.size()==1){
                    who = color(target[0]->getColor(), target[0]->getName());               
                    what = " gained "  + how_much + " block." ;
                    to_who = ""; 
                }
                else{
                    what = " gave "  + how_much + " block to " ;
                }
            break;

            case EffectType::draw:
                if(target.size()==1){
                    who = color(target[0]->getColor(), target[0]->getName());   
                }
                what = " drew "  + how_much + "  cards.";    
            break;

            case EffectType::discard: 
                what = " discarded "+ how_much + " cards.";   
            break;
            case EffectType::energy : 
                what = ((magnitude>=0)? " gained ":" lost ")+ how_much + " energy."; 
            break;
            case EffectType::hp: 
                what = ((magnitude>=0)? " gained ":" lost ") + how_much + " HP."; 
            break;

            default: what = ""; break;
    }
    
    if(target_type == TargetType::self){to_who="";}
    if(target.empty()){return "";}

    log = who + what + to_who;

    return who+what+to_who;

}