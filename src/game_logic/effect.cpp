#include "game_logic/effect.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/character.h"
#include "data/constants.h"


Effect::Effect(EffectType t, int m)
    :type(t), magnitude(m){}

void Effect::apply(Character* target, Character& source, Game& game){
    
    //Detect whether target is Player or Enemy object.
    Player* player = dynamic_cast<Player*>(target); 
    Enemy* enemy = dynamic_cast<Enemy*>(target); 
    
    switch(type){
        case EffectType::damage:

            if(magnitude>target->getAttribute(Attribute::block)){

                 //If the damage exceeds the target's block, reduce HP by the excess damage and set block to 0.
                target->changeAttribute(Attribute::hp,-magnitude+target->getAttribute(Attribute::block)); 
                target->setAttribute(Attribute::block,0);
                
                break;}

            else{target->changeAttribute(Attribute::block,-magnitude);break;}

        break;
        
        case EffectType::block:{ 
            if(target->getAttribute(Attribute::block)+magnitude>MAX_BLOCK){
                target->setAttribute(Attribute::block,MAX_BLOCK);
                std::cout<<"Reached maximum block!\n";
            }
            else{target->changeAttribute(Attribute::block, magnitude);} break;
        }

        case EffectType::draw:{ if(player){player->drawCards(magnitude,game);} break; }
        case EffectType::discard:{ std::cout<<"DISCARDING!!!\n"; break; }
        case EffectType::energy: {std::cout<<"EXHAUSTING!!!\n"; break;}
        case EffectType::hp: {target-> changeAttribute(Attribute::hp,magnitude); break;}
        default: {std::cout<<"No effect!\n"; break;}
    }
}