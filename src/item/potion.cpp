#include "item/potion.h"
#include "character/character.h"
#include "game_logic/effect.h"

Potion::Potion(PtID i, std::vector<Effect> e):
    id(i), effects(e){}

void Potion::use(Character* target){
    
}
