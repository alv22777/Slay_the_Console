#include "game_logic/effect.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EffectType t, int m, TargetType tar)
    :type(t), magnitude(m), target(tar){}

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
            case EffectType::energy: {std::cout<<"EXHAUSTING!!!\n"; break;}
            case EffectType::hp: {c->changeAttribute(Attribute::hp,magnitude); break;}
            default: {std::cout<<"No effect!\n"; break;}
        }
    }
    
}

EffectType Effect::getType(){return type;}
int Effect::getMagnitude(){return magnitude;}
TargetType Effect::getTarget(){return target;}
