#ifndef POTION_H
#define POTION_H


#include <vector>
class Character; class Effect;

enum class PtID{

    //Common
    attack_potion, blessing_of_the_forge, block_potion, colorless_potion, 
    dexterity_potion, energy_potion, explosive_potion,  fear_potion, 
    fire_potion, flex_potion,  power_potion, skill_potion, speed_potion, 
    strength_potion, swift_potion, weak_potion,
   
    blood_potion, bottled_miracle, focus_potion, poison_potion,

    //Uncommon
    ancient_potion,  distilled_chaos, duplication_potion,  
    essence_of_steel,  gamblers_brew, liquid_bronze,
    liquid_memories, regen_potion, 

    cunning_potion, elixir, potion_of_capacity, stance_potion,

    //Rare
    cultist_potion, entropic_brew, fairy_in_a_bottle, fruit_juice, smoke_bomb, snecko_oil,

    ambrosia, essence_of_darkness, ghost_in_a_jar, heart_of_iron,  
};

class Potion{

    PtID id;
    std::vector<Effect> effects;

    public:

    Potion(PtID i, std::vector<Effect> e);
    void use(Character* Target);
};


#endif