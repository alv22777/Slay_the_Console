#ifndef INTENT_H
#define INTENT_H


#include <vector>
#include <iostream>
#include <ui/colors.h>
#include <memory>

class Effect; class Enemy; enum class EID; enum class TID; class Game;
enum class IntentType{attack, block, buff, debuff, create_card, die, summon, unknown};


class Intent{

    std::vector<std::shared_ptr<Effect>> actions; //Everything the enemy will do
    
    public:

    Intent(std::vector<std::shared_ptr<Effect>> a);
    
    std::vector<std::shared_ptr<Effect>> getActions();
    
};

#endif