#include "character/intent.h"
#include "game_logic/effect.h"
#include "ui/colors.h"

std::vector<Effect> Intent::getActions(){return actions;}


Intent::Intent(std::vector<Effect> a): actions(a){}

void Intent::display(){
    
    int n = 0;
    bool displayedAttack = false;
    bool attack;
    for(Effect e:actions){
        (e.getType()==EffectType::damage)?  n++ : n;
    }

    for(Effect e: actions){
        attack = e.getType()==EffectType::damage;
        
        if((attack && !displayedAttack)||(!attack)){ std::cout<<"{"; }

        switch(e.getType()){
            case EffectType::block: std::cout<<color(Color::block,"BLOCK"); break;
            case EffectType::damage:
                if(n>1){
                    if(!displayedAttack){
                        std::cout<<color(Color::attack, "ATTACK "+std::to_string(e.getMagnitude()) + "x" + std::to_string(n)); 
                    }
                }else{ std::cout<<color(Color::attack, "ATTACK "+std::to_string(e.getMagnitude())); }
            break;
            case EffectType::strength: std::cout<<color(Color::buff, "BUFF"); break;
            default: std::cout<<color(Color::unknown, "???"); break;
        }
        
        if(attack && !displayedAttack){ std::cout<<"}"; displayedAttack=true; }
        else if(!attack){std::cout<<"}";}
    }

}