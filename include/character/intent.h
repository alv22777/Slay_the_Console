#ifndef INTENT_H
#define INTENT_H


#include <vector>
#include <iostream>
#include <ui/colors.h>

class Effect; class Enemy; enum class EID; enum class TID; class Game;
enum class IntentType{attack, block, buff, debuff, create_card, die, summon, unknown};


class Intent{

    std::vector<Effect> actions; //Everything the enemy will do
    
    public:

    Intent(std::vector<Effect> a);
    
    std::vector<Effect>& getActions();
    
};

#endif