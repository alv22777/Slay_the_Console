#include "effect.h"
#include "character.h"

Effect::Effect(EffectType t, int m)
    :type(t), magnitude(m){}

void Effect::apply(Character& target){
    switch(type){

        case EffectType::damage:

            if(magnitude>target.getAttribute(PlayerAttribute::block)){
                target.setAttribute(PlayerAttribute::block,0); 
                target.changeAttribute(PlayerAttribute::HP,-magnitude+target.getAttribute(PlayerAttribute::block));  
                break;}

            else{target.changeAttribute(PlayerAttribute::block,-magnitude);break;}

        break;
        
        case EffectType::block: target.changeAttribute(PlayerAttribute::block, magnitude); break;
        case EffectType::draw: target.addToPlayerPile(PileType::hand, target.getCardFromPile(PileType::draw, 0)); break;
        case EffectType::discard: target.removeFromPlayerPile(PileType::hand, 0); break;
        case EffectType::exhaust: target.addToPlayerPile(PileType::exhaust, target.getCardFromPile(PileType::hand, 0)); break;
        case EffectType::energy: target.changeAttribute(PlayerAttribute::energy, magnitude); break;
    }

}