#ifndef ENEMY_H
#define ENEMY_H

#include "character/character.h"

class Enemy: public Character{

    //std::deque<Intent> Intents;
    

    public:
    Enemy(std::string n, int mHP);

    void displayStatus();
    ~Enemy() noexcept override = default;
};

#endif