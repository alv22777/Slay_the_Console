#include "character/intent.h"
#include "game_logic/effect.h"
#include "ui/colors.h"

std::vector<Effect> Intent::getActions(){return actions;}


Intent::Intent(std::vector<Effect> a): actions(a){}

void Intent::display(){
    for(Effect e: actions){
        std::cout<<"[";
        switch(e.getType()){
            case EffectType::block: std::cout<<color(Color::block,"BLOCK"); break;
            case EffectType::damage: std::cout<<color(Color::attack, "ATTACK "+std::to_string(e.getMagnitude())); break;
            case EffectType::strength: std::cout<<color(Color::buff, "BUFF"); break;
            default: std::cout<<color(Color::unknown, "???"); break;
        }
        std::cout<<"] ";
    }
}