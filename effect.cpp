#include "effect.h"
#include "character.h"
#include "constants.h"



Effect::Effect(EffectType t, int m)
    :type(t), magnitude(m){}

void Effect::apply(Character* target, Character& source, Game& game){
    switch(type){

        case EffectType::damage:

            if(magnitude>target->getAttribute(PlayerAttribute::block)){

                 //If the damage exceeds the target's block, reduce HP by the excess damage and set block to 0.
                target->changeAttribute(PlayerAttribute::HP,-magnitude+target->getAttribute(PlayerAttribute::block)); 
                target->setAttribute(PlayerAttribute::block,0);
                
                break;}

            else{target->changeAttribute(PlayerAttribute::block,-magnitude);break;}

        break;
        
        case EffectType::block: 
            if(target->getAttribute(PlayerAttribute::block)+magnitude>MAX_BLOCK){
                target->setAttribute(PlayerAttribute::block,MAX_BLOCK);
                std::cout<<"Reached maximum block!\n";
            }
            else{target->changeAttribute(PlayerAttribute::block, magnitude);} break;
            

        case EffectType::draw: target->drawCards(magnitude, game); break;

        case EffectType::discard: target->removeFromPlayerPile(PileType::hand, 0); break;
        case EffectType::exhaust: target->addToPlayerPile(PileType::exhaust, target->getCardFromPile(PileType::hand, 0)); break;
        case EffectType::energy: target->changeAttribute(PlayerAttribute::energy, magnitude); break;
    }

}