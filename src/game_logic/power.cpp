#include "game_logic/power.h"
void Power::trigger(){
    if(decremented){intensity--;}
}

void Power::add(uint32_t delta){
    if(stackable){intensity += delta;}
}
void Power::remove(uint32_t delta){
    intensity -= delta;
}
void Power::eliminate(){
    intensity = 0;
}

